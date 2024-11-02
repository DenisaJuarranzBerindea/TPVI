#ifndef Goomba_h
#define Goomba_h

#include "checkML.h"
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

class Goomba
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	//Point2D<double> position;	// posicion actual en Point2D
	//Vector2D<int> direction;	// direccion de movimiento
	double x, y;
	int dx, dy;
	double speed;				// velocidad de movimiento


	bool frozen; // inactivo si no se ve en pantalla pantalla
	bool alive;	// vida

	int goombaFrame; // animacion
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

public:
	Goomba(Game* g, std::istream& in, double speed, int x, int y);

	void render() const;
	void update();
	void hit(SDL_Rect* rect);

private:

	// Movimiento
	void moveGoomba();
};

#endif