#include "Goomba.h"
#include "Game.h"
#include "Block.h"

Goomba::Goomba(Game* g, Point2D<double> p, Texture* t, Vector2D<double> s)
	: Enemy(g, p, t, s)
{
	frame = 0;
	frameTimer = 0;
}

SceneObject* Goomba::clone() const
{
	return new Goomba(*this);
}

void Goomba::render()
{
	Enemy::render();
	updateAnim();
}


void Goomba::update()
{
	Enemy::update();
}

void Goomba::collisionResult()
{

}

void Goomba::updateAnim()
{
	frameTimer++;
	if (frameTimer >= 3) {
		frameTimer = 0;
		frame = (frame + 1) % 2;
	}
}
