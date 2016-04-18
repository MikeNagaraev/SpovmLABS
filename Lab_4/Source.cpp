#include "Header.h"

HANDLE Print1, Print2, Print3;



int main(int argc, char* argv[]) {
	if (argc == CHAT_PROCESS) {
		MenuProcess();
	}
	else MainProcess(argv[0]);

	return 0;
}

void MainProcess(char *prog) {
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	HANDLE thread1, thread2, thread3;
	DWORD idThread1, idThread2, idThread3;
	Print1 = CreateSemaphore(NULL, 0, 1, "Print1");
	Print2 = CreateSemaphore(NULL, 0, 1, "Print2");
	Print3 = CreateSemaphore(NULL, 0, 1, "Print3");
	if (!CreateProcess(prog, "menu process", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		printf_s("Create Process failed %d\n", GetLastError());
		return;
	}
	if (!(thread1 = CreateThread(NULL, 0, funcPrint_1, NULL, 0, &idThread1))) {
		printf("CreateThread error: %d\n", GetLastError());
		return;
	}
	if (!(thread2 = CreateThread(NULL, 0, funcPrint_2, NULL, 0, &idThread2))) {
		printf("CreateThread error: %d\n", GetLastError());
		return;
	}
	if (!(thread3 = CreateThread(NULL, 0, funcPrint_3, NULL, 0, &idThread3))) {
		printf("CreateThread error: %d\n", GetLastError());
		return;
	}
	while (1) {

	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void MenuProcess() {

	Print1 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Print1");
	Print2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Print2");
	Print3 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Print3");

	menu();
}

DWORD WINAPI funcPrint_1(LPVOID lpParam) {
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile(PATH1, &FindFileData);
  try {
    if (hFind != INVALID_HANDLE_VALUE) {
      while (true) {
        WaitForSingleObject(Print1, INFINITE);
		do {
			cout << FindFileData.cFileName << endl;
		} while (FindNextFile(hFind, &FindFileData));
		ReleaseSemaphore(Print1, 1, NULL);
		hFind = FindFirstFile(PATH1, &FindFileData);
		_sleep(1000);
	  }
    } else {
      throw "Opening directory failed.";
    }
  }
  catch (char *s) {
    cout << "Error: " << s << endl;
  }
  FindClose(hFind);
}

DWORD WINAPI funcPrint_2(LPVOID lpParam) {
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile(PATH2, &FindFileData);
  try {
    if (hFind != INVALID_HANDLE_VALUE) {
      while (true) {
        WaitForSingleObject(Print2, INFINITE);
        do {
          cout << FindFileData.cFileName << endl;
        } while (FindNextFile(hFind, &FindFileData));
		ReleaseSemaphore(Print2, 1,NULL);
        hFind = FindFirstFile(PATH2, &FindFileData);
        _sleep(1000);
      }
    }
    else {
      throw "Opening directory failed.";
    }
  }
  catch (char *s) {
    cout << "Error: " << s << endl;
  }
  FindClose(hFind);

}

DWORD WINAPI funcPrint_3(LPVOID lpParam) {
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = FindFirstFile(PATH3, &FindFileData);
  try {
    if (hFind != INVALID_HANDLE_VALUE) {
      while (true) {
        WaitForSingleObject(Print3, INFINITE);
        do {
          cout << FindFileData.cFileName << endl;
        } while (FindNextFile(hFind, &FindFileData));
		ReleaseSemaphore(Print3, 1, NULL);
        hFind = FindFirstFile(PATH3, &FindFileData);
        _sleep(1000);
      }
    }
    else {
      throw "Opening directory failed.";
    }
  }
  catch (char *s) {
    cout << "Error: " << s << endl;
  }
  FindClose(hFind);

}

void menu() {
  int n;
  string s[3] = { START,START,START};

  while (1) {
	getMenu(s);
	do {
		cin >> n;
	} while (n < 0 || n>4);
	switch (n) {
	  case 1: {
		if (s[0] == START) {
			s[0] = STOP;
			ReleaseSemaphore(Print1, 1, NULL);			
		}
		else {
			s[0] = START;
			WaitForSingleObject(Print1, INFINITE);
		}
		break;
	  }
	  case 2: {
		if (s[1] == START) {
			s[1] = STOP;
			ReleaseSemaphore(Print2, 1, NULL);
		}
		else {
			s[1] = START;
			WaitForSingleObject(Print2, INFINITE);
		}
		break;
	  }
	  case 3: {
		if (s[2] == START) {
			s[2] = STOP;
			ReleaseSemaphore(Print3, 1, NULL);
		}
		else {
			s[2] = START;
			WaitForSingleObject(Print3, INFINITE);
		}
		break;
	  }
	  case 4: {
		  if (s[0] == STOP) {
			WaitForSingleObject(Print1, INFINITE);
		  }
		  if (s[1] == STOP) {
		    WaitForSingleObject(Print2, INFINITE);
		  }
		  if (s[2] == STOP) {
			WaitForSingleObject(Print3, INFINITE);
		  }
         for (int i = 0; i < 3; i++) {
           s[i] = START;
        }
		break;
	  }
	}
  }
}

void getMenu(string s[])
{
	system("CLS");
	cout << "Menu: " << endl;
	cout << "1 - " << s[0] << " 1st: " << endl;
	cout << "2 - " << s[1] << " 2nd: " << endl;
	cout << "3 - " << s[2] << " 3d: " << endl;
	cout << "4 - Stop All: " << endl;
}