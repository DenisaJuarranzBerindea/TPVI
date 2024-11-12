#include "Player.h"
#include "Game.h" // para evitar inclusiones cruzadas


Player::Player(Game* game, std::istream& in, double speedX_, double speedY_)
	: g(game), speed(speedX_, speedY_)
{

	cout << "Llamando constructor player" << endl;
	double tempX, tempY;
	in >> tempX >> tempY >> lifes;
	position = Point2D<double>(tempX, tempY) - Point2D<double>(0, 1); // coloca bien a mario //en world1.txt, y = 14
	direction = Vector2D<int>(0, 0);
	
	//double fallSpeed = speed.getY();

	texture = g->getTexture(Game::TextureName::MARIO); // textura inicial de mario

	marioState = 'm';
}

void Player::render() const
{
	SDL_Rect destRect = SDL_Rect();

	// tamano
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX() * (double)(g->TILE_SIDE) - g->getMapOffset();
	destRect.y = position.getY() * (double)(g->TILE_SIDE);

	// Usa el flip segun la direccion
	SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	texture->renderFrame(destRect, 0, marioFrame, 0.0, nullptr, flip);
}

void Player::update()
{
	//cout << (position.getX() * g->TILE_SIDE) - g->getMapOffset() << endl;
	//cout << (getX() * g->TILE_SIDE) - g->getMapOffset() << endl;
	
	Vector2D<double> tempSpeed = speed;
	bool canMoveX = true;
	bool canMoveY = true;

	colRect.h = texture->getFrameHeight();
	colRect.w = texture->getFrameWidth();
	SDL_Rect tempCol = colRect;

	colRect.y = position.getY() * (double)(g->TILE_SIDE) - direction.getY() * speed.getY();
	collisionMario = g->checkCollision(colRect, true);
	if (collisionMario.collides) {
		//cout << "Colisionando en Y" << endl;
		grounded = true;
		isFalling = false;

		canMoveY = false;
		colRect = tempCol;
	}

	colRect.x = position.getX() * (double)(g->TILE_SIDE) + direction.getX() * speed.getX();
	collisionMario = g->checkCollision(colRect, true);
	if (collisionMario.collides) {
		cout << "Colisionando en X" << endl;
		canMoveX = false;
		colRect = tempCol;
	}

	moveMario(canMoveX, canMoveY);
	updateOffset();
	updateAnims();

	speed = tempSpeed;
	canMoveX = true;
	canMoveY = true;

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
	// si llega a la mitad actual en pantalla en ese momento
	// actualiza el offset

	//cout << x * g->TILE_SIDE - g->getMapOffset() << " > " << g->WIN_WIDTH / 2 << endl;
	if (position.getX() * g->TILE_SIDE - g->getMapOffset() > g->WIN_WIDTH / 2.) g->setMapOffset(position.getX() * (double)g->TILE_SIDE - g->WIN_WIDTH / 2.);


}

bool Player::checkFall()
{
	return (position.getY() * g->TILE_SIDE - g->getMapOffset()) >= g->WIN_HEIGHT + texture->getFrameHeight();
}

void Player::moveMario(bool canMoveX, bool canMoveY)
{
	if (keyA == keyD) {
		direction = Vector2D<int>(0, 0);
	}

	else if (keyA != keyD) {
		//cout << dx << " " << x << endl;
		if (keyA) {
			direction = Vector2D<int>(-1, 0);
			flipSprite = true;  // Activa el flip al mover a la izquierda
		}
		else if (keyD) {
			direction = Vector2D<int>(1, 0);
			flipSprite = false; // Desactiva el flip al mover a la derecha
		}
	}

	if (canMoveX) position.setX(position.getX() + (direction.getX() * speed.getX()));
	
	if (keySpace && grounded && !isFalling) {
		direction.setY(-1);
		maxHeight = position.getY() - 4.;
		grounded = false;
		cout << 'S' << endl;
	}
	else direction.setY(0);

	if (position.getY() > maxHeight && keySpace && !isFalling && (canMoveY || direction.getY() == -1)) { //saltando dirY es -1
		position.setY(position.getY() - speed.getY());
	}
	//si se puede mover y su direccion es para abajo, caer
	else if (canMoveY && (position.getY() <= maxHeight || direction.getY() == 0)) { //cayendo dirY es 0
		isFalling = true;
		position.setY(position.getY() + fallSpeed);
	}

	//if (position.getX() < 0) position.setX(0);
	if (position.getX() * (double)g->TILE_SIDE - g->getMapOffset() <= 0 && direction.getX() == -1) position.setX(g->getMapOffset() / (double)g->TILE_SIDE);
	if (position.getX() * (double)g->TILE_SIDE + g->WIN_WIDTH >= 220*g->TILE_SIDE && direction.getX() == 1) position.setX(-0.00001 + (220 * g->TILE_SIDE - g->WIN_WIDTH) / (double)g->TILE_SIDE);

	if (position.getY() > 14.5) {
		position.setY(10);
		g->setMapOffset(0);
		position.setX(1);
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
