from dataclasses import dataclass
from os import mkdir, listdir, remove
from os.path import exists
from subprocess import run
from typing import List
from enum import Enum


@dataclass
class SmartEnum:
    name: str
    kind: str
    sequential_variants: List[str]
    valued_variants: List[List[str]]


def generate(e):
    print(f"Generating enums/{e.name}.hh")
    with open(f"enums/{e.name}.hh", "w") as f:
        f.write("#pragma once\n")
        f.write("#include <cstdint>\n")
        f.write('#include "../smart_enum.hh"\n')
        f.write(f"namespace {e.name} {{")
        f.write(f"class Type final : public SmartEnum<{e.kind}, Type> {{")
        f.write("public:")
        f.write(
            f"explicit constexpr Type({e.kind} value) : SmartEnum<{e.kind}, Type>(value) {{}}"
        )
        f.write(f"constexpr Type(SmartEnum<{e.kind}, Type> value) : SmartEnum<{e.kind}, Type>(value.value()) {{}}")
        f.write("};")

        for i, variant in enumerate(e.sequential_variants, start=0):
            f.write(f"constexpr Type {variant}{{{i}}};")
        last_value = "-1"
        for variant, value in e.valued_variants:
            if value is None:
                value = str(int(last_value) + 1)
            f.write(f"constexpr Type {variant}{{{value}}};")
            last_value = value

        f.write("}")
    run(["clang-format", "-i", f"enums/{e.name}.hh"])


def match(data, i, token):
    if data[i] != token:
        raise ValueError(f"expected '{token}', have '{data[i]}'")


if __name__ == "__main__":
    if not exists("enums"):
        mkdir("enums")
    for p in listdir("enums"):
        print(f"Removing enums/{p}")
        remove(f"enums/{p}")
    with open("enums.data") as f:
        data = f.read().split()
    class State(Enum):
        Name = 0
        Kind = 1
        OpenBrace = 2
        CloseBraceOrVariant = 3
        EqualsOrNextVariant = 4
        Value = 5
    state = State.Name
    i = 0
    e = SmartEnum("error", "error", [], [])
    from_file = []
    while i < len(data):
        if state == State.Name:
            e.name = data[i]
            e.kind = "error"
            e.sequential_variants = []
            e.valued_variants = []
            i += 1
            state = State.Kind
        elif state == State.Kind:
            e.kind = data[i]
            i += 1
            state = State.OpenBrace
        elif state == State.OpenBrace:
            match(data, i, "{")
            i += 1
            state = State.CloseBraceOrVariant
        elif state == State.CloseBraceOrVariant:
            if data[i] == "}":
                i += 1
                state = State.Name
                generate(e)
            else:
                e.valued_variants.append([data[i], None])
                i += 1
                state = State.EqualsOrNextVariant
        elif state == State.EqualsOrNextVariant:
            if data[i] == "=":
                i += 1
                state = State.Value
            else:
                state = State.CloseBraceOrVariant
        elif state == State.Value:
            e.valued_variants[-1][1] = data[i]
            i += 1
            state = State.CloseBraceOrVariant
