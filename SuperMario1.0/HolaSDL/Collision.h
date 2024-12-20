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
};

#endif