#ifndef Goomba_h
#define Goomba_h

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "Enemy.h"

class Game;

using uint = unsigned int;
using namespace std;

class Goomba : public Enemy
{
private:

public:
	Goomba(Game* g, Point2D<double> p, Texture* t, Vector2D<double> s);

	void render() override;
	void update() override;

	SceneObject* clone() const override;

	virtual void collisionResult() override;

	virtual void updateAnim() override;

};

#endif