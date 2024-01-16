#include "functions.hpp"

#include <thread>

void reload_dll();

int main() {
	reload_dll();

	init(69);

	while (true) {
		update(42.0);

		reload_dll();

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
