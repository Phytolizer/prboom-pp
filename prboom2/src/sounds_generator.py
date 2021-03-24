from re import match
from subprocess import run

if __name__ == "__main__":
    with open("sounds.cc.in") as f:
        contents = f.readlines()
    output = []
    line = 0
    array_index = 0
    while line < len(contents):
        if contents[line].startswith("%%literal"):
            line += 1
            while not contents[line].startswith("%%endliteral"):
                output.append(contents[line])
                line += 1
            line += 1
        else:
            if contents[line].strip().startswith("{"):
                array_index += 1
            elif contents[line].strip().startswith("["):
                m = match(r"\[(\d+)\]\s*=\s*(.*)", contents[line].strip())
                i = int(m.group(1))
                if i > array_index + 1:
                    for _ in range(array_index, i):
                        output.append("{{}, false, 0, nullptr, -1, -1, nullptr},\n")
                array_index = i
                contents[line] = m.group(2) + "\n"
            output.append(contents[line])
            line += 1
    with open("sounds.cc", "w") as f:
        f.writelines(output)
    run(["clang-format", "-i", "sounds.cc"])
