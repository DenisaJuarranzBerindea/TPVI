#include "checkML.h"
#include "Lift.h"
#include "Game.h"
#include "Collision.h"

Lift::Lift(Game* g, Point2D<double> p, Texture* t, Vector2D<double> s)
	: SceneObject(g, p, t, s)
{
	direction = Vector2D<int>(0, 1);
}

void Lift::render()
{
	texture->render(colRect);
}

void Lift::update()
{
	moveLift();
}

void Lift::updateAnim()
{

}

SceneObject* Lift::clone() const
{
	return new Lift(*this);
}

Collision Lift::hit(SDL_Rect rect, Collision::Target t)
{
	return Collision();
}

void Lift::manageCollisions(Collision c)
{

}

void Lift::moveLift()
{
	// se sale por abajo || se sale por arriba
	if (position.getY() > game->WIN_HEIGHT || position.getY() + colRect.h < 0)
	{
		direction.setY(direction.getY() * -1);
	}

	position.setY(position.getY() + (direction.getY() * speed.getY()));
}