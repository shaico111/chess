import re
import os

def extract_prototypes(src_directory):
    prototypes = []
    function_pattern = re.compile(r"^\s*([a-zA-Z_][a-zA-Z0-9_]*\s+\**[a-zA-Z_][a-zA-Z0-9_]*\s*\([^)]*\))\s*\{", re.MULTILINE)

    for subdir, dirs, files in os.walk(src_directory):
        for file in files:
            if file.endswith(".c"):
                with open(os.path.join(subdir, file), 'r') as file_content:
                    content = file_content.read()
                    functions = function_pattern.findall(content)
                    prototypes.extend(functions)

    return prototypes

def update_prototypes_h(header_path, prototypes):
    header_content = [
        "/* File: prototypes.h\n",
        " * -------------------\n",
        " * This header file includes declarations of all the functions used in the chessboard\n",
        " * project. It provides a central place to see all operations related to chess\n",
        " * game logic and movement.\n",
        " */\n\n",
        "#ifndef PROTOTYPES_H\n",
        "#define PROTOTYPES_H\n\n",
        "#include \"typedefs.h\"  // Include type definitions for function prototypes.\n\n",
        "// Function prototypes\n"
    ]

    prototype_set = set()
    for proto in prototypes:
        if not proto.startswith("int main") and proto + ";" not in prototype_set:
            prototype_set.add(proto + ";")
            header_content.append(proto + ";\n")

    header_content.append("\n#endif // PROTOTYPES_H\n")

    with open(header_path, 'w') as header_file:
        header_file.writelines(header_content)

dirname = os.path.dirname(__file__)
src_dir = os.path.join(dirname, '../src')
header_path = os.path.join(dirname, '../include/prototypes.h')
prototypes = extract_prototypes(src_dir)
update_prototypes_h(header_path, prototypes)
