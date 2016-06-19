#include "FTPlib.h"

FTPlib::FTPlib(const char *lib_title){

	this->info = new CommandsInfo;
#ifdef _MSC_VER
	this->lib = LoadLibrary(lib_title);

	if (this->lib) {
		this->ls_com = (void(*)(CommandsInfo*))GetProcAddress(this->lib, "ls_command");
		this->get_com = (void(*)(CommandsInfo*))GetProcAddress(this->lib, "get_command");
		this->put_com = (void(*)(CommandsInfo*))GetProcAddress(this->lib, "put_command");
		this->rm_com = (void(*)(CommandsInfo*))GetProcAddress(this->lib, "rm_command");
		if (!ls_com || !get_com || !put_com || !rm_com) {
			throw("GetProcAddress() error in FTPlib::FTPlib(const char *)");
			exit(1);
		}
	}
	else {
		throw("LoadLibrary() error in FTPlib::FTPlib(const char *)");
		exit(1);
	}
#elif __linux__
	this->lib = dlopen(lib_title, RTLD_LAZY);
	if (!this->lib) {
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		exit(1); 
	};

	this->ls_com = (void(*)(CommandsInfo*))dlsym(this->lib, "ls_command");
	this->get_com = (void(*)(CommandsInfo*))dlsym(this->lib, "get_command");
	this->put_com = (void(*)(CommandsInfo*))dlsym(this->lib, "put_command");
	this->rm_com = (void(*)(CommandsInfo*))dlsym(this->lib, "rm_command");
	if (!ls_com || !get_com || !put_com || !rm_com) {
		throw("GetProcAddress() error in FTPlib::FTPlib(const char *)");
		exit(1);
	}
#endif
}

FTPlib::~FTPlib() {
#ifdef _MSC_VER
	FreeLibrary(lib);
#elif __linux__
	dlclose(this->lib);
#endif
	delete this->info;
}

void FTPlib::init(CommandsInfo *new_info) {

	this->info->public_folder = new_info->public_folder;
	this->info->client_folder = new_info->client_folder;
	this->info->command = new_info->command;
#ifdef _MSC_VER
	this->info->hNamedPipe = new_info->hNamedPipe;
#elif __linux__
	this->info->fd = new_info->fd;
#endif
}

void FTPlib::setPublicFolder(string path) {
	this->info->public_folder = path;
}
void FTPlib::setClientFolder(string path) {
	this->info->client_folder = path;
}
void FTPlib::setCommand(string com) {
	this->info->command = com;
}
#ifdef _MSC_VER
void FTPlib::sethNamedPipe(HANDLE hPipe) {
	this->info->hNamedPipe = hPipe;
}
#elif __linux__
void FTPlib::setFileDesc(int desc) {
	this->info->fd = desc;
}
#endif

void FTPlib::action(char act) {
	switch (act) {
		case 'l': {
			this->ls_com(this->info);
			break;
		}
		case 'g': {
			this->get_com(this->info);
			break;
		}
		case 'p': {
			this->put_com(this->info);
			break;
		}
		case 'r': {
			this->rm_com(this->info);
			break;
		}
		default: {
			throw("Unknown command in FTPLib::action(char)");
		}
	}
}
