#ifndef PLAYER_H
#define PLAYER_H

#include "checkML.h"
#include <SDL.h>
//#include "Vector2D.h"
#include "../Texture.h"
#include "HolaSDL/Collision.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

// para evitar inclusiones cruzadas
class Game;

using uint = unsigned int;
using namespace std;

class Player
{

private:
	Texture* texture;	// puntero a su textura
	Game* g; // puntero al juego

	int maxLifes = 3;
	int lifes;					// numero de vidas restantes, 3 al inicio

	bool isAlive = true;

	//Point2D<double> position;	// posicion actual en Point2D
	//Vector2D<int> direction = Vector2D(0, 0);	// direccion de movimiento
	double x, y;
	int dx, dy;
	double speed;			// velocidad de movimiento

public:

	bool grounded = true;		// si esta en el suelo, solo puede saltar cuando lo este
	double groundedYPos;	// posicion en el suelo
	int maxHeight;

	char marioState; // m(mario), s(supermario)

	// ANIMACION
	int marioFrame = 0;

	// INPUT
	bool keyA = false; //Izqd
	bool keyD = false; //Dcha
	bool keyS = false; //Abajo
	bool keySpace = false; //Salto
	bool keyE = false; //Salir
		

	// Colisiones player
	SDL_Rect colRect = SDL_Rect();
	Collision collisionMario;

	bool isFalling = false;
	bool canJump = false;
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;
	bool flipSprite = false;

public:
	//Constructora
	Player(Game* game, std::istream& in, double speed_); // La textura tambien?

	// Render
	void render() const;
	// Actualizaci n
	void update();
	// Eventos, sobre todo input   
	void handleEvents(const SDL_Event& event);
	// Colisiones
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	// Animaciones
	void updateAnims();
	// Para bloquear pantalla cuando avanza
	void updateOffset();


	// Getters
	double getX() const { return x; }
	double getY() const { return y; }
	int getDx() const { return dx; }
	int getDy() const { return dy; }

	// Setters
	void setX(double newX) { x = newX; }
	void setY(double newY) { y = newY; }
	void setDx(int newDx) { dx = newDx; }
	void setDy(int newDy) { dy = newDy; }

private:
	// Movimiento
	void moveMario();

	//Ca das
	bool checkFall();
};

#endif	