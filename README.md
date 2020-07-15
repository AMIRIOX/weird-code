# weird-code

[English](README-en.md) | [Chinese]()

收录一些奇奇怪怪的代码,当然大多数都是非标准的,所以请不要开`-Werror`之类的编译选项

一切代码在`clang++ 10.0.0`下测试, 

```bash
$ clang++ {filename}.cpp -o {exename}.exe
% clang++ {filename}.cpp -o {exename}.exe
> clang++ {filename}.cpp -o {exename}.exe

./{exename}.exe
```

如果您觉得上面的~~玩意~~有些麻烦, ~~确实很他妈麻烦~~,您可以通过`code`文件夹下的`cmpl.sh`进行编译,前提是您具有`clang++`或`g++`二者之一

```bash
$ cd code
$ cmpl {filename}.cpp
# 然后将会自动创建文件夹tests并输出编译后执行的结果
```

如果您对代码有疑问, 请联系[wumingyun2120@outlook.com](mailto:wumingyun2120@outlook.com)

欢迎您fork本仓库并提交pull request!

感谢您的贡献!