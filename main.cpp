#include <unistd.h>

void update(int n);

int main() {
	while (true) {
		update(42);
		sleep(1);
	}
}
