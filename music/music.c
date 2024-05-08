#include<stdio.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")  //需要包含的庫文件

int main(){
    PlaySound(TEXT("music\\boom.wav"), NULL, SND_FILENAME|SND_ASYNC);
    return 0;
}