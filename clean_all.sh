#!/bin/bash

for dir in ./server ./client ./tests
do
    echo "Cleaning "$dir
    cd $dir
    rm ./build/* -r > /dev/null 2>&1
    rmdir ./build > /dev/null 2>&1
    cd ..
done

rm ./bin -r > /dev/null 2>&1
