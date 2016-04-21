#pragma once
#ifdef _MSC_VER
#include <conio.h>
#include <windows.h>
#include <list>
#include <iterator>
#include <string>

#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#endif
#include <stdio.h>
#include <iostream>
using namespace std;
#ifdef _MSC_VER
void MainProcess(char*);
void MenuProcess();
void menu();
void getMenu(string s[]);
DWORD WINAPI funcPrint_1(LPVOID);
DWORD WINAPI funcPrint_2(LPVOID);
DWORD WINAPI funcPrint_3(LPVOID);
#define CHAT_PROCESS 2
#define START "Start"
#define STOP "Stop"
#define PATH1 "E:\\1\\*"
#define PATH2 "E:\\2\\*"
#define PATH3 "E:\\3\\*"
#else
#define BUF_SIZE 1024
#define NAMEDPIPE_NAME "/tmp/server1"
#define PATH1 "/home/mikhail/Progects/a"
#define PATH2 "/home/mikhail/Progects/b"
#define PATH3 "/home/mikhail/Progects/c"
void connection();
void *thread_func1(void *);
void *thread_func2(void *);
void *thread_func3(void *);
#endif
