#!/bin/bash

cd classes/
files=($(ls | grep -e *.cpp))
elements=${#files[@]}
string="g++"
cd ..

for (( i=0;i<$elements;i++)); do
    
    listfiles="$string classes/${files[${i}]}"
done

command="$listfiles main.cpp -o tetris"
eval $command

