#include <bits/stdc++.h>
using namespace std;
void outputSource(ofstream& autocompile,string filename,string compiler,string commandline) {
#ifdef linux
    autocompile << "# Configure Script: Outputing the source code: " << filename << endl;
    autocompile << compiler << " " << filename << " " << commandline << " ../bin/" << filename << " || { echo \"Compile Error! Please go to github and submit a issue.\";exit $? }" << endl;
#else
    autocompile << "rem Configure Script: Outputing the source code: " << filename << endl;
    autocompile << compiler << " " << filename << " " << commandline << " ../bin/" << filename << " || { echo \"Compile Error! Please go to github and submit a issue.\";exit %errorlevel% }" << endl;
#endif
}
int main(int argc,char** argv){
#ifdef linux
    ofstream autocompile("../AutoCompile.sh ");
    system("chmod 777 ./AutoCompile.sh");
    autocompile<<"#!/bin/bash"<<endl<<"# Configure Script: Hello world!"<<endl;
#else
    ofstream autocompile("../AutoCompile.bat");
    autocompile<<"@echo off"<<endl<<"rem Configure Script: Hello world!"<<endl;
#endif
    ifstream listFile;
    bool flag = false,comflag=false;
    vector<string> files;
    if(!strcmp(argv[1],"auto")){
        if(!strcmp(argv[2],"windows")){
            listFile.open("windows.list");
        }
        else if(!strcmp(argv[2],"linux")){
            listFile.open("linux.list");
        }
        else if (!strcmp(argv[2], "ioccc")) {
#ifdef linux
            system("find . -name \" * .c\" > IOCCC.list");
#else
            system("for /r IOCCC %i in (*.c) do @echo %i >> IOCCC.list")
#endif
            listFile.open("IOCCC.list");
        }
        else if(!strcmp(argv[2],"compatible")){
            listFile.open("compatible.list");
            comflag = true;
        }
        else {
            return;
        }
        flag=true;
    }
    for(int i=1;i<argc;i+=3){
        string compiler=argv[i];
        string commandline=argv[i+2];
        string stri;
        stri.resize(8192);
        if(flag==false){
            string files=argv[i+1];
            while(sscanf(files.c_str(),"%s",&stri[0])!=0){
                outputSource(autocompile, stri,compiler,commandline);
            }
        }else{
            while(listFile>>stri){
                outputSource(autocompile, stri, compiler, commandline);
            }
        }
    }
    return 0;
}
