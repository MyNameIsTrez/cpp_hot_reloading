#include "update.hpp"

#include <iostream>

// TODO: Try removing the declspec from here on Windows
EXPORT_FN void update(int n) {
	std::cout << n << "\n";
	// std::cout << n * 2 << "\n";
}
