#!/bin/bash

set -o pipefail
set -e

SELF=$(basename $0)
NAME=${1}

help() {
	echo "
Clones the example using a new name

Usage: ${SELF} NAME

       NAME   Name to use for the clone
"
}

error() {
	echo "error: $*" >&2
	help >&2
}

if [ -z "${NAME}" ]; then
	error "missing argument NAME"
fi

git ls-files example | while read src; do
	dest=${src//example/${NAME}}
	mkdir -p $(dirname ${dest})
	cp ${src} ${dest}
	sed -i 's/example/'${NAME}'/g' ${dest}
done

exit 0
