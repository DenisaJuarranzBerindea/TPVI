#include "Player.h"
#include "../Game.h" // para evitar inclusiones cruzadas


Player::Player(Game* game, std::istream& in, double speed_)
	: g(game), speed(speed_)
{

	cout << "Llamando constructor player" << endl;
	//position = Point2D<double>(x_, y_) - Point2D<double>(0, 1); // coloca bien a mario
	//direction = Vector2D<int>(0, 0);
	in >> x >> y >> lifes;
	y -= 1;
	dx = 0;
	dy = 0;

	texture = g->getTexture(Game::TextureName::MARIO); // textura inicial de mario

	marioState = 'm';

	//groundedYPos = position.getY();
	groundedYPos = y;
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

	destRect.x = x * (double)(g->TILE_SIDE) - g->getMapOffset();
	destRect.y = y * (double)(g->TILE_SIDE);

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
	//cout << (getX() * g->TILE_SIDE) - g->getMapOffset() << endl;
	
	colRect.h = texture->getFrameHeight();
	colRect.w = texture->getFrameWidth();

	// posicion
	//destRect.x = (position.getX() * g->TILE_SIDE) - g->getMapOffset();
	//destRect.y = (position.getY() * g->TILE_SIDE);


	colRect.y = y * (double)(g->TILE_SIDE) - dy * speed; //corregir a speed.x y speed.y

	collisionMario = g->checkCollision(colRect, true);

	colRect.x = x * (double)(g->TILE_SIDE) - g->getMapOffset() + dx * speed;

	collisionMario = g->checkCollision(colRect, true);

	//vidas (a futuro) // vidas por update
	//if (lifes > 0) lifes--;
	//else isAlive = false;
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

	//cout << x * g->TILE_SIDE - g->getMapOffset() << " > " << g->WIN_WIDTH / 2 << endl;
	if (x * g->TILE_SIDE - g->getMapOffset() > g->WIN_WIDTH / 2.) g->setMapOffset(x * (double)g->TILE_SIDE - g->WIN_WIDTH / 2.);


}

bool Player::checkFall()
{
	//return (position.getY() * g->TILE_SIDE - g->getMapOffset()) >= g->WIN_HEIGHT + texture->getFrameHeight();
	return (y * g->TILE_SIDE - g->getMapOffset()) >= g->WIN_HEIGHT + texture->getFrameHeight();
}

void Player::moveMario()
{
	if (keyA == keyD) {
		//direction = Vector2D<double>(0, 0);
		dx = 0;
		dy = 0;
	}

	else if (keyA != keyD) {
		//cout << dx << " " << x << endl;
		if (keyA) {
			//direction = Vector2D<double>(-1, 0);
			dx = -1;
			dy = 0;
			flipSprite = true;  // Activa el flip al mover a la izquierda
		}
		else if (keyD) {
			//direction = Vector2D<double>(1, 0);
			dx = 1;
			dy = 0;
			flipSprite = false; // Desactiva el flip al mover a la derecha
		}
	}

	if (keySpace && grounded) { 
		//direction = Vector2D<int>(0, -1);
		dx = 0;
		dy = -1;
		//maxHeight = position.getY() - 3;
		maxHeight = y - 4.0;
		grounded = false;
		isFalling = false;
	}

	//position.setX(position.getX() + (direction.getX() * speed * 0.3));
	x += (dx * speed);

	if (!grounded) {
		if (!isFalling && y > maxHeight) { //(!isFalling && position.getY() > maxHeight)
			//position.setY(position.getY() - speed * 0.3);
			y -= speed;
		}
		else {
			isFalling = true;
			//position.setY(position.getY() + speed * 0.3);
			y += speed;
		}

		if (y >= groundedYPos) { //(position.getY() >= groundedYPos)
			//position.setY(groundedYPos);
			y = groundedYPos;
			grounded = true;
			isFalling = false;
		}
	}

	//if (position.getX() < 0) position.setX(0);
	if (x * (double)g->TILE_SIDE - g->getMapOffset() <= 0 && dx == -1) x = g->getMapOffset() / (double)g->TILE_SIDE;
	if (x * (double)g->TILE_SIDE + g->WIN_WIDTH >= 220*g->TILE_SIDE && dx == 1) x = -0.00001 + (220 * g->TILE_SIDE - g->WIN_WIDTH) / (double)g->TILE_SIDE;
	//canJump = keySpace;
}
