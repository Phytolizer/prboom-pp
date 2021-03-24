from enum import Enum, auto
from os import mkdir, rmdir, remove, listdir
from os.path import exists
from subprocess import run

from inflection import underscore

SYSTEM_INCLUDES = ["cstdint", "stdexcept"]


class State(Enum):
    Name = auto()
    OpenBrace = auto()
    Includes = auto()
    PreDeclarations = auto()
    Namespace = auto()
    TypeStart = auto()
    FnOpenParen = auto()
    FnArg = auto()
    FnCloseParen = auto()
    FnArrow = auto()
    FnReturnType = auto()
    FieldName = auto()


class FunctionType:
    def __init__(self):
        self.args = []
        self.return_type = None

    def __str__(self):
        return f"{self.return_type} (*)({','.join(self.args)})"


class UnionField:
    def __init__(self):
        self.ty = None
        self.name = None

    def __str__(self):
        return f"UnionField {{ ty: {self.ty}, name: {self.name} }}"

    def field_type(self):
        if isinstance(self.ty, FunctionType):
            return f"m_{self.name}_t"
        else:
            return f"{self.ty}"

    def is_pointer(self):
        return self.is_function() or self.ty.endswith("*")

    def is_function(self):
        return isinstance(self.ty, FunctionType)


class Union:
    def __init__(self):
        self.name = None
        self.fields = []

    def reset(self):
        self.name = None
        self.fields = []

    def __str__(self):
        return (
            f"Union {{ name: {self.name}, fields: {', '.join(map(str, self.fields))} }}"
        )


