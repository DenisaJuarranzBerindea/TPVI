#ifndef Goomba_h
#define Goomba_h

#include "SceneObject.h"

#include "checkML.h"
#include <SDL.h>
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "Collision.h"

class Game;

using uint = unsigned int;
using namespace std;

class Goomba : public SceneObject
{
private:
	Texture* texture = nullptr;	// puntero a su textura

	const double X_SPEED = 0.01;
	const double Y_SPEED = 0.015;
	const double GRAVITY = 0.0025;
	
	bool frozen = true; // inactivo si no se ve en pantalla pantalla
	bool alive = true;	// vida

	bool grounded = true;

	int goombaFrame = 0; // animacion
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

	

public:
	// Colisiones goomba
	SDL_Rect colRect = SDL_Rect();

	Goomba(Game* game_, std::istream& in);

	void render() const override;
	void update() override;
	Collision hit(SDL_Rect, Collision::Target) override;

	void killGoomba() { alive = false; }

	bool getAlive() { return alive; }

	void printPos();

private:

	// Movimiento
	void moveGoomba();
};

#endif