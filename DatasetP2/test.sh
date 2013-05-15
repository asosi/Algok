#!/bin/bash

[ "$#" -eq 2 ] || { echo "Usage: test.sh ./commandtoexecute idtest(0-19)" >&2; exit 1; }

COMMAND=$1
ID=$2
[[ -x $COMMAND ]] || { echo "File $COMMAND is not executable" >&2; exit 1; }
(( ID >= 0 && ID<=19 )) || { echo "ID must be between 0 and 19" >&2; exit 1; } 

cp input/input$ID.txt input.txt

timeout 2.0s time ./$COMMAND || { echo "TIMEOUT!" ; exit 1; }
if ! diff -q output.txt output/output$ID.txt >/dev/null; then
    echo "WRONG ANSWER"
    echo "CORRECT ANSWER: $(cat output/output$ID.txt)"
    echo "YOUR ANSWER: $(cat output.txt)"
else
    echo "CORRECT"
fi
