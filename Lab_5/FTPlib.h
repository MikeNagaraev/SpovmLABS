#include "hGeneral.h"

struct CommandsInfo {
	string public_folder;
	string client_folder;
	string command;
#ifdef _MSC_VER
	HANDLE hNamedPipe;
#elif __linux__
	int fd;
#endif
};

class FTPlib {
	CommandsInfo *info;
#ifdef _MSC_VER
	HINSTANCE lib;
#elif __linux__
	void *lib;
#endif
	void(*ls_com)(CommandsInfo*);
	void(*get_com)(CommandsInfo*);
	void(*put_com)(CommandsInfo*);
	void(*rm_com)(CommandsInfo*);
	void(*hello)(int);
public:
	FTPlib(const char * = "lib.dll");
	~FTPlib();
	void init(CommandsInfo *);
	void setPublicFolder(string);
	void setClientFolder(string);
	void setCommand(string);
#ifdef _MSC_VER
	void sethNamedPipe(HANDLE);
#elif __linux__
	void setFileDesc(int);
#endif
	void action(char);
	class Exception {
	public:
		string info;
		Exception(string info) {
			this->info = info;
			cerr << info << endl;
		}
	};
};