def generate(union):
    print(f"Generating unions/{union.name}.hh...")
    with open(f"unions/{union.name}.hh", "a") as union_file:

        union_file.write(f"class {union.name} {{")

        for field in union.fields:
            if field.is_function():
                print(f"Aliasing {field.ty} to '{field.field_type()}'")
                union_file.write(f"using m_{field.name}_t = {field.ty};")

        for field in union.fields:
            union_file.write(f"{field.field_type()} m_{field.name}")
            if field.is_pointer():
                union_file.write(" = nullptr")
            else:
                union_file.write("{}")
            union_file.write(";")

        print("Generating discriminant type...")
        union_file.write("enum class D {")
        for field in union.fields:
            union_file.write(f"{underscore(field.name)},")
        union_file.write("undefined")
        union_file.write("};")
        union_file.write("D m_d = D::undefined;")

        union_file.write("\n\npublic:")
        print("Generating constructors...")
        union_file.write(f"constexpr {union.name}()=default;\n")
        for field in union.fields:
            union_file.write(
                "// NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)\n"
            )
            union_file.write(f"constexpr {union.name}(")
            if field.is_function():
                union_file.write(f"m_{field.name}_t {field.name}")
            elif field.is_pointer():
                union_file.write(f"{field.ty} {field.name}")
            else:
                union_file.write(f"{field.ty} {field.name}")
            union_file.write(
                f"): m_{field.name}({field.name}), m_d(D::{underscore(field.name)}) {{}}"
            )
            union_file.write(f"// ctor({field.field_type()})\n")
        print("Generating type-specific members...")
        for field in union.fields:
            union_file.write(
                f"[[nodiscard]] constexpr bool is{field.name.title()}() {{"
            )
            union_file.write(f"return m_d == D::{underscore(field.name)};")
            union_file.write(f"}} // fn is{field.name}\n")
            if not field.is_pointer():
                union_file.write(
                    f"[[nodiscard]] constexpr const {field.field_type()} ")
                union_file.write("&")
                union_file.write(f"{field.name}() const {{")
                union_file.write(
                    f"if (m_d == D::{underscore(field.name)}) {{ return m_{field.name}; }}"
                )
                union_file.write(f"throw std::runtime_error{{\"in '{union.name}.hh':")
                union_file.write(f" This {union.name} is not a '{field.field_type()}'")
                if isinstance(field.ty, FunctionType):
                    union_file.write(f" (a.k.a '{field.ty}')")
                union_file.write('"};')
                union_file.write(f"}} // fn {field.name} const\n")
            union_file.write(
                f"[[nodiscard]] constexpr {field.field_type()} ")
            if not field.is_pointer():
                union_file.write("&")
            union_file.write(f"{field.name}() {{")
            union_file.write(
                f"if (m_d == D::{underscore(field.name)}) {{ return m_{field.name}; }}"
            )
            union_file.write(f"throw std::runtime_error{{\"in '{union.name}.hh':")
            union_file.write(f" This {union.name} is not a '{field.field_type()}'")
            if isinstance(field.ty, FunctionType):
                union_file.write(f" (a.k.a '{field.ty}')")
            union_file.write('"};')
            union_file.write(f"}} // fn {field.name}\n")

            if field.is_pointer():
                union_file.write(
                    f"[[nodiscard]] constexpr {field.field_type()} reinterpret{field.name.title().replace('_', '')}() const {{"
                )
                union_file.write("switch (m_d) {")
                for f in union.fields:
                    if f == field:
                        union_file.write(f"case D::{underscore(field.name)}:")
                        union_file.write(
                            f"throw std::runtime_error{{\"in '{union.name}.hh': This {union.name}"
                        )
                        union_file.write(f" is already a {field.field_type()}")
                        if isinstance(field.ty, FunctionType):
                            union_file.write(f" (a.k.a. {field.ty})")
                        union_file.write('"};')
                    else:
                        union_file.write(f"case D::{underscore(f.name)}:\n")
                        union_file.write(
                            "// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)\n"
                        )
                        union_file.write(
                            f"return reinterpret_cast<{field.field_type()}>(m_{f.name});"
                        )
                union_file.write("case D::undefined:")
                union_file.write(
                    f"throw std::runtime_error{{\"in '{union.name}.hh': This {union.name} is undefined\"}};"
                )
                union_file.write("} // switch (m_d)\n")
                union_file.write("return nullptr;// unreachable\n")
                union_file.write(f"}} // fn reinterpret{field.name.title()}\n")

            union_file.write(f"void set{field.name.title()}() {{")
            union_file.write(f"m_d = D::{underscore(field.name)};")
            union_file.write(f"}} // set{field.name.title()}\n")

        print("Generating universal members...")

        union_file.write("[[nodiscard]] constexpr bool isNull() const {")
        union_file.write("return m_d == D::undefined;")
        union_file.write("} // fn isNull\n")

        union_file.write("[[nodiscard]] constexpr bool notNull() const {")
        union_file.write("return m_d != D::undefined;")
        union_file.write("} // fn notNull\n")

        union_file.write(
            f"[[nodiscard]] constexpr bool operator==(const {union.name} &other) const {{"
        )
        union_file.write("switch (m_d) {")
        for field in union.fields:
            union_file.write(f"case D::{underscore(field.name)}:")
            union_file.write(
                f"return m_d == other.m_d && m_{field.name} == other.m_{field.name};"
            )
        union_file.write(f"case D::undefined:return other.m_d == D::undefined;")
        union_file.write("} // switch (m_d)\n")
        union_file.write("return false;// unreachable\n")
        union_file.write("} // fn operator==\n")

        union_file.write(
            f"[[nodiscard]] constexpr bool operator!=(const {union.name} &other) const {{"
        )
        union_file.write("return !(*this == other);")
        union_file.write("} // fn operator!=\n")

        union_file.write("};")
        print(f"Wrapping up unions/{union.name}.hh")


def write_include(name, include):
    with open(f"unions/{name}.hh", "a") as union_file:
        union_file.write(f'#include "{include}.hh"\n')


def write_system_include(name, include):
    with open(f"unions/{name}.hh", "a") as union_file:
        union_file.write(f"#include {include}\n")


def write_pre_declaration(union, name):
    with open(f"unions/{union}.hh", "a") as union_file:
        union_file.write(f"struct {name};")


