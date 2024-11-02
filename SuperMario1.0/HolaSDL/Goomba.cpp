#include "Goomba.h"
#include "../Game.h"

Goomba::Goomba(Game* g, std::istream& in, double(_speed), int _x, int _y) 
	: game(g), speed(_speed)
{
	cout << "Llamando constructor goomba" << endl;

	//in >> position;
	//direction = Vector2D<int>(0, 0);
	x = _x;
	y = _y - 1;
	dx = 0;
	dy = 0;

	texture = game->getTexture(Game::GOOMBA); // textura inicial de mario

	goombaFrame = 0;

	frozen = true;
	alive = true;
}

void Goomba::render() const
{
	SDL_Rect destRect;

	// tamano (son de 16*16, pero los queremos de 32*32, así que * 2
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
	if ((x * 32) - texture->getFrameWidth() < (game->getMapOffset() + game->WIN_WIDTH))
	{
		frozen = false;
	}

	moveGoomba();
}

void Goomba::hit(SDL_Rect* rect)
{

}

void Goomba::moveGoomba()
{
	//direction = Vector2D<int>(0, 0);
	dx = 0;
	dy = 0;

	if (!frozen)
	{
		//direction = Vector2D<int>(-1, 0);
		dx = -1;
		dy = 0;

		//position.setX(position.getX() + (direction.getX() * speed));
		x = dx + x * speed;
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