#!/bin/bash
echo "Welcome!"

echo -n "Enter FileName and press [ENTER]: "
read f_name
echo $f_name

# read -p "Enter file_name and press [ENTER]: " f_name
# read -p "Continue? (Y/N): " confirm && [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]] || exit 1

echo "Copying input_file to working_file..."
cp $f_name ip.bin

echo "Compiling the Code..."
gcc main.c

echo "Running the Program..."
./a.out ip.bin

echo "Removing working_file..."
rm ip.bin

echo "Done!"
