#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "Collision.h"

#include "Vector2D.h"

class Game;

class SceneObject : public GameObject {
protected:
	Point2D<double> position;
	double width;
	double height;
	Vector2D<double> speed;

	SDL_Rect rectCol;
public:
	virtual Collision hit(SDL_Rect, bool) = 0;
protected:
	Collision tryToMove(const Vector2D<double>& speed, Collision::Target target);
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
};

#endif