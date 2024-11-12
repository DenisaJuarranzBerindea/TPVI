#include "Goomba.h"
#include "../Game.h"
#include "Block.h"

Goomba::Goomba(Game* g, std::istream& in)
	: game(g)
{
	cout << "Llamando constructor goomba" << endl;

	//in >> position;
	in >> x >> y;
	y -= 1;

	//direction = Vector2D<int>(0, 0);
	dx = 0;
	dy = 0;

	texture = game->getTexture(Game::GOOMBA); // textura inicial de goomba

	goombaFrame = 0;

	frozen = true;
	alive = true;
}

void Goomba::render() const
{
	SDL_Rect destRect;

	// tamano (son de 16*16, pero los queremos de 32*32, as� que * 2
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	//// posicion
	//destRect.x = (position.getX() * game->TILE_SIDE) - game->getMapOffset();
	//destRect.y = (position.getY() * game->TILE_SIDE);
	destRect.x = x * (double)(game->TILE_SIDE) - game->getMapOffset();
	destRect.y = y * (double)(game->TILE_SIDE);

	texture->renderFrame(destRect, 0, goombaFrame);
}

void Goomba::update()
{
	// si la pos del goomba es menor que el offset mas el ancho de la pantalla -> se activa
	if ((x * game->TILE_SIDE) - texture->getFrameWidth() < (game->getMapOffset() + game->WIN_WIDTH)) {
		frozen = false;
	}
	else frozen = true;

	if ((x * game->TILE_SIDE + texture->getFrameWidth() * 2) < (game->getMapOffset())) {
		frozen = true;
	}

	moveGoomba();

	colRect.h = texture->getFrameHeight() * 2;
	colRect.w = texture->getFrameWidth() * 2;
	colRect.x = x * game->TILE_SIDE;
	colRect.y = y * game->TILE_SIDE;
}

Collision Goomba::hit(const SDL_Rect& rect, bool fromPlayer)
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
}

void Goomba::printPos() {
	cout << "x: " << x << ", y: " << y << endl;
}