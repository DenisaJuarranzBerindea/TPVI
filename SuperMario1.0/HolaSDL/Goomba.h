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
	double speed = 0.003;			// velocidad de movimiento


	bool frozen = true; // inactivo si no se ve en pantalla pantalla
	bool alive;	// vida

	int goombaFrame; // animacion
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

public:
	// Colisiones goomba
	SDL_Rect colRect = SDL_Rect();

	Goomba(Game* g, std::istream& in);

	void render() const;
	void update();
	//Collision hit(const SDL_Rect& rect, bool Mario);

	void printPos();

private:

	// Movimiento
	void moveGoomba();
};

#endif