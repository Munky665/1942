#include "Game1942App.h"
#include "MainMenu.h"


int main() {
	srand(time(nullptr));
	
	// allocation
	auto app = new Game1942App();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;
	return 0;
}