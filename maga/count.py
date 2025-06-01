#!/usr/bin/python3

import re
import sys


def process_markdown_file(input_file, output_file=None):
    # Read the markdown file
    with open(input_file, "r", encoding="utf-8") as file:
        content = file.read()

    # Split the content into lines
    lines = content.split("\n")

    # Initialize counters for each level
    counters = [0, 0, 0, 0, 0, 0]  # 0-based for h1-h6
    processed_lines = []

    for line in lines:
        # Capture leading spaces
        leading_spaces_match = re.match(r"^(\s*)", line)
        leading_spaces = leading_spaces_match.group(1) if leading_spaces_match else ""

        # Remove leading spaces for header detection
        stripped_line = line.strip()

        # Check if the stripped line is a header
        header_match = re.match(r"^(#{1,6})\s+(.*)$", stripped_line)
        if header_match:
            level = len(header_match.group(1))
            header_text = header_match.group(2)

            # Remove existing enumeration (like "1.2.3. " or "1. " or "1.1 " etc.)
            header_text = re.sub(r"^\d+(\.\d+)*\.?\s+", "", header_text)

            # Reset counters for deeper levels
            for i in range(level, len(counters)):
                counters[i] = 0

            # Increment counter for current level
            counters[level - 1] += 1

            # Generate the enumeration string
            enum_parts = counters[:level]
            enumeration = ""
            if level != 1:
                enumeration = ".".join(str(num) for num in enum_parts) + ". "

            # Create the new header line with preserved leading spaces
            new_line = leading_spaces + "#" * level + " " + enumeration + header_text
            processed_lines.append(new_line)
        else:
            processed_lines.append(line)

    # Join the processed lines back into content
    processed_content = "\n".join(processed_lines)

    # Write to output file or print to console
    if output_file:
        with open(output_file, "w", encoding="utf-8") as file:
            file.write(processed_content)
        print(f"Processed content written to {output_file}")
    else:
        print(processed_content)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py input_file.md [output_file.md]")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else input_file

    process_markdown_file(input_file, output_file)
