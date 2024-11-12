#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
//#include <Windows.h>
#include <vector>

#include "Game.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	try {
		Game game;
		game.run();
	}
	catch (const std::string& msg) {
		cerr << "Error: " << msg << endl;
	}

	return 0;
}

