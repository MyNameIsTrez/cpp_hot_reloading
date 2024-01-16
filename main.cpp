#include "update.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

typedef decltype(update) update_type;
static update_type *update_ptr;

void update(int n) {
	update_ptr(n);
}

void *load_dynamic_function(void *dll, const std::string &function_name) {
#ifdef _WIN32
	void *proc = (void *)GetProcAddress((HMODULE)dll, function_name.c_str());
#else
	void* proc = dlsym(dll, function_name.c_str());
#endif
	assert(proc);
	return proc;
}

void *load_dynamic_library(const std::string &dll_path) {
#ifdef _WIN32
	HMODULE lib = LoadLibraryA(dll_path.c_str());
#else
	void *lib;
	while (true) {
		lib = dlopen(("./" + dll_path).c_str(), RTLD_NOW);
		std::cerr << "lib: " << lib << "\n";
		char *errstr = dlerror();
		if (errstr == nullptr) {
			break;
		}
		std::cerr << "A dynamic linking error occurred: " << errstr << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
#endif
	assert(lib);
	return lib;
}

void free_dynamic_library(void *dll) {
#ifdef _WIN32
	assert(FreeLibrary((HMODULE)dll));
#else
	assert(!dlclose(dll));
#endif
}

void reload_dll() {
	static void *dll;
	static std::filesystem::file_time_type prev_write_time = std::filesystem::last_write_time("update.dll");

	std::filesystem::file_time_type current_write_time = std::filesystem::last_write_time("update.dll");

	if (current_write_time >= prev_write_time) {
		if (dll) {
			free_dynamic_library(dll);
			dll = nullptr;
			std::cout << "Freed update.dll\n";
		}
		
		dll = load_dynamic_library("update.dll");
		std::cout << "Loaded update.dll\n";

		update_ptr = (update_type *)load_dynamic_function(dll, "update");
		std::cout << "Loaded dynamic function 'update'\n";

		prev_write_time = current_write_time;
	}
}

int main() {
	while (true) {
		reload_dll();

		update(42);

		// std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
