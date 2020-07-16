# weird-code

[English](README-en.md) | [Chinese]()

收录一些奇奇怪怪的代码,当然大多数都是非标准的,所以请不要开`-Werror`之类的编译选项

## 测试代码

未注明测试环境的代码默认在`clang++ 10.0.0`下测试.

```bash
$ clang++ {filename}.cpp -o {exename}.exe
% clang++ {filename}.cpp -o {exename}.exe
> clang++ {filename}.cpp -o {exename}.exe
./{exename}.exe
```

如果您觉得上面的~~玩意~~有些麻烦, ~~确实很他妈麻烦~~,您可以通过`code`文件夹下的`configure`文件进行编译。

```bash
$ cd code
$ chmod 777 configure
$ ./configure g++ *.cpp "--std=c++11 -o"
$ cd ..
$ ./AutoCompile.sh
# 然后将会自动创建文件夹bin并输出编译后执行的结果（注意双引号和通配符还有不可或缺的-o）
# 这行表示使用g++编译器编译所有cpp文件，扩展：g++ --std=c++11 -o xxx.cpp
# 注意没有-o不行（保持不同编译器间的兼容）
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
