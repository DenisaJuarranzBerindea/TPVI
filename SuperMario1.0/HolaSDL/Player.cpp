#include "Player.h"
#include "../Game.h" // para evitar inclusiones cruzadas


Player::Player(Game* game, int x_, int y_, int lifes_, double speed_)
	: g(game), lifes(lifes_), speed(speed_)
{
	cout << "Llamando constructor player" << endl;
	//position = Point2D<double>(x_, y_) - Point2D<double>(0, 1); // coloca bien a mario
	//direction = Vector2D<int>(0, 0);
	setX(x_);
	setY(y_ - 1);
	setDx(0);
	setDy(0);

	texture = g->getTexture(Game::TextureName::MARIO); // textura inicial de mario

	//marioState = 'm';

	//groundedYPos = position.getY();
	groundedYPos = getY();
}

void Player::render() const
{
	SDL_Rect destRect = SDL_Rect();

	// tamano
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	//destRect.x = (position.getX() * g->TILE_SIDE) - g->getMapOffset();
	//destRect.y = (position.getY() * g->TILE_SIDE);

	destRect.x = getX() * g->TILE_SIDE - g->getMapOffset();
	destRect.y = getY() * g->TILE_SIDE;

	texture->renderFrame(destRect, 0, marioFrame);

	// Usa el flip segun la direccion
	SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	texture->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
}

void Player::update()
{
	moveMario();

	updateOffset();

	updateAnims();
	//cout << (position.getX() * g->TILE_SIDE) - g->getMapOffset() << endl;
	cout << (getX() * g->TILE_SIDE) - g->getMapOffset() << endl;

}

void Player::handleEvents(const SDL_Event& event)
{
	// Recibe tecla
	SDL_Scancode key = event.key.keysym.scancode;

	// pulsar
	if (event.type == SDL_KEYDOWN)
	{
		// IZQD
		if (key == SDL_SCANCODE_A) keyA = true;

		// DCHA
		else if (key == SDL_SCANCODE_D) keyD = true;

		// ABAJO
		else if (key == SDL_SCANCODE_S) keyS = true;

		// SALTAR
		else if (key == SDL_SCANCODE_SPACE) keySpace = true;

		// SALIR
		else if (key == SDL_SCANCODE_E) keyE = true;

	}

	// despulsar
	else if (event.type == SDL_KEYUP)
	{
		// IZQ
		if (key == SDL_SCANCODE_A) keyA = false;

		// DER
		else if (key == SDL_SCANCODE_D) keyD = false;

		// ABJ
		else if (key == SDL_SCANCODE_S) keyS = false;

		// SALTAR
		else if (key == SDL_SCANCODE_SPACE) keySpace = false;

		// SALIR
		else if (key == SDL_SCANCODE_E) keyE = false;

	}
}

void Player::hit(SDL_Rect* rect)
{
	if (lifes > 0) lifes--;
	else isAlive = false;
}

void Player::updateAnims()
{
	if (!grounded) {
		//Frame del salto
		marioFrame = 6;
	}
	else if (keyA != keyD) {
		frameTimer++;
		if (frameTimer >= 200) {  // Velocidad del ciclo
			frameTimer = 0;
			animationFrame = (animationFrame + 1) % 4;  // Ciclo 0,1,2,3, y luego se reinicie 

			// Ciclo de caminar 2 -> 3 -> 4 -> 3
			if (animationFrame == 0 || animationFrame == 3) marioFrame = 2;
			else if (animationFrame == 1) marioFrame = 3;
			else if (animationFrame == 2) marioFrame = 4;
		}
	}
	else {
		//Cuando esta quieto
		marioFrame = 0;
	}
}

void Player::updateOffset()
{
	// si llega a la mitad actual en pantalla en ese momento
	// actualiza el offset

	//int screenX = position.getX() * g->TILE_SIDE - g->getMapOffset();
	int screenX = getX() * g->TILE_SIDE - g->getMapOffset();

	if (screenX > g->TILE_SIDE * g->WIN_WIDTH / 2) {
		g->setMapOffset(g->getMapOffset() + g->TILE_SIDE * speed); // + g->TILE_SIDE * speed ??
	}
}

bool Player::checkFall()
{
	//return (position.getY() * g->TILE_SIDE - g->getMapOffset()) >= g->WIN_HEIGHT + texture->getFrameHeight();
	return (getY() * g->TILE_SIDE - g->getMapOffset()) >= g->WIN_HEIGHT + texture->getFrameHeight();
}

void Player::moveMario()
{
	if (keyA == keyD) {
		//direction = Vector2D<double>(0, 0);
		setDx(0);
		setDy(0);
	}

	if (keyA != keyD) {
		if (keyA) {
			//direction = Vector2D<double>(-1, 0);
			setDx(-1);
			setDy(0);
			flipSprite = true;  // Activa el flip al mover a la izquierda
		}
		else if (keyD) {
			//direction = Vector2D<double>(1, 0);
			setDx(1);
			setDy(0);
			flipSprite = false; // Desactiva el flip al mover a la derecha
		}
	}

	if (keySpace && grounded && !canJump) {
		//direction = Vector2D<int>(0, -1);
		setDx(0);
		setDy(-1);
		//maxHeight = position.getY() - 3;
		maxHeight = getY() - 3;
		grounded = false;
		isFalling = false;
	}

	//position.setX(position.getX() + (direction.getX() * speed * 0.3));
	setX(getX() + (getDx() * speed * 0.3));

	if (!grounded) {
		if (!isFalling && getY() > maxHeight) { //(!isFalling && position.getY() > maxHeight)
			//position.setY(position.getY() - speed * 0.3);
			setY(getY() - speed * 0.3);
		}
		else {
			isFalling = true;
			//position.setY(position.getY() + speed * 0.3);
			setY(getY() + speed * 0.3);
		}

		if (getY() >= groundedYPos) { //(position.getY() >= groundedYPos)
			//position.setY(groundedYPos);
			setY(groundedYPos);
			grounded = true;
			isFalling = false;
		}
	}

	//if (position.getX() < 0) position.setX(0);
	if (getX() < 0) setX(0);

	canJump = keySpace;
}
