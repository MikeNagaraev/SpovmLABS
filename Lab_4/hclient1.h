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
#include <iostream>

using namespace std;

void menu();
void getMenu(string[]);
#define NAMEDPIPE_NAME "/tmp/server1"
#define BUF_SIZE 1024
#define START "Start"
#define STOP "Stop"

