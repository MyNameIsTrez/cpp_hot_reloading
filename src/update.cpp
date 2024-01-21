#include "functions.hpp"
#include "inner/update2.hpp"

#include <iostream>

void update(int n) {
	std::cout << "update() calling update2() " << n << "\n";
	update2(n);
}
