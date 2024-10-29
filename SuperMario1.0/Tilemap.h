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

public:
	Tilemap(const string&, Game*);

	void renderMapa();
};


