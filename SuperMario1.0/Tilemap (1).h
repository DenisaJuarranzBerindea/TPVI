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
	vector<vector<int>> mapaV;
	Texture* background;
	Game* g;

public: 

	Tilemap(const string& fichero);

	void renderMapa();
};


