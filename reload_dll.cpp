#include "functions.hpp"

#include <filesystem>
#include <iostream>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using update_type = decltype(update);
static update_type *update_ptr;
void update(int n) {
	update_ptr(n);
}

#ifndef _WIN32
static void print_dlerror(const std::string &function_name) {
	char *err = dlerror();
	if (err == nullptr) {
		abort();
	}
	std::cerr << "dlerror in " << function_name << "()" << ":\n" << err << "\n";
	abort();
}
#endif

static void *load_dynamic_function(void *dll, const std::string &function_name) {
	std::cout << "Loading dynamic function '" << function_name << "'\n";
#ifdef _WIN32
	void *proc = (void *)GetProcAddress((HMODULE)dll, function_name.c_str());
	if (!proc) {
		abort();
	}
#else
	void* proc = dlsym(dll, function_name.c_str());
	if (!proc) {
		print_dlerror("load_dynamic_function");
	}
#endif
	return proc;
}

static void *load_dynamic_library(const std::string &dll_path) {
#ifdef _WIN32
	HMODULE lib = LoadLibraryA(dll_path.c_str());
	if (!lib) {
		abort();
	}
#else
	void *lib = dlopen(("./" + dll_path).c_str(), RTLD_NOW);
	if (!lib) {
		print_dlerror("load_dynamic_library");
	}
#endif
	return lib;
}

static void free_dynamic_library(void *dll) {
#ifdef _WIN32
	if (!FreeLibrary((HMODULE)dll)) {
		abort();
	}
#else
	if (dlclose(dll)) {
		print_dlerror("free_dynamic_library");
	}
#endif
}

void reload_dll() {
	static void *dll;
	static std::filesystem::file_time_type prev_write_time = std::filesystem::file_time_type::min();

	static const std::string dll_path = "program.dll";

	const std::filesystem::file_time_type current_write_time = std::filesystem::last_write_time(dll_path);

	if (current_write_time > prev_write_time) {
		if (dll) {
			free_dynamic_library(dll);
			dll = nullptr;
			std::cout << "Freed " << dll_path << "\n";
		}

		dll = load_dynamic_library(dll_path);
		std::cout << "Loaded " << dll_path << "\n";

		update_ptr = (update_type *)load_dynamic_function(dll, "update");

		std::cout << "Loaded all dynamic functions\n";

		prev_write_time = current_write_time;
	}
}
