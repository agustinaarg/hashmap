#!/bin/bash

# Directory containing the files
directory="./data"

# Program to execute
program="./build/ContarPalabras"

# Change to the directory
cd "$directory"

# Create an array to store the filenames
filenames=()

# Loop through the files in the directory

# Loop through the files in the directory
for file in *; do
    # Check if the current item is a file
    if [[ -f $file ]]; then
        # Append the filename to the arguments
         filenames+=(./data/$file)
    fi
done
cd ..


# Execute the program with all filenames as arguments
for((j=1; j<=250; j++));do 
    for ((i=1; i<=26; i++)); do 

    "$program" "$i" "$i" "${filenames[@]}"

    done

done
