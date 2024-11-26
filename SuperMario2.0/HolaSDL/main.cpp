#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <vector>
#include "Game.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	try {
		cout << "G" << endl;
		Game game;
		cout << "Game creado" << endl;
		game.run();
	}
	catch (const std::string& msg) {
		cerr << "Error: " << msg << endl;
	}

	return 0;
}

