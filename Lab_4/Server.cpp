#include "hServer.h"
#ifdef _MSC_VER
HANDLE Print1, Print2, Print3;
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
	if (!CreateProcess(prog, "menu process", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,
		NULL, &si, &pi)) {
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
		}
		else {
			throw new exception("Opening directory failed.");
		}
	}
	catch (exception *s) {
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
				ReleaseSemaphore(Print2, 1, NULL);
				hFind = FindFirstFile(PATH2, &FindFileData);
				_sleep(1000);
			}
		}
		else {
			throw new exception("Opening directory failed.");
		}
	}
	catch (exception *s) {
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
			throw new exception("Opening directory failed.");
		}
	}
	catch (exception *s) {
		cout << "Error: " << s << endl;
	}
	FindClose(hFind);

}

void menu() {
	int n;
	string s[3] = { START,START,START };

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
#else
int fd;
char readbuffer[BUF_SIZE];
pthread_t thread[3];
sem_t semaphore_1, semaphore_2, semaphore_3;
void *thread_func1(void *arg) {
	while (true) {
		sem_wait(&semaphore_1);
		DIR *d;
		struct dirent *dirr;
		d = opendir(PATH1);

		if (d) {
			while ((dirr = readdir(d)) != NULL) {
				printf("%s\n", dirr->d_name);
			}
			sleep(1);
			closedir(d);
		}
		else {
			perror("Opendir");
		}
		sem_post(&semaphore_1);
	}
}
void *thread_func2(void *arg) {
	while (true) {
		sem_wait(&semaphore_2);
		DIR *d;
		struct dirent *dirr;
		d = opendir(PATH2);
		if (d) {
			while ((dirr = readdir(d)) != NULL) {
				printf("%s\n", dirr->d_name);
			}
			sleep(1);
			closedir(d);
		}
		else {
			perror("Opendir");
		}
		sem_post(&semaphore_2);
	}
}
void *thread_func3(void *arg) {
	while (true) {
		sem_wait(&semaphore_3);
		DIR *d;
		struct dirent *dirr;
		d = opendir(PATH3);
		if (d) {
			while ((dirr = readdir(d)) != NULL) {
				printf("%s\n", dirr->d_name);
			}
			sleep(1);
			closedir(d);
		}
		else {
			perror("Opendir");
		}
		sem_post(&semaphore_3);
	}
}
void connection() {

	bool stop_or_start[3] = { false,false,false };
	while (true) {
		memset(readbuffer, '\0', BUF_SIZE);

		if ((read(fd, readbuffer, BUF_SIZE - 1)) > 0) {

			int k = atoi(readbuffer);
			switch (k) {
			case 1: {
				if (!stop_or_start[0]) {
					stop_or_start[0] = true;
					sem_post(&semaphore_1);
				}
				else {
					stop_or_start[0] = false;
					sem_post(&semaphore_1);
				}
				break;
			}
			case 2: {
				if (!stop_or_start[1]) {
					stop_or_start[1] = true;
					sem_post(&semaphore_2);
				}
				else {
					stop_or_start[1] = false;
					sem_post(&semaphore_2);
				}
				break;
			}
			case 3: {
				if (!stop_or_start[2]) {
					stop_or_start[2] = true;
					sem_post(&semaphore_3);
				}
				else {
					stop_or_start[2] = false;
					sem_post(&semaphore_3);
				}
				break;
			}
			case 4: {
				if (stop_or_start[0]) {
					sem_wait(&semaphore_1);
				}
				if (stop_or_start[1]) {
					sem_wait(&semaphore_2);
				}
				if (stop_or_start[2]) {
					sem_wait(&semaphore_3);
				}
				break;
			}
			}
		}
		else {
			close(fd);
			remove(NAMEDPIPE_NAME);
		}
	}
}

#endif
int main(int argc, char *argv[]) {
#ifdef _MSC_VER
	if (argc == CHAT_PROCESS) {
		MenuProcess();
	}
	else {
		MainProcess(argv[0]);
	}
#else
	if (mkfifo(NAMEDPIPE_NAME, 0777)) {
		perror("Mkfifo");
	}

	if ((fd = open(NAMEDPIPE_NAME, O_RDWR)) <= 0) {
		perror("openfile");
		return 1;
	}
	sem_init(&semaphore_1, 0, 0);
	sem_init(&semaphore_2, 0, 0);
	sem_init(&semaphore_3, 0, 0);

	pthread_create(&thread[0], NULL, thread_func1, NULL);
	pthread_create(&thread[1], NULL, thread_func2, NULL);
	pthread_create(&thread[2], NULL, thread_func3, NULL);
	cout << "Server" << endl;

	connection();
#endif
	return 0;
}

