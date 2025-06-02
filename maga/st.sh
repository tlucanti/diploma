#!/bin/bash

source ./arch/a.sh

function frag() {
	cat $2
	cat $1 | tail -n +$3
}

if [ -z "$1" ]; then
	echo "expected argument";
	exit 1;
fi

arch ch1.md > structure.md
arch ch2.md >> structure.md
frag ch3.md CHAPTER-3.md $1 >> structure.md
arch ch4.md >> structure.md
