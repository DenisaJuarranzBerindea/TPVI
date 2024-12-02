#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include "Vector2D.h"

struct Collision {
	bool collides = false;
	bool damages = false;        // indica si la colision implica danio
    
	SDL_Rect intersection = SDL_Rect();       // rectangulo de interseccion de la colision
	void* collider = nullptr;    // puntero al objeto con el que se colisiono

	// �A qui�n afecta esta colisi�n? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparasz�n opciona).
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisi�n
	enum Result {
		NONE,		// no ha habido colisi�n
		DAMAGE,		// la colisi�n produce da�o
		OBSTACLE,	// la colisi�n impide el movimiento
		ACTION,
	};

	Result result = NONE;
	double horizontal = 0;   // profundidad de la colisi�n horizontal
	double vertical = 0;     // profundidad de la colisi�n vertical

	operator bool() const { return collides; }
};

#endif