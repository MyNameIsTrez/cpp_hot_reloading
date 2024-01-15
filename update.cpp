#include "update.hpp"

#include <iostream>

// TODO: Try removing the declspec from here
EXPORT_FN void update(int n) {
	std::cout << n << " foo\n";
	// std::cout << n * 2 << " bar\n";
}
