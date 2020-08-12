#!/bin/bash
function read_dir(){
    for file in `ls $1`; do
        if [ -d $1"/"$file ]; then
            read_dir $1"/"$file
        else
            while [ $? -eq 1 ]; do
                ./cmpl.sh $1"/"$file
            done
            if [ $? -eq 2 ]; then echo "Cannot get update. Are you running on git bash?" >&2; exit 1; fi
        fi
    done
} 
# Check C++ file directory
if [ ! -d "../bin/cpp" ]; then
	mkdir ../bin/cpp
fi
cp ./music ./bin/cpp/
read_dir .
exit $?