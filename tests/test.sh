#!/bin/bash
currentScript=$0
countToTest=0

for file in *; do
  if [[ -f "$file" && -x "$file" && "$file" != "$currentScript" ]]; then
    echo "$file:"
    ./$file
    let countToTest=$countToTest+1
  fi
done 

echo "$countToTest"


