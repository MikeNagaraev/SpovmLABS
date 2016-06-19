#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#endif
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include "FTPlib.h"

using namespace std;

#ifdef _MSC_VER
#define PUBLIC_DIR "..\\Debug\\public\\*"
#define PUBLIC_FOLDER "..\\Debug\\public\\"
#define CLIENT_FOLDER "..\\Debug\\private\\"
#define FTP_LIB "FTPdll.dll"
#else
#define FTP_LIB "../Debug/FTPdll.so"
#define PUBLIC_FOLDER_UNIX "../Debug/public/"
#define CLIENT_FOLDER_UNIX "../Debug/private/"
#define NAMEDPIPE_NAME "/tmp/server"
#endif
#define BUF_SIZE 512
#define COM_LS "ls"
#define COM_EXIT "exit"
#define COM_RMFILE "rm"
#define COM_GETFILE "get"
#define COM_PUTFILE "put"

string getCommand(char *, int);
void Communication();
char buffer[BUF_SIZE];
char readbuffer[BUF_SIZE];
char GetShortCommand(const char *);

FTPlib ftp(FTP_LIB);

#ifdef _MSC_VER
HANDLE hNamedPipe;
LPSTR  lpszPipeName = "\\\\.\\pipe\\$MyPipe$";
DWORD  cbRead;
DWORD  cbWritten;
#else
int fd, len;
#endif
