#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include "Vector2D.h"

struct Collision {
    bool collides = false;
    bool damages = false;        // indica si la colision implica danio
    
    SDL_Rect intersection;       // rectangulo de interseccion de la colision
    void* collider = nullptr;    // puntero al objeto con el que se colisiono

    operator bool() const { return collides; }

    // BLOQUES
    bool killBrick = false;

    // SETAS
    bool evolMario = false;
    bool spawnSeta = false;

	// ¿A quién afecta esta colisión? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparaszón opciona).
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisión
	enum Result {
		NONE,		// no ha habido colisión
		DAMAGE,		// la colisión produce daño
		OBSTACLE,	// la colisión impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisión horizontal
	int vertical = 0;     // profundidad de la colisión vertical
};

#endif