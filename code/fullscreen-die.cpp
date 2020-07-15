#include<windows.h>
#include<cstdio>
#include<iostream>
#include<conio.h>
using namespace std;
HWND hwnd=GetForegroundWindow();
int main(){
	ShowWindow(hwnd,SW_MAXIMIZE);
  EnableMenuItem(hwnd, SC_CLOSE, MF_GRAYED);
  //TODO:添加你的整人代码，让人关不掉（比如播放尴尬的音乐）
	return 0;
}
