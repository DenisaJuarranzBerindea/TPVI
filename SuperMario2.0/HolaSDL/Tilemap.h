#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Texture.h"
#include "Collision.h"

using namespace std;
class Game;
class Tilemap
{

protected:
	Game* g;
	SDL_Rect rect;
	vector<vector<int>> mapaV;
	Texture* background_spritesheet;

public:
	Tilemap(vector<int>, const string&, Game*);
	void renderMapa();
	void handleEvents(const SDL_Event&);
	Collision hit(const SDL_Rect& rect, bool fromPlayer);
};


