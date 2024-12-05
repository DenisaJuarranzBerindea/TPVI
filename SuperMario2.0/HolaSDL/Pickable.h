#ifndef PICKABLE_H
#define PICKABLE_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "SceneObject.h"

class Game;

using uint = unsigned int;
using namespace std;

class Pickable : public SceneObject
{
public:
	Pickable(Game* g, Point2D<double> p, Texture* t);

	//virtual void render() override;
	virtual void update() override;
	virtual void updateAnim() override;

	virtual Collision hit(SDL_Rect rect, Collision::Target t) override;

	void manageCollisions(Collision c) override;

	//SceneObject* clone() const override;

protected:
	virtual void triggerAction() = 0;
};

#endif