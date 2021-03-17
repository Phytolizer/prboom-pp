from enum import Enum, auto
from os import mkdir, rmdir, remove, listdir
from os.path import exists
from subprocess import run


class State(Enum):
    Name = auto()
    OpenBrace = auto()
    Includes = auto()
    PreDeclarations = auto()
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


class Union:
    def __init__(self):
        self.name = None
        self.fields = []

    def reset(self):
        self.name = None
        self.fields = []

    def __str__(self):
        return f"Union {{ name: {self.name}, fields: {', '.join(map(str, self.fields))} }}"


def generate(union):
    with open(f"unions/{union.name}.hh", "a") as union_file:

        union_file.write(f"class {union.name} {{")

        for field in union.fields:
            if isinstance(field.ty, FunctionType):
                union_file.write(f"using m_{field.name}_t = {field.ty};")

        for field in union.fields:
            union_file.write(f"{field.field_type()} m_{field.name}")
            if isinstance(field.ty, FunctionType) or '*' in field.ty:
                union_file.write(" = nullptr")
            union_file.write(";")

        union_file.write("enum class D {")
        for field in union.fields:
            union_file.write(f"{field.name},")
        union_file.write("undefined")
        union_file.write("} m_d = D::undefined;")

        union_file.write("public:")
        union_file.write(f"constexpr {union.name}()=default;")
        for field in union.fields:
            union_file.write(f"constexpr {union.name}(")
            if isinstance(field.ty, FunctionType):
                union_file.write(f"m_{field.name}_t {field.name}")
            else:
                union_file.write(f"{field.ty} {field.name}")
            union_file.write(f"): m_{field.name}({field.name}), m_d(D::{field.name}) {{}}")
        for field in union.fields:
            union_file.write(f"{field.field_type()} {field.name}() {{")
            union_file.write("switch (m_d) {")
            for f in union.fields:
                union_file.write(f"case D::{f.name}:")
                if f == field:
                    union_file.write(f"return m_{f.name};")
                else:
                    # FIXME is this ok?
                    union_file.write(f"return reinterpret_cast<{field.field_type()}>(m_{f.name});")
            union_file.write("case D::undefined:return nullptr;")
            union_file.write("}")
            union_file.write("}")

        union_file.write("constexpr bool isNull() const {")
        union_file.write("return m_d == D::undefined;")
        union_file.write("}")

        union_file.write("constexpr bool notNull() const {")
        union_file.write("return m_d != D::undefined;")
        union_file.write("}")

        union_file.write(f"constexpr bool operator==(const {union.name} &other) const {{")
        union_file.write("switch (m_d) {")
        for field in union.fields:
            union_file.write(f"case D::{field.name}:")
            union_file.write(f"return m_d == other.m_d && m_{field.name} == other.m_{field.name};")
        union_file.write(f"case D::undefined:return true;")
        union_file.write("}")
        union_file.write("}")

        union_file.write(f"constexpr bool operator!=(const {union.name} &other) const {{")
        union_file.write("return !(*this == other);")
        union_file.write("}")

        union_file.write("};")
    run(["clang-format", "-i", f"unions/{union.name}.hh"])


def write_include(name, include):
    with open(f"unions/{name}.hh", "a") as union_file:
        union_file.write(f'#include "{include}.hh"\n')


def write_pre_declaration(union, name):
    with open(f"unions/{union}.hh", "a") as union_file:
        union_file.write(f"struct {name};")


if __name__ == '__main__':
    with open("unions.data") as unions_data:
        words = unions_data.read().split()

    if exists("unions"):
        for f in listdir("unions"):
            remove(f"unions/{f}")
        rmdir("unions")

    mkdir("unions")

    state = State.Name
    union = Union()
    field = UnionField()
    fn = FunctionType()
    while True:
        try:
            word = words.pop(0)
        except IndexError:
            break
        if state == State.Name:
            union.reset()
            union.name = word
            print(f"Union: '{word}'")
            with open(f"unions/{union.name}.hh", "w") as union_file:
                union_file.write(f"#pragma once\n")
                union_file.write("#include <cstdint>\n")
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
                    write_include(union.name, include)
                    print(f'"{include}"')
            state = State.PreDeclarations
        elif state == State.PreDeclarations:
            if not word.startswith("@"):
                raise ValueError(f"expected '@', got {word[0]}")
            if len(word) != 1:
                for pre_declaration in word[1:].split(","):
                    write_pre_declaration(union.name, pre_declaration)
            state = State.TypeStart
        elif state == State.TypeStart:
            field = UnionField()
            if word == "fn":
                fn = FunctionType()
                state = State.FnOpenParen
            elif word == "}":
                print(f"{str(union)}")
                generate(union)
                state = State.Name
            else:
                field.ty = word
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