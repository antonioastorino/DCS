#!/bin/bash
curr_dir="`pwd`/`dirname $0`"
cd "$curr_dir"/
n=""
o="0"
[ "$1" != "" ] && n="$1"
[ "$2" != "" ] && o="$2"

filename="../gui/logic-analyzer/data/prj-n$n.log"

./prj-build-run.sh "$n" "$o" | tee $filename
if ! [ -s $filename ]; then
	rm $filename
fi