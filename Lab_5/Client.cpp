#include "hClient.h"
#include <fstream>

int main(int argc, char *argv[]) {
	
	cout << "Client:" << endl;

	getMenu();

#ifdef _MSC_VER

	hNamedPipe = CreateFile(
		szPipeName, 
		GENERIC_READ | GENERIC_WRITE,
		0, 
		NULL, 
		OPEN_EXISTING, 
		0, 
		NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		perror("CreateNamedPipe");
		return 1;
	}
	

#else

	if (mkfifo(NAMEDPIPE_NAME, 0777)) {
		perror("mkfifo");
	}

	if ((fd = open(NAMEDPIPE_NAME, O_RDWR)) <= 0) {
		perror("Openfile");
		return 1;
	}

#endif

	Communication();

#ifdef _MSC_VER

	CloseHandle(hNamedPipe);

#endif

	return 0;
}

void showFiles(char *buffer, string folder) {

	string file;
	stringstream ss;

	ss << buffer;

	while (getline(ss, file, '/')) {
		cout << folder << "/" << file << endl;
	}
}

void getMenu() {

	cout << "Comands:" << endl;
	cout << COM_LS << " - show all files" << endl;
	cout << COM_RMFILE << " - remove file" << endl;
	cout << COM_GETFILE << " - get file from server" << endl;
	cout << COM_PUTFILE << " - put file to server" << endl;
	cout << COM_EXIT  << " - close interact" << endl;

}

string getCommand(char *buffer) {

	string command;
	stringstream ss;

	ss << buffer;

	getline(ss, command, ' ');
		
	return command;
}
#ifdef _MSC_VER 
int WriteToFileAsync(std::string name, std::string content) {
	// create the buffer
	char* buffer = new char[content.size()];
	strcpy(buffer, content.c_str());
	
	int i = 0;
	while (buffer[i]) {
		std::cout << buffer[i++];
	}	
	HANDLE file_handle = CreateFile(name.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	OVERLAPPED str;
	memset(&str, 0, sizeof(str));
	str.Offset = 0;
	str.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	DWORD erroc = WriteFile(file_handle, buffer, i - 1, NULL, &str);
	
	if (erroc == FALSE) {
		return 1;
	}
	return 0;
}
#else 
int writeToFileAsync(std::string name, std::string content) {
	int file = open(name.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (file == -1)
	{
		std::cout << "Unable to open file!" << std::endl;
		return 0;
	}

	// create the buffer
	char* buffer = new char[content.size()];
	strcpy(buffer, content.c_str());

	int i = 0;
	while (buffer[i]) {
		std::cout << buffer[i++];
	}

	// create the control block structure
	aiocb cb;

	memset(&cb, 0, sizeof(aiocb));
	cb.aio_nbytes = content.size();
	cb.aio_fildes = file;
	cb.aio_offset = 0;
	cb.aio_buf = buffer;

	// read!
	if (aio_write(&cb) == -1)
	{
		std::cout << "Unable to create request!" << std::endl;
		close(file);
	}

	// wait until the request has finished
	while (aio_error(&cb) == EINPROGRESS)
	{
		//std::cout << "Working..." << std::endl;
	}

	// success?
	int numBytes = aio_return(&cb);

	
	delete[] buffer;
	close(file);

	return 0;
}

#endif
#ifdef _MSC_VER

void Communication() {

	while (true) {

		getline(cin, buf);
		strcpy_s(buffer, buf.c_str());

		if (!WriteFile(hNamedPipe,
			buffer,
			strlen(buffer) + 1,
			&cbWritten,
			NULL)) {
			perror("WriteFile");
		}

		if (ReadFile(hNamedPipe, buffer, BUF_SIZE, &cbRead, NULL)) {

			if (!strcmp(buffer, COM_LS)) {

				if (ReadFile(hNamedPipe,
					buffer,
					BUF_SIZE,
					&cbRead,
					NULL)) {
					showFiles(buffer, "public");
				}
				else {
					perror("ReadFile");
				}
			}
			else if (!strcmp(buffer, COM_EXIT)) {
				break;
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

		//get command
		getline(cin, buf);
		//copy command to buffer
		strcpy(buffer, buf.c_str());

		//send command to server
		write(fd, buffer, strlen(buffer));

		//command 'exit' terminate programm
		if (!strcmp(buffer, COM_EXIT)) {
			break;
		}
		//command 'ls' inquire server file system
		else if (!strcmp(buffer, COM_LS)) {

			cout << "Files on server:" << endl;

			//waiting the list of files from server
			if ((len = read(fd, readbuffer, BUF_SIZE - 1)) > 0) {

				//print the list of files on screen
				showFiles(readbuffer, "public");
			}
			else {

				perror("Read");
				close(fd);
				remove(NAMEDPIPE_NAME);
				break;
			}
		}
	}
}

#endif
