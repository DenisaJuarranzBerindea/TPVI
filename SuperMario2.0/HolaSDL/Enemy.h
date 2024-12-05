#ifndef ENEMY_H
#define ENEMY_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "SceneObject.h"
#include "Collision.h"

class Game;

using uint = unsigned int;
using namespace std;

class Enemy : public SceneObject
{
private:

	bool frozen; 
	bool alive;

	bool grounded;
	double moveDelay = 5;

public:
	// Constructora
	Enemy(Game* g, Point2D<double> p, Texture* t, Vector2D<double> s);

	// Update
	virtual void update() override;

	// Hit
	virtual Collision hit(SDL_Rect rect, Collision::Target t) override;

	//virtual Collision tryToMove(Vector2D<int>& v, Collision::Target t) override;

	virtual void collisionResult();

	virtual void manageCollisions(Collision c) override;

	//SceneObject* clone() const override;
	virtual void updateAnim() override;
};

#endif