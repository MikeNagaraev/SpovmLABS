#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

#define THIRD_EVENT "ThirdEvent"

int main(int argc, char *argv[]) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(argv[1], &FindFileData);

	HANDLE event3;

	try {

		if (!(event3 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, THIRD_EVENT)))
		{
			throw "Child3 : OpenEvent event3 Failed";
		}	

		if (hFind != INVALID_HANDLE_VALUE) {
			
			while (1) {

				WaitForSingleObject(event3, INFINITE);			

				do {
					cout << FindFileData.cFileName << endl;
				} while (FindNextFile(hFind, &FindFileData));
			
				hFind = FindFirstFile(argv[1], &FindFileData);
				SetEvent(event3);
				_sleep(2000);				
			}
		}
		else {

			throw "Child3: Opening directory failed.";
		}
	}
	catch (char *s) {
		cout << "Error: " << s << endl;
	}
	FindClose(hFind);

	return 0;
}