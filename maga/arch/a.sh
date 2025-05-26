#!/bin/bash

max_hashes=${1:-2}

function arch() {
  if ! [[ "$max_hashes" =~ ^[0-9]+$ ]] || [ "$max_hashes" -eq 0 ]; then
    echo "Usage: $0 [positive_integer]"
    exit 1
  fi
  cat $1 | grep -E "^[[:space:]]*#{1,$max_hashes} "
}

arch ch1.md > arch/a.md
arch ch2.md >> arch/a.md
arch ch3.md >> arch/a.md
arch ch4.md >> arch/a.md
arch conclusion.md >> arch/a.md

