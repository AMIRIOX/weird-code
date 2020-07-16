# weird-code

[English]() | [Chinese](README.md)

Contains some weird codes, of course most of them are non-standard,So please don't open compile options like `-Werror`

## Test Code

Code that does not indicate the test environment is tested by default under `clang++ 10.0.0`.

```bash
$ clang++ {filename}.cpp -o {exename}.exe
% clang++ {filename}.cpp -o {exename}.exe
> clang++ {filename}.cpp -o {exename}.exe

./{exename}.exe
```

If you think the above is a little troublesome, ~~is really fucking troublesome~~,  you can compile through `configure` under the `code` folder.

```bash
$ cd code
$ g++ configure.cpp -std=c++11 -o configure
$ ./configure g++ *.cpp "-std=c++11 -o"
# Then the folder bin will be automatically created 
# It means use g++ make any cpp files. It also means "g++ --std=c++11 -o xxx.cpp"
# WARNING: REMEMBER -O!!!!!!
# But you can also use these to compile the programs.
$ ./configure < windows.list
$ ./configure < linux.list
$ ./configure < compatible.list
# Run this when configure script is ready.
$ ../AutoCompile.bat (Windows)
$ ../AutoCompile.sh (Linux)
```

**`configure` supports any compilers and codes.**

If you have questions about the code, please contact [wumingyun2120@outlook.com](mailto:wumingyun2120@outlook.com)

You are welcome to fork this warehouse and submit a pull request,You can submit "standard undefined `UB` but **interesting** code" or "spoof code" for this repository.
Languages include but not limited to rust, C++, C, Python, Shell.

## Submit pull request for this warehouse

You are welcome to fork this warehouse and submit a pull request, you can submit "Unused standard "UB` but **very interesting** code" or "Malicious code" for this warehouse
Languages include but are not limited to rust, C++, C, Python, Shell.

Before submitting a pull request, please note:

* The file is named in full English, words are separated by `-`
* Author and contact information can be marked at the beginning of the file
* Since it is standard UB code, please mark your test environment at the beginning of the file, such as `clang++10.0.0 | macOS 10.14`
* If it is malicious code, please mark "dangerous" at the beginning of the file and indicate the possible consequences
* If it can only run on certain operating system platforms, please mark XXX-only at the beginning of the file, such as Windows-Only


Thank you for your contribution!

[*] Some Words Translated by [Google Translate](https://translate.google.cn/)
