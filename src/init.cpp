#include "functions.hpp"

#include <iostream>

void init(double n) {
	std::cout << "init() calling init2() " << n << "\n";
	init2(n);
}
