#!/usr/bin/python3

from markdown_pdf import MarkdownPdf, Section

pdf = MarkdownPdf(toc_level=4, optimize=True)

for fname in [
    # "INTRODUCTION.md",
    # "CHAPTER-1.md",
    # "CHAPTER-2.md",
    "CHAPTER-3.md",
    "ch4.md",
    "conclusion.md",
]:
    with open(fname) as f:
        print(f"adding {fname}")
        pdf.add_section(Section(f.read()))
pdf.meta["title"] = "diploma"
print("saving as diploma.pdf")
pdf.save("diploma.pdf")
