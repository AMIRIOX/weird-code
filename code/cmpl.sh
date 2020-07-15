# If the tests folder does not exist, create it.
if [ ! -d "../tests" ]; then
  mkdir ../tests
fi

# Intercept file name without suffix
filename=$(echo $1 | cut -d . -f1)
# echo $filename

# get file suffix name
FILE=$1
suffix="${FILE##*.}"
RUST="rust"
CPP="cpp"

if [ $suffix == $CPP ];then 
	# Check the compiler and compile
	if command -v clang++ >/dev/null 2>&1; then 
  		clang++ $(echo $# |sed 's/$0//g') -o ../tests/$filename.exe || exit $?
	else 
    		echo -e 'no exists clang, check gcc...\n' 
    		if command -v g++ >/dev/null 2>&1; then 
      			g++ $(echo $# |sed 's/$0//g') -o ../tests/$filename.exe || exit $?
    		else 
        		echo 'no exists compiler'
			exit 2
	    	fi
	fi
	../tests/$filename.exe
	exit
fi

if [ $suffix == $RUST ];then
	# Check the compiler and compile
	if command -v rustc >/dev/null 2>&1; then
		rustc $(echo $# |sed 's/$0//g') -o ../tests/$filename.exe || exit $?
	else
		echo 'no exists rustc'
	fi
	../tests/$filename.exe
	exit
fi
