#!/bin/bash

# Check binary file directory
if [ ! -d "../bin" ]; then
  mkdir ../bin
fi

# Define some vars
filename=$(echo $1 | cut -d . -f1) #filename (ONLY name)
suffix="${$1##*.}" # suffix name
cflag="-std=gnuc11 -g -p -lm -O3 -Wall" # C language flags
cxxflag="-std=gnu++11 -g -p -lstdc++ -lm -O3 -Wall" # C++ language flags
asmflag="-f elf32" # asm language flags
pyflag="-F -w" # phpinstaller

# Compile C source code
if [[ ($suffix == "c") ]];then 
	# Check C file directory
	if [ ! -d "../bin/c" ]; then
  		mkdir ../bin/c
	fi
	if command -v gcc >/dev/null 2>&1; then 
		echo "Running Script: gcc $1 -o ../bin/c/$filename.exe $cflag"
      	gcc $1 -o ../bin/c/$filename.exe $cflag
		exit 0
	else 
    	echo 'No gcc found. Try to install it.' >&2
		if command -v apt >/dev/null 2>&1; then
			apt install gcc -y
		else
			yum install gcc -y
		fi 
		if [ $? -eq 0 ]; then exit 1
		else; exit 2; fi
	fi
fi

# Compile C++ source code
if [[ ($suffix == "cpp") || ($suffix == "cxx") || ($suffix == "C") ]];then 
	# Check C++ file directory
	if [ ! -d "../bin/cpp" ]; then
  		mkdir ../bin/cpp
	fi
	if command -v g++ >/dev/null 2>&1; then 
		echo "Running Script: g++ $1 -o ../bin/cpp/$filename.exe $cxxflag"
      	g++ $1 -o ../bin/cpp/$filename.exe $cxxflag
		exit 0
	else 
    	echo 'No g++ found. Try to install it.' >&2
		if command -v apt >/dev/null 2>&1; then
			apt install g++ -y
		else
			yum install g++ -y
		fi 
		if [ $? -eq 0 ]; then exit 1
		else; exit 2; fi
	fi
fi

# Compile ASM source code
if [[ ($suffix == "asm") ]];then 
	# Check C file directory
	if [ ! -d "../bin/asm" ]; then
  		mkdir ../bin/asm
	fi
	if command -v nasm >/dev/null 2>&1; then 
		echo "Running Script: nasm $1 -o ../bin/asm/$filename.exe $cxxflag > /dev/null"
      	nasm $1 -o ../bin/asm/$filename.exe $asmflag > /dev/null
		exit 0
	else 
    	echo 'No nasm found. Try to install it.' >&2
		if command -v apt >/dev/null 2>&1; then
			apt install nasm -y
		else
			yum install nasm -y
		fi 
		if [ $? -eq 0 ]; then exit 1
		else; exit 2; fi
	fi
fi

# Compile Bash Script code
if [[ ($suffix == "sh") ]];then 
	if [ ! -d "../bin/bash" ]; then
  		mkdir ../bin/bash
	fi
	echo "Running Script: cp -f $1 ../bin/bash/"
	cp -f $1 ../bin/bash/
	exit 0
fi

# Compile Batch Script code
if [[ ($suffix == "bat") ]];then 
	if [ ! -d "../bin/bat" ]; then
  		mkdir ../bin/bat
	fi
	echo "Running Script: cp -f $1 ../bin/bat/"
	cp -f $1 ../bin/bat/
	exit 0
fi

# Compile C++ source code
if [[ ($suffix == "py") ]];then 
	# Check C++ file directory
	if [ ! -d "../bin/py" ]; then
  		mkdir ../bin/py
	fi
	if command -v pip >/dev/null 2>&1; then 
		echo "Running Script: pip install pyinstaller"
      	pip install pyinstaller
		echo "Running Script: phpinstaller $pyflag $1"
		phpinstaller $pyflag $1
		echo "Running Script: cp -f dist/* ../bin/py/"
		cp -f dist/* ../bin/py/
		echo "Running Script: rm -rf dist"
		rm -rf dist
		exit 0
	else 
    	echo 'No pip found. Try to install it.' >&2
		if command -v apt >/dev/null 2>&1; then
			apt install pip -y
		else
			yum install pip -y
		fi 
		if [ $? -eq 0 ]; then exit 1
		else; exit 2; fi
	fi
fi

echo "Skiping file: $1" >&2
exit 3