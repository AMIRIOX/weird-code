# weird-code

[English](README-en.md) | [Chinese]()

收录一些奇奇怪怪的代码,当然大多数都是非标准的,所以请不要开`-Werror`之类的编译选项

## 测试代码

未注明测试环境的代码默认在`clang++ 10.0.0`下测试.

`configure`文件语法：

```bash
$ cd code
$ ./configure g++ g++ *.cpp "-std=c++11 -o"
# configure后紧跟的g++是编译configure.cpp的C++编译器，不可或缺，否则会出语法错误。
# 然后将会自动创建文件夹bin并输出编译后执行的结果（注意双引号和通配符还有不可或缺的-o）
# 注意没有-o不行（保持不同编译器间的兼容）
# 注意：为了保持兼容，configure文件后要紧跟C++编译器。
# 可以使用默认的文件进行快速编译：
$ ./configure g++ auto windows g++（任何你喜欢的编译器） "-std=c++11 -o"（任何你喜欢的编译器命令行参数）
$ ./configure g++ auto linux g++（任何你喜欢的编译器） "-std=c++11 -o"（任何你喜欢的编译器命令行参数）
$ ./configure g++ auto compatible g++（任何你喜欢的编译器） "-std=c++11 -o"（任何你喜欢的编译器命令行参数）
$ ./configure g++ auto ioccc g++（任何你喜欢的编译器） "-std=c++11 -o"（任何你喜欢的编译器命令行参数）
$ ../AutoCompile.bat (Windows)
$ ../AutoCompile.sh (Linux)
```

**理论上任何编译器都能兼容。**

如果您对代码有疑问, 请联系[wumingyun2120@outlook.com](mailto:wumingyun2120@outlook.com)

## 为本仓库提交pull request

欢迎您fork本仓库并提交pull request, 您可以为本仓库提交"标准未定义的`UB`但是**很有趣**的代码"或"恶意代码"
语言包括但不限于rust, C++, C, Python, Shell.

在提交pull request之前,请注意:

* 文件以全英文命名,单词用`-`分割
* 文件开头可以标注作者和联系方式
* 由于是标准UB的代码,请在文件开头标注您的测试环境,如`clang++10.0.0 | macOS 10.14`
* 如果是恶意代码,请在文件开头标注`dangerous`,并注明可能的后果
* 如果是只能在某些操作系统平台运行的,请在文件开头标注`XXX-only`如`Windows-Only`

感谢您的贡献!
