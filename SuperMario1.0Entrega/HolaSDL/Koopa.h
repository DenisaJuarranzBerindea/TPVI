#ifndef Koopa_h
#define Koopa_h

#include "../checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "../texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

class Game;

using uint = unsigned int;
using namespace std;

class Koopa
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<int> direction;	// direccion de movimiento

public:
	Koopa();

	void render() const;
	void update();
	void hit(SDL_Rect* rect);
};

#endif