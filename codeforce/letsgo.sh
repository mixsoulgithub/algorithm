#! /bin/bash
# TODO cmp ans and golden?
# use problem_id_ to record right answer
set -euo pipefail
echo "usage: letsgo PROBLEM_ID"
cp template.cpp $1.cpp
touch $1.data 
sed -i "s/problem_id/$1/g" $1.cpp
code $1.cpp $1.data $1.md