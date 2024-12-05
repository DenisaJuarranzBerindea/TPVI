#ifndef Mushroom_h
#define Mushroom_h

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "Pickable.h"

class Game;

using uint = unsigned int;
using namespace std;

class Mushroom : public Pickable
{
private:

	double moveDelay = 5;

public:
	Mushroom(Game* g, Point2D<double> p, Texture* t);

	void render() override;
	void update() override;
	void updateAnim() override;

	void moveSeta();

	void triggerAction() override;

	//SceneObject* clone() const override;

};

#endif