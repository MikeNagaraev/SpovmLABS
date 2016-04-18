#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

#define FIRST_EVENT "FirstEvent"
#define SECOND_EVENT "SecondEvent"
#define THIRD_EVENT "ThirdEvent"
#define FOURTH_EVENT "FourthEvent"

#define START "Start"
#define STOP  "Stop"

void ControlMenu(HANDLE , HANDLE , HANDLE , HANDLE );
void GetMenu(string []);

int main(int argc, char *argv[]) {

	HANDLE event1, event2, event3, event4;

	if (!(event1 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, FIRST_EVENT)))
		throw "OpenEvent FirstEvent Failed";
	if (!(event2 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, SECOND_EVENT)))
		throw "OpenEvent SecondEvent Failed";
	if (!(event3 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, THIRD_EVENT)))
		throw "OpenEvent ThirdEvent Failed";
	if (!(event4 = OpenEvent(EVENT_ALL_ACCESS | EVENT_MODIFY_STATE, TRUE, FOURTH_EVENT)))
		throw "OpenEvent FourthEvent Failed";

	try {
		ControlMenu(event1, event2, event3, event4);
	}
	catch (char *ss) {
		cout << "Error: " << ss << endl;
	}

	return 0;
}

void ControlMenu(HANDLE event1, HANDLE event2, HANDLE event3, HANDLE event4)
{
	int n;
	string s[4] = { STOP,START,START,START };

	while (1) {
		GetMenu(s);
		cin >> n;
		switch (n) {
			case 1: {
				if (s[0] == START) {
					s[0] = STOP;
					SetEvent(event1);
				}
				else {
					s[0] = START;
					ResetEvent(event1);
				}
				break; 
			}
			case 2: {
				if (s[1] == START) {
					s[1] = STOP;
					SetEvent(event2);
				}
				else {
					s[1] = START;
					ResetEvent(event2);
				}
				break;
			}
			case 3: {
				if (s[2] == START) {
					s[2] = STOP;
					SetEvent(event3);
				}
				else {
					s[2] = START;
					ResetEvent(event3);
				}
				break;
			}
			case 4: {
				if (s[3] == START) {
					s[3] = STOP;
					SetEvent(event4);
				}
				else {
					s[3] = START;
					ResetEvent(event4);
				}
				break;
			}
			case 5: {
				ResetEvent(event1);
				ResetEvent(event2);
				ResetEvent(event3);
				ResetEvent(event4);
				for (int i = 0; i < 4; i++)
					s[i] = START;
				break;
			}
		}
	}
}

void GetMenu(string s[])
{
	system("CLS");
	cout << "Menu: " << endl;
	cout << "1 - " << s[0] << " 1st: " << endl;
	cout << "2 - " << s[1] << " 2nd: " << endl;
	cout << "3 - " << s[2] << " 3d: " << endl;
	cout << "4 - " << s[3] << " 4th: " << endl;
	cout << "5 - Stop All: " << endl;
}