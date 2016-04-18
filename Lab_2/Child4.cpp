#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

#define FOURTH_EVENT "FourthEvent"

int main(int argc, char *argv[]) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(argv[1], &FindFileData);

	HANDLE event4;

	try {
		if (!(event4 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, FOURTH_EVENT)))
		{
			throw "Child4: OpenEvent event4 Failed";
		}		

		if (hFind != INVALID_HANDLE_VALUE) {
		
			while (1) {
				WaitForSingleObject(event4, INFINITE);
			
				do {
					cout << FindFileData.cFileName << endl;
				} while (FindNextFile(hFind, &FindFileData));
			

				hFind = FindFirstFile(argv[1], &FindFileData);
				SetEvent(event4);
				_sleep(2000);				
			}
		}
		else {

			throw "Child4: Opening directory failed.";
		}
	}
	catch (char *s) {
		cout << "Error: " << s << endl;
	}
	FindClose(hFind);

	return 0;
}