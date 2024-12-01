#include "SceneObject.h"
#include "Game.h"


//SDL_Rect SceneObject::getRenderRect() const
//{
//	SDL_Rect rect = SDL_Rect();
//
//	rect.x = position.getX() * (double)(game->TILE_SIDE) - game->getMapOffset();
//	rect.y = position.getY() * (double)(game->TILE_SIDE) - texture->getFrameHeight();
//	rect.w = texture->getFrameWidth();
//	rect.h = texture->getFrameHeight();
//
//	return rect;
//}

SDL_Rect SceneObject::getCollisionRect() const
{
	SDL_Rect rect = SDL_Rect();

	rect.x = position.getX() * Game::TILE_SIDE;
	rect.y = position.getY() * Game::TILE_SIDE + texture->getFrameHeight();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	return rect;
}

Collision
SceneObject::tryToMove(const Vector2D<double>& speed, Collision::Target target, Texture* texture_)
{
	texture = texture_;

	Collision collision;
	SDL_Rect rect = getCollisionRect();

	//cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << " SceneObject.cpp/tryToMove" << endl;
	// Intenta moverse en vertical
	if (speed.getY() != 0) {

		rect.y += speed.getY();
		collision = game->checkCollision(rect, target);

		// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)

		double fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		position += {0, speed.getY() - fix};

		// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario
		rect.y -= fix; // recoloca la caja para la siguiente colisión
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	// (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
	if (speed.getX() != 0) {
		rect.x += speed.getX();
		Collision partial = game->checkCollision(rect, target);

		// Copia la información de esta colisión a la que se devolverá
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;
		double fix = collision.horizontal * (speed.getX() > 0 ? 1 : -1);
		position += {speed.getX() - fix, 0};
	}

	return collision;
}