#include "hServer.h"

struct command {
	const char *maxi;
	char mini;
};

struct command Command[] = {
	{ COM_LS, 'l'},
	{ COM_GETFILE, 'g' },
	{ COM_PUTFILE, 'p' },
	{ COM_RMFILE, 'r' },
	{ COM_EXIT, 'e' }
};

int main(int argc, char *argv[]) {

	cout << "Server:" << endl;

#ifdef _MSC_VER

	hNamedPipe = CreateNamedPipe(
		lpszPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		BUF_SIZE,
		BUF_SIZE,
		5000,
		NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		perror("CreateNamedPipe");
		return 1;
	}

	if (!ConnectNamedPipe(hNamedPipe, NULL)) {
		perror("ConnectNamedPipe");
	}

	ftp.setClientFolder(CLIENT_FOLDER);
	ftp.sethNamedPipe(hNamedPipe);

	Communication();
	
	DisconnectNamedPipe(hNamedPipe);
	CloseHandle(hNamedPipe);
	

#else
	
	if (mkfifo(NAMEDPIPE_NAME, 0777)) {
		perror("Mkfifo");
	}

	if ((fd = open(NAMEDPIPE_NAME, O_RDWR)) <= 0) {
		perror("openfile");
		return 1;
	}

	ftp.setClientFolder(CLIENT_FOLDER_UNIX);
	ftp.setPublicFolder(PUBLIC_FOLDER_UNIX);
	ftp.setFileDesc(fd);

	Communication();

#endif

	return 0;
}

char GetShortCommand(const char *long_command) {

	char short_command;

	for (int i = 0; i < 5; i++) {
		if (!strcmp(long_command, Command[i].maxi)) {
			short_command = Command[i].mini;
			return short_command;
		}
	}

	return 'z';
}

string getCommand(char *buffer, int type) {

	string command;

	if (type == 1) {

		stringstream ss;
		ss << buffer;
		getline(ss, command, ' ');
	}
	else {

		command = buffer;
		command = command.substr(
			command.find(" ") + 1,
			sizeof(command) - command.find(" ") - 1);
	}

	return command;
}

#ifdef _MSC_VER

void Communication() {

	while (true) {

		if (ReadFile(hNamedPipe, buffer, BUF_SIZE, &cbRead, NULL)) {

			cout << buffer << endl;

			if (!WriteFile(hNamedPipe,
					buffer,
					strlen(buffer) + 1,
					&cbWritten,
					NULL)) {

				perror("WriteFile");
			}

			switch (GetShortCommand(getCommand(buffer, 1).c_str())) {
				case 'l': {
					ftp.setPublicFolder(PUBLIC_DIR);
					ftp.action('l');
					break;
				}
				case 'e': {
					return;
					break;
				}
				case 'r': {
					ftp.setPublicFolder(PUBLIC_FOLDER);
					ftp.setCommand(buffer);
					ftp.action('r');
					break;
				}
				case 'g': {
					ftp.setPublicFolder(PUBLIC_FOLDER);
					ftp.setCommand(buffer);
					ftp.action('g');
					break;
				}
				case 'p': {
					ftp.setPublicFolder(PUBLIC_FOLDER);
					ftp.setCommand(buffer);
					ftp.action('p');
					break;
				}
				default: {
					cout << "Bad command." << endl;
				}
			}

		}
		else {

			perror("ReadFile");
		}

	}
}

#else

void Communication() {

	while (true) {

		//clear buffers
		memset(readbuffer, '\0', BUF_SIZE);
		memset(buffer, '\0', BUF_SIZE);

		//waiting and reading command from client
		if ((len = read(fd, readbuffer, BUF_SIZE - 1)) > 0) {
			
			//print command on screen
			cout << readbuffer << endl;

			switch (GetShortCommand(getCommand(readbuffer, 1).c_str())) {
				case 'l': {
					ftp.action('l');
					break;
				}
				case 'e': {
					close(fd);
					remove(NAMEDPIPE_NAME);
					return;
					break;
				}
				case 'r': {
					ftp.setCommand(readbuffer);
					ftp.action('r');
					break;
				}
				case 'g': {
					ftp.setCommand(readbuffer);
					ftp.action('g');
					break;
				}
				case 'p': {
					ftp.setCommand(readbuffer);
					ftp.action('p');
					break;
				}
				default: {
					cout << "Bad command." << endl;
				}
			}
		}
		else {

			perror("Read");
			close(fd);
			remove(NAMEDPIPE_NAME);
			return;
		}
	}
}
#endif




