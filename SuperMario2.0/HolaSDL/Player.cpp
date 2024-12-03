#include "Player.h"
#include "Game.h"

Player::Player(Game* game_, std::istream& in)
{

	game = game_;

	cout << "Llamando constructor player" << endl;
	double tempX, tempY;
	in >> tempX >> tempY >> lifes;
	position = Point2D<double>(tempX, tempY) - Point2D<double>(0, 1); // coloca bien a mario

	speed = Vector2D<double>(X_SPEED, Y_SPEED);
	
	texture = game->getTexture(Game::TextureName::MARIO); // textura inicial de mario

	marioState = 'm';

	cout << "Player creado" << endl;
}

void Player::render() const
{
	SDL_Rect destRect = SDL_Rect();

	// tamano
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX() * (double)(game->TILE_SIDE) - game->getMapOffset();
	destRect.y = position.getY() * (double)(game->TILE_SIDE);

	// Usa el flip segun la direccion
	SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	texture->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
}

void Player::update()
{
	colRect.h = texture->getFrameHeight();
	colRect.w = texture->getFrameWidth();

	moveMarioY();
	moveMarioX();

	//Orden: tryToMove, game->checkCollision, mapa->hit
	Collision move = tryToMove(speed, Collision::ENEMIES, texture); // no encuentro otra forma de pasarle los datos que pasarle la texture

	if (move.result != Collision::NONE) {
		speed.setY(0);

		//Distinguir si es por arriba o por abajo para cambiar grounded/canJump
		if (move.vertical < 0) { //por abajo
			canJump = true;
			grounded = true;
		}
		else if (move.vertical > 0) { //por arriba
			canJump = false;
		}
	}
	position.setY(position.getY()/* + speed.getY()*/);

	if (move.horizontal) {
		cout << "Colision horizontal" << endl;
		speed.setX(0);
	}
	position.setX(position.getX() + speed.getX());
	
	updateOffset();
	updateAnims();

	//vidas (a futuro) // vidas por update
	//if (lifes > 0) lifes--;
	//else isAlive = false;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Collision Player::hit(SDL_Rect, Collision::Target) //no es necesario, implementado para que funcione herencia, preguntar
{
	return Collision();
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
		if (frameTimer >= 50) {  // Velocidad del ciclo
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
	// No se sale por la izquierda
	if ((position.getX()) * game->TILE_SIDE <= game->getMapOffset() && speed.getX() < 0) position.setX(game->getMapOffset() / (double)game->TILE_SIDE);

	// Mueve offset
	int mitad = game->getMapOffset() + game->WIN_WIDTH / 2.;
	if (position.getX() * game->TILE_SIDE > mitad) {
		game->setMapOffset(position.getX() * (double)game->TILE_SIDE - game->WIN_WIDTH / 2.);
	}
	
	// Agujeros
	if (position.getY() > 14.5) {
		position.setY(2);
		//game->setMapOffset(0); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//position.setX(1);
	}

	// Cambio de mapa
	if (position.getX() * (double)game->TILE_SIDE + game->WIN_WIDTH >= 215 * game->TILE_SIDE && speed.getX() > 0) {
		game->cambioMapa = true;
		game->map += 1;
	}


}

void Player::moveMarioX()
{
	if (keyA == keyD) {
		speed.setX(0);
	}

	else if (keyA != keyD) {
		if (keyA) {
			speed.setX(-X_SPEED);
			flipSprite = true;  // Activa el flip al mover a la izquierda
		}
		else if (keyD) {
			speed.setX(X_SPEED);
			flipSprite = false; // Desactiva el flip al mover a la derecha
		}
	}
}

void Player::moveMarioY()
{
	if (keySpace && grounded && canJump) {
		speed.setY(-Y_SPEED);
		maxHeight = position.getY() - 4;
		grounded = false;
	}

	if (canJump && keySpace) {
		speed.setY(-Y_SPEED);
	}
	
	if (!keySpace || position.getY() < maxHeight) {
		speed.setY(Y_SPEED /*+ GRAVITY*/);
		canJump = false;
	}
}

void Player::damage()
{
	if (marioState == 's')
	{
		marioState = 'm';
	}
	else
	{
		if (lifes > 0) lifes--;
		else isAlive = false;
	}
}
