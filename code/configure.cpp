#include <bits/stdc++/h>
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
    if(!strcmp(argv[1],"auto")){
        if(!strcmp(argv[2],"windows")){
            ofstream listFile("windows.list");
        }
        else if(!strcmp(argv[3],"linux")){
            ofstream listFile("linux.list");
        }
        else{
            ofstream listFile("compatible.list");
        }
        bool flag=true;
    }
    for(int i=1;i<argc;i+=3){
        string compiler=argv[i];
        string commandline=argv[i+2];
        string i;
        if(flag==false){
            string files=argv[i+1];
            while(sscanf(files.c_str(),"%s",i)!=0){
#ifdef linux
                autocompile<<"# Configure Script: Outputing the source code: "<<i<<endl;
#else
                autocompile<<"rem Configure Script: Outputing the source code: "<<i<<endl;
#endif
                autocompile<<compiler<<" "<<i<<" "<<commandline<<" ../bin/"<<i<<" || { echo \"Compile Error! Please go to github and submit a issue.\";exit $? }"<<endl;
            }
        }else{
            while(listFile>>i){
#ifdef linux
                autocompile<<"# Configure Script: Outputing the source code: "<<i<<endl;
#else
                autocompile<<"rem Configure Script: Outputing the source code: "<<i<<endl;
#endif
                autocompile<<compiler<<" "<<i<<" "<<commandline<<" ../bin/"<<i<<" || { echo \"Compile Error! Please go to github and submit a issue.\";exit $? }"<<endl;
            }
    }
    return 0;
}
