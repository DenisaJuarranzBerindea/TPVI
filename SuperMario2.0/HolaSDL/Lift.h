#ifndef LIFT_H
#define LIFT_H

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

class Lift : public SceneObject
{
private:

public:
	Lift(Game* g, Point2D<double> p, Texture* t, Vector2D<double> s);

	void render() override;
	void update() override;
	void updateAnim() override;

	Point2D<double> getPos() const { return position; }

	SceneObject* clone() const override;

	Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	void manageCollisions(Collision c) override;

private:
	void moveLift();

};

#endif