#!/bin/bash

max_hashes=${1:-2}

if ! [[ "$max_hashes" =~ ^[0-9]+$ ]] || [ "$max_hashes" -eq 0 ]; then
  echo "Usage: $0 [positive_integer]"
  exit 1
fi

cat arch.md | grep -E "^[[:space:]]*#{1,$max_hashes} " > a.md

