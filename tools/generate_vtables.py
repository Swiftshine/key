import sys

def generate_vtable(start_hex, end_hex):
    start = int(start_hex, 16)
    end = int(end_hex, 16)

    num_digits = len(end_hex.lstrip("0x").lstrip("X"))

    output = []

    for cur_offset in range(start, end + 4, 4):
        offset_str = hex(cur_offset).upper().replace("0X", "0x")

        formatted_offset = f"/* 0x{offset_str[2:].zfill(num_digits)} */"
        func_name = f"vf{offset_str.replace("0x", '')}();"

        output.append(f"\t{formatted_offset} virtual void {func_name}")

    return "\n".join(output)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} START END")
        sys.exit(1)

    print(generate_vtable(sys.argv[1], sys.argv[2]))