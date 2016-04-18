#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define BUF_SIZE 1024*1024*10

void SearchMin(int*, int);

int main(int argc, char* argv[])
{
	HANDLE hMapFile;
	LPCTSTR pBuf;
	TCHAR szName[] = TEXT("FileMappingObject");
	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // ������ � ������/������
		FALSE,                 // ��� �� �����������
		szName);               // ��� "������������� " ������� 
	if (hMapFile == NULL)
	{
		return 0;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,    // ���������� "�������������" �������
		FILE_MAP_ALL_ACCESS,  // ���������� ������/������
		0,
		0,
		BUF_SIZE);
	if (pBuf == NULL)
	{
		return 0;
	}
	int *size = new int[1];// �����!!!
	
	MoveMemory((PVOID)size, pBuf, sizeof(int));
	//cout << "PBUF = " << *size << endl;
	int *b = new int[*size];
	MoveMemory((PVOID)b, pBuf, sizeof(int)*(*size)); 
	SearchMin(b,*size);//����� ������������

	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	return 0;
}

void SearchMin(int *mas, int size)
{
	int min = mas[1];
	//cout << "Initial Size = " << size << endl;
	int l=0;
	for (int i = 1; i<size; i++)
	{
		l++;
		if(mas[i]<min)
			min=mas[i];
	}
	//cout << "Finish size = " << l << endl;
	cout << "Minimal value is " <<min;
	_getch();
}