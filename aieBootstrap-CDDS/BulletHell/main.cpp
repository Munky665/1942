#include "BulletHellApp.h"

int main() {
	
	// allocation
	auto app = new BulletHellApp();

	// initialise and loop
	app->run("Bullet Hell", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}