def write_namespace(union, namespace):
    with open(f"unions/{union}.hh", "a") as union_file:
        union_file.write(f"namespace {namespace} {{")


def finish_namespace(union, namespace):
    with open(f"unions/{union.name}.hh", "a") as union_file:
        union_file.write(f"}} // namespace {namespace}\n")


if __name__ == "__main__":
    with open("unions.data") as unions_data:
        lines = unions_data.readlines()

    if exists("unions"):
        for f in listdir("unions"):
            remove(f"unions/{f}")
        rmdir("unions")

    mkdir("unions")

    state = State.Name
    union = Union()
    field = UnionField()
    fn = FunctionType()
    words = []
    while True:
        if len(words) == 0:
            print("Grabbing next line...")
            if len(lines) == 0:
                print("No more lines.")
                break
            line = lines.pop(0)
            words = list(map(lambda w: w.strip(), line.split()))
            print(f"Words: {words}")
        try:
            word = words.pop(0)
        except IndexError:
            continue
        if state == State.Name:
            union.reset()
            union.name = word
            print(f"Union: '{word}'")
            with open(f"unions/{union.name}.hh", "w") as union_file:
                union_file.write(f"#pragma once\n")
                for include in SYSTEM_INCLUDES:
                    union_file.write(f"#include <{include}>\n")
            state = State.OpenBrace
        elif state == State.OpenBrace:
            if word != "{":
                raise ValueError(f"expected '{{', got '{word}'")
            state = State.Includes
        elif state == State.Includes:
            if not word.startswith("#"):
                raise ValueError(f"expected '#', got '{word[0]}'")
            print("Required includes:")
            if len(word) == 1:
                print("None")
            else:
                for include in word[1:].split(","):
                    if include[0] == "<" and include[-1] == ">":
                        write_system_include(union.name, include)
                    else:
                        write_include(union.name, include)
                    print(f'"{include}"')
            state = State.PreDeclarations
        elif state == State.PreDeclarations:
            if not word.startswith("@"):
                raise ValueError(f"expected '@', got {word[0]}")
            if len(word) != 1:
                for pre_declaration in word[1:].split(","):
                    write_pre_declaration(union.name, pre_declaration)
            state = State.Namespace
        elif state == State.Namespace:
            if not word.startswith(":"):
                raise ValueError(f"expected ':', got {word[0]}")
            if len(word) != 1:
                namespace = word[1:]
                write_namespace(union.name, namespace)
            state = State.TypeStart
        elif state == State.TypeStart:
            field = UnionField()
            if word == "fn":
                fn = FunctionType()
                state = State.FnOpenParen
            elif word == "}":
                print(f"{str(union)}")
                generate(union)
                if namespace is not None:
                    finish_namespace(union, namespace)
                namespace = None
                run(["clang-format", "-i", f"unions/{union.name}.hh"])
                state = State.Name
            else:
                id = words.pop()
                field.ty = " ".join(w for sl in [[word], words] for w in sl)
                words = [id]
                print(f"Field type is '{field.ty}'")
                state = State.FieldName
        elif state == State.FnOpenParen:
            if word != "(":
                raise ValueError(f"expected '(', got '{word}'")
            state = State.FnArg
        elif state == State.FnArg:
            if word == ")":
                state = State.FnArrow
            else:
                fn.args.append(word)
        elif state == State.FnArrow:
            if word != ">":
                raise ValueError(f"expected '>', got '{word}'")
            state = State.FnReturnType
        elif state == State.FnReturnType:
            fn.return_type = word
            field.ty = fn
            print(f"Field type is '{fn.return_type}(*)({','.join(fn.args)})'")
            state = State.FieldName
        elif state == State.FieldName:
            field.name = word
            print(f"Field name is 'm_{field.name}'")
            union.fields.append(field)
            print(f"Final field: {union.fields[-1]}")
            state = State.TypeStart
