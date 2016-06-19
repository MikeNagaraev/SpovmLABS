#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <cstdio>
#include <fcntl.h>
#endif
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#ifndef _MSC_VER
#define NAMEDPIPE_NAME "/tmp/server"
#endif
#define BUF_SIZE 512
#define COM_LS "ls"
#define COM_EXIT "exit"
#define COM_RMFILE "rm"
#define COM_GETFILE "get"
#define COM_PUTFILE "put"

char buffer[BUF_SIZE];
char readbuffer[BUF_SIZE];
string buf;


void showFiles(char *, string);
void getMenu();
string getCommand(char *);
void Communication();

#ifdef _MSC_VER
HANDLE hNamedPipe;
LPSTR  szPipeName = "\\\\.\\pipe\\$MyPipe$";
DWORD cbWritten;
DWORD cbRead;
#else
int fd, len;
#endif