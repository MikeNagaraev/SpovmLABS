#ifdef _MSC_VER
#include <windows.h>
#include <string>

#else
#include <typeinfo>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <err.h>
#include <errno.h>

char global_way_of_dir[50];

 void output()
{
	DIR *d;
	struct dirent *dirr;
	d = opendir(global_way_of_dir);
	if (d)
	{
		cout«"I'm here"«endl;
		while ((dirr = readdir(d)) != NULL)
		{
			printf("%s\n", dirr->d_name);
		}
		sleep(1);
		closedir(d);
	}
}

 void handle(int p)
{
	while (1)
	{
	}
}
 void handle1(int p)
{
	while (1)
	{
		sleep(1);
		output();
	}
}

#endif
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
using namespace std;

#define FIRST_EVENT "FirstEvent"
#define SECOND_EVENT "SecondEvent"
#define THIRD_EVENT "ThirdEvent"
#define FOURTH_EVENT "FourthEvent"

/* Создать 4 процесса, каждый процесс выводит в консоль содержимое папки */
int main(int argc, char* argv[]) {

#ifdef _MSC_VER
	char lpszAppName1[] = "E:\\Projects\\C++ - Visual Studio\\Spovm\\lab_2\\Debug\\Child1.exe";
	char lpszAppName2[] = "E:\\Projects\\C++ - Visual Studio\\Spovm\\lab_2\\Debug\\Child2.exe";
	char lpszAppName3[] = "E:\\Projects\\C++ - Visual Studio\\Spovm\\lab_2\\Debug\\Child3.exe";
	char lpszAppName4[] = "E:\\Projects\\C++ - Visual Studio\\Spovm\\lab_2\\Debug\\Child4.exe";
	char lpszAppNameState[] = "E:\\Projects\\C++ - Visual Studio\\Spovm\\lab_2\\Debug\\Menu.exe";


	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	HANDLE  event1, event2, event3, event4;

	event1 = CreateEvent(NULL,			//атрибут защиты - по умолчанию
		FALSE,			//тип сбоса - АВТО
		TRUE,			//начальное состояние - сигнальное (вкл)
		FIRST_EVENT); //имя объекта

	event2 = CreateEvent(NULL, FALSE, FALSE, SECOND_EVENT);
	event3 = CreateEvent(NULL, FALSE, FALSE, THIRD_EVENT);
	event3 = CreateEvent(NULL, FALSE, FALSE, FOURTH_EVENT);


	try {
		if (!CreateProcess(
			lpszAppName1,
			".. \\1\\*",
			NULL,		// Дескриптор процесса не наследуемый.
			NULL,		// Дескриптор потока не наследуемый.
			FALSE,		// Наследование дескриптора - TRUE.
			0,			// Флажков создания нет.
			NULL,		// Использование блока конфигурации родителя.
			NULL,		// Использование стартового каталога родителя.
			&si,		// Указатель на структуру STARTUPINFO.	
			&pi)) 		// Указатель на структуру PROCESS_INFORMATION.
		{
			throw "First failed";
		}

		if (!CreateProcess(lpszAppName2, ".. \\2\\*", NULL, NULL, FALSE, 
							0, NULL, NULL, &si, &pi)) {
			throw "Second Process failed";
		}
		if (!CreateProcess(lpszAppName3, ".. \\3\\*", NULL, NULL, FALSE,
							0, NULL, NULL, &si, &pi)) {
			throw "Third Process failed";
		}
		if (!CreateProcess(lpszAppName4, ".. \\4\\*", NULL, NULL, FALSE,
							0, NULL, NULL, &si, &pi)) {
			throw "Fourth Process failed";
		}
		if (!CreateProcess(lpszAppNameState, NULL, NULL, NULL, FALSE,
							CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			throw  "State Process failed";
		}
	}
	catch (string s) {
		cout << "Error: " << s << endl;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

#else
	int pid[4], status;
	char *way, st[] = "/home/mikhail/Progects/", *str1, *dir, *dir1;
	dir = new char[200];
	dir1 = new char[200];
	str1 = new char[200];
	pid[0] = getpid();
	pid[1] = fork();
	pid[2] = fork();
	sprintf(str1, "%d", getpid());
	dir = strcat(st, str1);
	strcpy(dir1, dir);
	strcpy(global_way_of_dir, dir1);
	status = mkdir(dir, S_IRWXU | S_IRWXG | S_IXOTH);
	way = strcat(dir, "/");
	way = strcat(way, str1);
	way = strcat(way, "abcd.txt");
	ofstream out(way); 
	out.close();
	signal(SIGUSR1, *handle);
	signal(SIGUSR2, *handle1);
	cout << getpid() << endl;

	while (1)
	{

	}
	delete dir;
	delete dir1;
	delete str1;
#endif

	return 0;
}














