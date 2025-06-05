#!/bin/bash

source ./arch/a.sh

function frag() {
	cat $2
	cat $1 | tail -n +$3
}

if [ -z "$1" ]; then
	echo "expected argument" >&2
	exit 1;
fi

arch ./ch1.md 4 > structure.md
arch ./ch2.md 4 >> structure.md
#cat ./CHAPTER-2.md >> structure.md
#frag ./ch3.md ./CHAPTER-3.md $1 >> structure.md
arch ./CHAPTER-3.md 4 >> structure.md
frag ./ch4.md ./CHAPTER-4.md $1 >> structure.md
