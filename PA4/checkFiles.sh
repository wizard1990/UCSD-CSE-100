#!/bin/bash

dir="/home/linux/ieng6/cs100e/public"

if [ $# -ne 1 ]; then
    echo "Usage: checkFiles PA#"
    echo "   ex: ./checkFiles PA3"
    echo "Supports PA3 PA4"
    exit 0
fi

file="${dir}/${1}_files"

if [ ! -f "${file}" ]; then
    echo "$1 Not supported!"
    echo "Supports PA3 PA4"
    exit 1
fi

while read line; do
    [ ! -f "${line}" ] && echo "Missing! - ${line}" && missing="true"
done < "${file}"

[ "${missing}" == "true" ] || echo "All files accounted for!"

