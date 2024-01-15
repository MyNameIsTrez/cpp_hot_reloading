#include "update.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

typedef decltype(update) update_type;
static update_type *update_ptr;

void update(int n) {
	update_ptr(n);
}

void *load_dynamic_function(void *dll, const char *function_name) {
#ifdef _WIN32
	FARPROC proc = GetProcAddress((HMODULE)dll, function_name);
#endif
	assert(proc);
	return (void *)proc;
}

void *load_dynamic_library(const char *dll_path) {
#ifdef _WIN32
	HMODULE result = LoadLibraryA(dll_path);
#endif
	assert(result);
	return result;
}

void free_dynamic_library(void *dll) {
#ifdef _WIN32
	assert(FreeLibrary((HMODULE)dll));
#endif
}

void reload_dll() {
	static void *dll;
	static std::filesystem::file_time_type prev_write_time;

	std::filesystem::file_time_type current_write_time = std::filesystem::last_write_time("update.dll");

	if (current_write_time > prev_write_time) {
		if (dll) {
			free_dynamic_library(dll);
			dll = nullptr;
			std::cout << "Freed update.dll\n";
		}
		
		std::filesystem::copy("update.dll", "update_load.dll", std::filesystem::copy_options::overwrite_existing);
		std::cout << "Copied update.dll to update_load.dll\n";

		dll = load_dynamic_library("update_load.dll");
		std::cout << "Loaded update_load.dll\n";

		update_ptr = (update_type *)load_dynamic_function(dll, "update");
		std::cout << "Loaded dynamic function 'update'\n";

		prev_write_time = current_write_time;
	}
}

int main() {
	while (true) {
		reload_dll();

		update(42);

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}