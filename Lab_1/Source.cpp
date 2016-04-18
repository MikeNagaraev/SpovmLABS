#include <windows.h>
#include <conio.h>
#include <iostream>
#include <ctime>
using namespace std;

#define BUF_SIZE 1024*1024*10

int* Initialise_array(int);	//���������� �������
int Type_size();			//���� ���������� �����

int main()
{
	char lpszComLine[80]; // ��� ��������� ������
	char lpszAppName[] = "E:\\Projects\\C++ - Visual Studio\\Lab1Memory\\Debug\\Child.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	HANDLE hMapFile;
	LPCTSTR pBuf;
	TCHAR szName[] = TEXT("FileMappingObject");	
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // ������������� ����� ��������
		NULL,                    // ������ �� ��������� 
		PAGE_READWRITE,          // ������ � ������/������
		0,                       // ����. ������ ������� 
		BUF_SIZE,                // ������ ������  
		szName);                 // ��� ����������� � ������ �������

	if (hMapFile == NULL || hMapFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // ����������  �����������
											 // � ������ �������
		FILE_MAP_ALL_ACCESS, // ���������� ������/������
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		return 0;
	}

	int kol;
	kol = Type_size();
	//cout << "SIZE = " << kol << endl;
	CopyMemory((PVOID)pBuf, Initialise_array(kol), sizeof(int)*kol);
	getch();

	if (!CreateProcess(lpszAppName, GetCommandLine(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
	{
		cout << "ERROR";
		return 0;
	}
	cout << "The new process is created.";
	// ���� ���������� ���������� ��o����a
	WaitForSingleObject(piApp.hProcess, INFINITE);

	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	// ��������� ����������� ����� �������� � ������� ��������
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	return 0;
}
int* Initialise_array(int a)
{
	int *mass=new int[a];
	srand(time(NULL));
	mass[0] = a;
	for (int i = 1; i < a; i++)
	{
		mass[i] = rand();
	}
	return mass;
}

int Type_size()
{
	bool flag = true;
	int a;
	do {
		try {
			system("cls");
			flag = true;
			cout << "Input number of elements of array" << endl;
			cin >> a;
			if (a < 1 || a>100000)
				throw a;
		}
		catch (int _a)
		{
			flag = false;
			cin.clear();
			cin.ignore(10, '\n');
			cin.sync();
		}
	} while (!flag);
	return a+1;
}