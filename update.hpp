#pragma once

#ifdef _WIN32
#define EXPORT_FN __declspec(dllexport)
#else
#define EXPORT_FN
#endif

extern "C" {
	EXPORT_FN void update(int n);
}
