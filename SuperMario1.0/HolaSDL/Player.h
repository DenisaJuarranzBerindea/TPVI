#ifndef PLAYER_H
#define PLAYER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
//#include "Texture.h"
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
	//Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	int maxLifes = 3;
	int lifes;					// numero de vidas restantes, 3 al inicio

	bool isAlive = true;

	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<int> direction;	// direccion de movimiento
	float speed = 0.05;			// velocidad de movimiento

	bool grounded;		// si esta en el suelo, solo puede saltar cuando lo este
	int groundedYPos;	// posicion en el suelo
	int maxHeight;

	//char marioState; // m(mario), s(supermario)

	// ANIMACION
	int marioFrame;

	// INPUT
	bool keyA = false, //Izqd
		keyD = false, //Dcha
		keyS = false, //Abajo
		keySpace = false, //Salto
		keyE = false; //Salir
		

	// rect destino
	//SDL_Rect destRect;

	bool isFalling = false;
	bool canJump = false;
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;
	bool flipSprite = false;

public:
	//Constructora
	Player(Game* g, std::istream& i); // La textura tambíén?

	// Render
	void render() const;
	// Actualización
	void update();
	// Eventos, sobre todo input   
	void handleEvents(const SDL_Event& event);
	// Colisiones
	void hit(SDL_Rect* rect);

	// Animaciones
	void updateAnims();
	// Para bloquear pantalla cuando avanza
	void updateOffset();

private:
	// Movimiento
	void moveMario();

	//Caídas
	bool checkFall();
};

#endif	