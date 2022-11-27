#!/bin/bash

for dir in ./server ./client ./tests
do
    echo "Building "$dir
    cd $dir
    ./build.sh
    cd ..
done

./bin/Tests
