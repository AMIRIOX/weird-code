# If the tests folder does not exist, create it.
if [ ! -d "../tests" ]; then
  mkdir ../tests
fi

# Intercept file name without suffix
filename=$(echo $1 | cut -d . -f1)
# echo $filename

# Check the compiler and compile
if command -v clang++ >/dev/null 2>&1; then 
  clang++ $1 -o ../tests/$filename.exe 
else 
    echo -e 'no exists clang, check gcc...\n' 
    if command -v g++ >/dev/null 2>&1; then 
      g++ $1 -o ../tests/$filename.exe 
    else 
        echo 'no exists compiler'
	exit
    fi
fi
../tests/$filename.exe
