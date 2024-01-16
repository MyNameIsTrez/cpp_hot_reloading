#pragma once

#ifdef _WIN32
#define EXPORT_FN __declspec(dllexport)
#else
#define EXPORT_FN
#endif

extern "C" {
	EXPORT_FN void init(double n);
	EXPORT_FN void init2(double n);
	EXPORT_FN void update(int n);
	EXPORT_FN void update2(int n);
}
