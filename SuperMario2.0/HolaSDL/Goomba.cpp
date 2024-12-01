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

/*Collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision c;

	// si hay colision
	if (SDL_HasIntersection(&rect, &colRect))
	{
		c.collides = true;

		// si se origina en mario...
		if (fromPlayer)
		{
			// si la colision es por: arr -> muere el goomba
			if (((rect.y - rect.h) <= colRect.y) && (rect.x >= colRect.x && rect.x <= (colRect.x + colRect.w)))
			{
				c.damages = false;
			}

			// otra colision -> hiere a mario
			else c.damages = true;
		}
		// si no... con el tilemap
		else
		{
			// choca por la izq -> va a der
			if (colRect.x <= (rect.x + rect.w))
			{
				dx = 1;
			}
			// choca por la der -> va a izq
			else if ((colRect.x + colRect.w) >= rect.x)
			{
				dx = -1;
			}
		}

	}
		return c;
}

void Goomba::moveGoomba()
{
	//cout << "Goomba update frozen = " << frozen << endl;
	//direction = Vector2D<int>(0, 0);
	dx = 0;
	dy = 0;

	if (!frozen)
	{
		//debug comprueba que el goomba no se mueve fuera de la pantalla
		//cout << (x * game->TILE_SIDE + texture->getFrameWidth() * 2) - (game->getMapOffset()) << endl;
		
		//direction = Vector2D<int>(-1, 0);
		dx = -1;
		dy = 0;

		//position.setX(position.getX() + (direction.getX() * speed));
		x += dx * speed;
	}

	//Animaciones
	if (x != 0)
	{
		frameTimer++;
		if (frameTimer >= 800) {  // Velocidad del ciclo
			frameTimer = 0;
			animationFrame = (animationFrame + 1) % 2;


			if (animationFrame == 0) goombaFrame = 1;
			else if (animationFrame == 1) goombaFrame = 0;
		}
	}
}*/

void Goomba::printPos() {
	cout << "x: " << x << ", y: " << y << endl;
}