#include <bits/stdc++.h>
using namespace std;
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
    bool flag=false;
    if(!strcmp(argv[1],"auto")){
        if(!strcmp(argv[2],"windows")){
            listFile.open("windows.list");
        }
        else if(!strcmp(argv[3],"linux")){
            listFile.open("linux.list");
        }
        else{
            listFile.open("compatible.list");
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
#ifdef linux
                autocompile<<"# Configure Script: Outputing the source code: "<<stri<<endl;
#else
                autocompile<<"rem Configure Script: Outputing the source code: "<<stri<<endl;
#endif
                autocompile<<compiler<<" "<<stri<<" "<<commandline<<" ../bin/"<<stri<<" || { echo \"Compile Error! Please go to github and submit a issue.\";exit $? }"<<endl;
            }
        }else{
            while(listFile>>stri){
#ifdef linux
                autocompile<<"# Configure Script: Outputing the source code: "<<i<<endl;
#else
                autocompile<<"rem Configure Script: Outputing the source code: "<<i<<endl;
#endif
                autocompile<<compiler<<" "<<stri<<" "<<commandline<<" ../bin/"<<stri<<" || { echo \"Compile Error! Please go to github and submit a issue.\";exit $? }"<<endl;
            }
        }
    }
    return 0;
}
