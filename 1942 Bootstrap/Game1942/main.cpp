#include "Game1942App.h"

int main() {
	srand(time(NULL));
	// allocation
	auto app = new Game1942App();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}