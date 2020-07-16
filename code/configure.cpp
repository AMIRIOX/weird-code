#include <bits/stdc++/h>
using namespace std;
int main(int argc,char** argv){
#ifdef linux
    ostream autocompile("../AutoCompile.sh ");
    system("chmod 777 ./AutoCompile.sh");
    autocompile<<"#!/bin/bash"<<endl<<"# Configure Script: Hello world!"<<endl;
#else
    ostream autocompile("../AutoCompile.bat");
    autocompile<<"@echo off"<<endl<<"rem Configure Script: Hello world!"<<endl;
#endif
    if(argc%3!=1){
        bool first_time=true,a_time=false;
        string compiler,files,commandline,i;
        while(true){
            cin>>compiler>>files;
            while(true){
                cin>>i;
                if((i.find("\"")==i.npos&&first_time==true)||(i.find("\"")!=i.npos&&a_time==true)) {commandline+=i;break;}
                else if(i.find("\"")!=i.npos&&a_time==false) a_time=true;
                commandline+=i;
                first_time=false;
            }
#ifdef linux
                autocompile<<"# Configure Script: Outputing the source code: "<<i<<endl;
#else
                autocompile<<"rem Configure Script: Outputing the source code: "<<i<<endl;
#endif
                autocompile<<compiler<<" "<<i<<" "<<commandline<<" ../bin/"<<i<<" || { echo \"Compile Error! Please go to github and submit a issue.\";exit $? }"<<endl;
            }
            return 0;
        }
    }
    for(int i=1;i<argc;i+=3){
        string compiler=argv[i];
        string files=argv[i+1];
        string commandline=argv[i+2];
        string i;
        while(sscanf(files.c_str(),"%s",i)!=0){
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
