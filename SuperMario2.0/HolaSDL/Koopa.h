#ifndef Koopa_h
#define Koopa_h

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

class Koopa : public Enemy
{
private:


public:
	Koopa(Game* g, Point2D<double> p, Texture* t, Vector2D<double> s);

	void update() override;

	virtual void collisionResult() override;
	//SceneObject* clone() const override;

	void render() override;

	virtual void updateAnim() override;
};

#endif