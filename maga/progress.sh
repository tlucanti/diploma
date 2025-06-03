#!/bin/zsh

if [ -z "$1" ]; then
	echo "expected argument";
	exit 1
fi

TOTAL=$(cat ./structure.md | grep '##' | wc -l)
CURRENT=$(cat ./structure.md | grep '##' | grep -n "$1" | awk '{print $1}' | tr -d ':')
PERCENT="$((${CURRENT}.0 / ${TOTAL}.0 * 100))"

printf "$CURRENT / $TOTAL: %.1f\n" "$PERCENT"
