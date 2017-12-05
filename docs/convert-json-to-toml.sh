#!/bin/bash

# ./convert-json-to-toml.sh Assessments/dreams.json Dreams dreams
# $1 input file
# $2 Old name
# $3 new name

cat $1 | sed -e '/^{$/ d' | sed -e '/^}$/ d' | sed -e '/  \]/ d' | \
    sed -e "s/.*\"${2}\": \[$/\[${3}\]/g" | sed -e 's/",$/"/g' | \
    sed -e "s/^        \"/    \[\[${3}.question\]\]\n        question = \"/g"
