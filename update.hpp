#pragma once

#ifdef _WIN32
#define EXPORT_FN __declspec(dllexport)
#else
#define EXPORT_FN
#endif

extern "C" {
	// TODO: Try removing the declspec from here on Windows
	EXPORT_FN void update(int n);
}
