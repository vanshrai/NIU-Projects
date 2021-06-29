#! /usr/bin/bash 

# Name: Vansh Rai
# Class: CSCI 330
# Assignment 6

filename=$1
fileheader=""
func=$2
line=$4
third=$3
r2=$5
r2=$((r2+1))
line=$((line+1))
a=("${@:3}") #Stores all the value after the second arg in an array.
name=${a[@]} 
function new () {
    if [ -z "$name" ]; then
        fileheader="Untitled database"
    else
        fileheader="$name"
    fi
    touch "$filename"
    echo $fileheader >> $filename  
    echo "New database created"
}

function add () {
    if [ -z "$name" ]; then
        echo "Please enter a valid input" #
        return 1
    fi
    name=${name// /, } #Adding commas
    echo $name >> $filename    
    echo "Successfully added a record to the database"
}

function show () {
    if [ "$third" == "all" ]; then
        awk '{ print }' $filename
    elif [ "$third" == "single" ]; then #Using sed to print a single line.
        sed "$line!d" $filename 
    elif [ "$third" == "range" ]; then
        awk '$line<=NR && NR <=$r2' $filename
   fi
}

function delete () {
    if [ "$third" == "all" ]; then 
        sed -n 1p $filename > temp #Deletes all contents.
		mv temp $filename
    elif [ "$third" == "single" ]; then
        echo "1 record deleted"
		sed "$line""d" $filename > tmp
		mv tmp $filename
    fi   
}
function count () {
    n=$(wc -l < "$filename") #Storing the number of lines in a var
    n="$(($n-1))" #Subtracting one becuase we don't want the header.
    echo "$n"    
}

#Calling functions
if [ "$func" == "new" ]; then
    new
elif [ "$func" == "add" ]; then
    add 
elif [ "$func" == "show" ]; then
    show 
elif [ "$func" == "delete" ]; then
    delete
elif [ "$func" == "count" ]; then
    count
fi