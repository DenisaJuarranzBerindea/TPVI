#ifndef GameObject_h
#define GameObject_h

#include "Game.h"

class Game;

class GameObject
{
public:
	//Estos m�todos no tienen implementaci�n, se overridean desde cada GO.
	virtual void render() const = 0;
	virtual void update() = 0;
	
	virtual ~GameObject() = default;

protected:
	Game* game;
	GameObject(Game* g) : game(g) {};

};

#endif