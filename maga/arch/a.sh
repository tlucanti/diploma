#!/bin/bash

function arch() {
  max_hashes=${2:-2}

  if ! [[ "$max_hashes" =~ ^[0-9]+$ ]] || [ "$max_hashes" -eq 0 ]; then
    echo "Usage: $0 [positive_integer]" >&2
    exit 1
  fi
  cat $1 | grep -E "^[[:space:]]*#{1,$max_hashes} "
}

arch CHAPTER-1.md $1 > arch/a.md
arch CHAPTER-2.md $1 >> arch/a.md
arch CHAPTER-3.md $1 >> arch/a.md
arch CHAPTER-4.md $1 >> arch/a.md

