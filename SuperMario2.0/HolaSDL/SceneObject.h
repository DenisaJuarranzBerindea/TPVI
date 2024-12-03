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
	Texture* texture; // no se como pasar la informacion de la textura asi que la inicializo en el tryToMove

	SDL_Rect rectCol;
public:
	virtual Collision hit(SDL_Rect, Collision::Target) = 0;
	//virtual void handleEvents(const SDL_Event& event) = 0;
	void setListAnchor(GameList<SceneObject>::anchor&& anchor);
protected:
	Collision tryToMove(const Vector2D<double>& speed, Collision::Target target, Texture* texture);
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;

	GameList<SceneObject>::anchor anchor;
};

#endif