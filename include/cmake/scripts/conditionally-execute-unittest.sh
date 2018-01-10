#!/bin/sh

UNITTEST=$1

if [ "${EXECUTE_UNITTESTS}" != "1" ]; then
	exit 0
fi

if ! [ -x "${UNITTEST}" ]; then
	echo "error: '${UNITTEST}' is not a valid executable" >&2
	exit 1
fi

if ./${UNITTEST}; then
	exit 0
else
	mv ${UNITTEST} ${UNITTEST}.fails
	exit 1
fi
