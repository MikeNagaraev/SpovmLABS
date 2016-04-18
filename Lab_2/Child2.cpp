#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

#define SECOND_EVENT "SecondEvent"

int main(int argc, char *argv[]) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(argv[1], &FindFileData);

	HANDLE event2;

	try {

		if (!(event2 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, SECOND_EVENT)))
		{
			throw " Child2 : OpenEvent event2 Failed";
		}
	
		if (hFind != INVALID_HANDLE_VALUE) {
					
			while (1) {

				WaitForSingleObject(event2, INFINITE);
				
				do {
					cout << FindFileData.cFileName << endl;
				} while (FindNextFile(hFind, &FindFileData));
								
				hFind = FindFirstFile(argv[1], &FindFileData);
				SetEvent(event2);
				_sleep(2000);				
			}
		}
		else {

			throw "Child2: Opening directory failed.";
		}
	}
	catch (char *s) {
		cout << "Error: " << s << endl;
	}

	FindClose(hFind);

	return 0;
}