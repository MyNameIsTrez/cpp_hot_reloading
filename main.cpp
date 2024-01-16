#include "src/update.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using update_type = decltype(update);
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
	void *lib = dlopen(("./" + dll_path).c_str(), RTLD_NOW);
	char *errstr = dlerror();
	if (errstr != nullptr) {
		std::cerr << "A dynamic linking error occurred: " << errstr << "\n";
		assert(false);
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
	static const std::vector<std::string> names = {"update"};
	static std::vector<std::filesystem::file_time_type> prev_write_times(names.size(), std::filesystem::file_time_type::min());

	for (int i = 0; i < names.size(); i++) {
		const auto &name = names[i];
		const auto &prev_write_time = prev_write_times[i];

		const auto path = "dll/" + name + ".dll";

		const std::filesystem::file_time_type current_write_time = std::filesystem::last_write_time(path);

		if (current_write_time > prev_write_time) {
			if (dll) {
				free_dynamic_library(dll);
				dll = nullptr;
				std::cout << "Freed " << path << "\n";
			}
			
			dll = load_dynamic_library(path);
			std::cout << "Loaded " << path << "\n";

			update_ptr = (update_type *)load_dynamic_function(dll, name);
			std::cout << "Loaded dynamic function '" << name << "'\n";

			prev_write_times[i] = current_write_time;
		}
	}
}

int main() {
	while (true) {
		reload_dll();

		update(42);

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
