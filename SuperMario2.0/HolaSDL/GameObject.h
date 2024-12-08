#ifndef GameObject_h
#define GameObject_h

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"

class Game;

class GameObject
{
protected:
	Game* game;

public:
	//Estos métodos no tienen implementación, se overridean desde cada GO.
	GameObject() {};
	GameObject(Game* g) : game(g) {};

	// Destructora virtual
	virtual ~GameObject() {};

	// Render
	virtual void render() = 0;

	// Update
	virtual void update() = 0;
};

#endif