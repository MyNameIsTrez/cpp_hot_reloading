#include "functions.hpp"

#include <iostream>

void update(int n) {
	std::cout << "update() calling update2() " << n << "\n";
	update2(n);
}
