#!/bin/bash
currentScript=$(basename "$0")
countToTest=0
countToPass=0

for file in *.; do
  if [[ -f "$file" && -x "$file" && "$file" != "$currentScript" ]]; then
    make $file
  fi
done 


testsToUnPass=()

for file in *; do
  if [[ -f "$file" && -x "$file" && "$file" != "$currentScript" ]]; then
    echo "$file:"
    ./"$file"
    if [[ $? -eq 0 ]]; then
      let countToPass=$countToPass+1
    else 
      testsToUnPass+=("$file")
    fi
    let countToTest=$countToTest+1
  fi
done 


echo "$countToPass/$countToTest"

if [[ countToPass -ne countToTest ]]; then
  echo "unpass tests:"
  for item in ${testsToUnPass[@]}; do
    echo "$item  "
  done
else 
  echo "all tests passed!" 
fi

