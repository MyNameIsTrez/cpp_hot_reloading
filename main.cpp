#include "functions.hpp"

#include <thread>

void reload_dll();

int main() {
#ifndef NO_HOT_RELOADING
	reload_dll();
#endif

	while (true) {
		update(42.0);

#ifndef NO_HOT_RELOADING
		reload_dll();
#endif

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
