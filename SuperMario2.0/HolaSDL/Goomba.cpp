#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* game_, std::istream& in) : SceneObject()
{

	game = game_;

	cout << "Llamando constructor goomba" << endl;
	double tempX, tempY;
	in >> tempX >> tempY;
	position = Point2D<double>(tempX, tempY) - Point2D<double>(0, 1); // coloca bien al goomba

	speed = Vector2D<double>(X_SPEED, Y_SPEED);

	texture = game->getTexture(Game::GOOMBA); // textura inicial de goomba

	cout << "Goomba creado" << endl;
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
	destRect.x = position.getX() * (double)(game->TILE_SIDE) - game->getMapOffset();
	destRect.y = position.getY() * (double)(game->TILE_SIDE);

	texture->renderFrame(destRect, 0, goombaFrame);
}

void Goomba::update()
{
	// si la pos del goomba es menor que el offset mas el ancho de la pantalla -> se activa
	if ((position.getX() * game->TILE_SIDE) - texture->getFrameWidth() < (game->getMapOffset() + game->WIN_WIDTH)) {
		frozen = false;
	}
	else frozen = true;

	if ((position.getX() * game->TILE_SIDE + texture->getFrameWidth() * 2) < (game->getMapOffset())) {
		frozen = true;
	}

	moveGoomba();

	//Orden: tryToMove, game->checkCollision, mapa->hit
	Collision move = tryToMove(speed, Collision::ENEMIES, texture); // no encuentro otra forma de pasarle los datos que pasarle la texture

	if (move.result != Collision::NONE) {
		speed.setY(0);
		grounded = true;
	}
	position.setY(position.getY() + speed.getY());

	if (move.horizontal) {
		speed.setX(0);
	}
	position.setX(position.getX() + speed.getX());

	//cout << "Update goomba" << endl;
}

Collision Goomba::hit(SDL_Rect rect, Collision::Target)
{
	Collision c;

	// si hay colision
	if (SDL_HasIntersection(&rect, &colRect))
	{
		c.collides = true;

		// si se origina en mario...
		if (Collision::Target::ENEMIES)
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
				speed.setX(X_SPEED);
			}
			// choca por la der -> va a izq
			else if ((colRect.x + colRect.w) >= rect.x)
			{
				speed.setX(-X_SPEED);
			}
		}

	}
		return c;
}

void Goomba::moveGoomba()
{
	//cout << "Goomba update frozen = " << frozen << endl;

	if (!frozen)
	{
		//debug comprueba que el goomba no se mueve fuera de la pantalla
		//cout << (x * game->TILE_SIDE + texture->getFrameWidth() * 2) - (game->getMapOffset()) << endl;
		
		speed.setX(-X_SPEED);
		speed.setY(Y_SPEED);
	}

	//Animaciones
	if (position.getX() != 0)
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
	cout << "x: " << position.getX() << ", y: " << position.getY() << endl;
}

Goomba::~Goomba() {

}