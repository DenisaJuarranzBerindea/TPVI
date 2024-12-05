#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* g, Point2D<double> p, Texture* t, Vector2D<double> s)
	: SceneObject(g, p, t, s)
{
	setScale(2);
}

void Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (speed.getY() < game->SPEED_LIMIT)
		speed = speed + Vector2D<double>(0, game->GRAVITY);

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<double> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = game->MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal) speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad
	if (collision.vertical) speed.setY(0);

	// SceneObject::update(); // si hiciera falta
}

Collision Enemy::hit(SDL_Rect rect, Collision::Target t)
{
	// Calcula la interseccion
	SDL_Rect intersection;
	SDL_Rect colRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&colRect, &rect, &intersection);

	if (hasIntersection)
	{
		Collision c{ Collision::EMPTY, Collision::NONE, intersection.w, intersection.h };

		// si se origina en mario...
		if (t == Collision::ENEMIES)
		{
			c.result = Collision::DAMAGE;

			// si la colision es por: arr -> muere el enemigo
			if (((rect.y) >= colRect.y - colRect.h) && rect.y != colRect.y)
			{
				t = Collision::ENEMIES;
				delete this;
				cout << "Enemigo golpeado" << endl;
			}

			// otra colision -> hiere a mario
			else
			{
				t = Collision::PLAYER;
				cout << "Mario golpeado" << endl;
			}
		}

		return c;
	}

	return game->NO_COLLISION;
}

void Enemy::collisionResult()
{

}

void Enemy::manageCollisions(Collision c)
{

}

void Enemy::updateAnim()
{

}