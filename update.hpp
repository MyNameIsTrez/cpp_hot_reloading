#pragma once

#ifdef _WIN32
#define EXPORT_FN __declspec(dllexport)
#elif __linux__
#define EXPORT_FN
#endif

extern "C" {
	// TODO: Try removing the declspec from here
	EXPORT_FN void update(int n);
}
