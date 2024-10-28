#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Texture.h"

using namespace std;
class Game;
class Tilemap
{

protected:
	Game* g;
	vector<vector<int>> mapaV;
	Texture* background_spritesheet;

	SDL_Texture* background_texture;

public: 

	Texture* background;
	Tilemap(const string&, Game*);

	void renderMapa();
};


