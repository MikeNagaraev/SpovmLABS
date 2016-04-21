#include "hclient1.h"

int fd;
char buffer[BUF_SIZE];

int main(int argc, char *argv[]) {
	
  cout << "Menu:" << endl;
  if (mkfifo(NAMEDPIPE_NAME, 0777)) {
    perror("mkfifo");
  }

  if ((fd = open(NAMEDPIPE_NAME, O_RDWR)) <= 0) {
    perror("Openfile");
    return 1;
  }
  menu();

  return 0;
}

void menu() {
  int n;
  string s[3] = { START,START,START};
  string str;
  while (1) {
	str = "";
    memset(buffer, '\0', BUF_SIZE);	
	getMenu(s);
	do {
		cin >> n;
	} while (n < 0 || n > 3);
	ostringstream os;
	os << n;
    str = os.str();
    cout << str << endl;
	strcpy(buffer, str.c_str());
    write(fd, buffer, strlen(buffer));	
  }
}

void getMenu(string s[]){
	system("clear");
	cout << "Menu: " << endl;
	cout << "1 - " << s[0] << " 1st: " << endl;
	cout << "2 - " << s[1] << " 2nd: " << endl;
	cout << "3 - " << s[2] << " 3d: " << endl;
}



