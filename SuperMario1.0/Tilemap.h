#pragma once

#include "checkML.h"

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
	Game* g = nullptr;
	vector<vector<int>> mapaV;
	Texture* background_spritesheet = nullptr;

public:
	//Constructora
	Tilemap(const string&, Game*);

	////Destructora
	//~Tilemap();

	//Render
	void renderMapa();
	//Actualizar
	void update();
	// Colisiones
	void hit();
};


