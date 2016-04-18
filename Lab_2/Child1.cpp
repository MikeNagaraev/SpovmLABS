#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

#define FIRST_EVENT "FirstEvent"

int main(int argc, char *argv[]) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(argv[1], &FindFileData);

	HANDLE event1;

	try {

		if (!(event1 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, FIRST_EVENT)))
		{
			throw "Child1 : OpenEvent event1 Failed";
		}
						
		if (hFind != INVALID_HANDLE_VALUE) {
			while (1) {

				WaitForSingleObject(event1, INFINITE);

				do {
					cout << FindFileData.cFileName << endl;
				} while (FindNextFile(hFind, &FindFileData));
		
				hFind = FindFirstFile(argv[1], &FindFileData);
				SetEvent(event1);
				_sleep(2000);
			}
		}
		else {

			throw "Child1: Opening directory failed.";
		}
	}
	catch (char *s) {
		cout << "Error: " << s<<endl;
	}
	FindClose(hFind);

	return 0;
}