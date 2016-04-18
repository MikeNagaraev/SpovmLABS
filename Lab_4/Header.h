#pragma once
#ifdef _MSC_VER
#include <conio.h>
#include <windows.h>
#include <list>
#include <iterator>
#include <string>

#else
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/wait.h>  
#include <unistd.h>    
#include <string.h>  
#include <stdlib.h>

#endif
#include <stdio.h>
#include <iostream>
using namespace std;

#ifdef _MSC_VER
void MainProcess(char*);
void MenuProcess();
void menu();
void getMenu(string s[]);
DWORD WINAPI funcPrint_1(LPVOID );
DWORD WINAPI funcPrint_2(LPVOID);
DWORD WINAPI funcPrint_3(LPVOID);
#define CHAT_PROCESS 2
#define START "Start"
#define STOP "Stop"
#define PATH1 "E:\\1\\*"
#define PATH2 "E:\\2\\*"
#define PATH3 "E:\\3\\*"
#endif
