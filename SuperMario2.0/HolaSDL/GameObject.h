#ifndef GameObject_h
#define GameObject_h

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"

class Game;

class GameObject
{
public:
	//Estos métodos no tienen implementación, se overridean desde cada GO.
	GameObject(Game* game);

	// Destructora virtual
	virtual ~GameObject();

	// Render
	virtual void render() = 0;

	// Update
	virtual void update() = 0;

protected:
	Game* game;

};

#endif