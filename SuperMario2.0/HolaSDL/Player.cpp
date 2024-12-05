#include "Player.h"
#include "Game.h"

// Constructora
Player::Player(Game* g, Point2D<double> p, Texture* t, int l, Vector2D<double> s)
	: SceneObject(g, p, t, s), lifes(l)
{
	lifes = 3;
	canMove = true;
	velX = 6;
	grounded = false;
	jumping = false;

	walkFrame = 0;
	flipSprite = true;
	flip = SDL_FLIP_NONE;

	marioState = MARIO;
	textureM = game->getTexture(Game::MARIO);	   // textura inicial de mario
	textureS = game->getTexture(Game::SUPERMARIO); // textura supermario

	invencible = false;
	cout << "Player creado" << endl;
}

void Player::render() 
{
	SceneObject::render();
	updateAnim();
}

// Actualizacion a nivel logico
void Player::update()
{
	if (speed.getY() < game->SPEED_LIMIT)
		speed = speed + Vector2D<double>(0, game->GRAVITY);

	if (canMove)
		c = tryToMove(speed, Collision::ENEMIES);
	else if (!canMove && speed.getY() != 0)
		c = tryToMove({ 0, speed.getY() }, Collision::ENEMIES);

	if (c.vertical)
	{
		if (speed.getY() > 0)
		{
			grounded = true;
			jumping = false;
		}

		speed.setY(0);
	}

	if (speed.getX() > 0)
	{
		flip = SDL_FLIP_NONE;

		// Limites
		if (position.getX() - game->getMapOffset() >= game->WIN_WIDTH / 2
			&& game->getMapOffset() <= game->MAP_MAX_OFFSET)
		{
			game->setMapOffset(game->getMapOffset() + speed.getX());
		}
		canMove = true;
	}
	else if (speed.getX() < 0)
	{
		flip = SDL_FLIP_HORIZONTAL;

		if (position.getX() - game->getMapOffset() < game->TILE_SIDE) canMove = false;
	}

	updateTexture();

	checkFall();

	finishLevel();

	marioState = game->getMarioState();
}

// Actualizacion a nivel grafico
void Player::updateTexture()
{
	if (marioState == MARIO)
	{
		setScale(2);
		texture = textureM;
	}
	else
	{
		setScale(1.5);
		texture = textureS;
	}
}

// Comprueba colisiones y las maneja
Collision Player::hit(SDL_Rect region, Collision::Target target)
{
	Collision c;
	// Comprueba si hay colision
	SDL_Rect colRect = getCollisionRect();

	// si la colision es con los enemies
	if (target == Collision::PLAYER && SDL_HasIntersection(&colRect, &region))
	{
		manageDamage();
	}

	return game->NO_COLLISION; // constante Collision{}
}

// Input
void Player::handleEvent(const SDL_Event& event)
{
	// Recibe tecla
	SDL_Scancode key = event.key.keysym.scancode;

	// pulsar
	if (event.type == SDL_KEYDOWN)
	{
		// Izqd (A)
		if (key == SDL_SCANCODE_A)
		{
			speed.setX(-speed.getX());
			keyA = true;
		}
		// Dcha (D)
		else if (key == SDL_SCANCODE_D)
		{
			speed.setX(speed.getX());
			keyD = true;
		}
		// Abajo (S)
		else if (key == SDL_SCANCODE_S) keyS = true;

		// Salto (Space)
		else if (key == SDL_SCANCODE_SPACE)
		{
			keySpace = true;
			if (!jumping && grounded)
			{
				grounded = false;
				jumping = true;

				speed.setY(-30);
			}
		}
		// Salir (S)
		else if (key == SDL_SCANCODE_E) keyE = true;

		// Offset mapa (->)
		else if (key == SDL_SCANCODE_RIGHT) keyDcha = true;
	}

	// No pulsar
	else if (event.type == SDL_KEYUP)
	{
		// Izqd
		if (key == SDL_SCANCODE_A)
		{
			speed.setX(0);
			keyA = false;
		}
		// Dcha
		else if (key == SDL_SCANCODE_D)
		{
			speed.setX(0);
			keyD = false;
		}
		// Abjs
		else if (key == SDL_SCANCODE_S) keyS = false;

		// Salto
		else if (key == SDL_SCANCODE_SPACE) keySpace = false;

		// Salir
		else if (key == SDL_SCANCODE_E) keyE = false;

		// Offset mapa
		else if (key == SDL_SCANCODE_RIGHT) keyDcha = false;
	}
}

// Actualizacion animaciones
void Player::updateAnim()
{
	// Andando en el suelo
	if (speed.getX() != 0 && grounded)
	{
		frameTimer++;
		if (frameTimer >= 1)
		{
			frameTimer = 0;

			int cycleLength = invencible ? 4 : 5;
			walkFrame = (walkFrame + 1) % cycleLength;

			// Asigna el frame correspondiente
			if (walkFrame == 0 || walkFrame == (cycleLength - 1)) {
				frame = 2;
			}
			else if (walkFrame == 1) {
				frame = 3;
			}
			else if (walkFrame == 2) {
				frame = 4;
			}
			else if (invencible && walkFrame == 3) {
				frame = -1;
			}
		}
	}
	// Saltando 
	else if (!grounded) {
		frame = 6;
	}
	// Idle
	else {
		frame = 0;
	}
}

// Mapa
void Player::updateOffset()
{
	// No se sale por la izquierda
	if ((position.getX()) * game->TILE_SIDE <= game->getMapOffset() && speed.getX() < 0) position.setX(game->getMapOffset() / (double)game->TILE_SIDE);

	// si llega a la mitad actual en pantalla en ese momento
	// actualiza el offset

	int screenX = position.getX() * game->TILE_SIDE - game->getMapOffset();

	if (screenX > game->TILE_SIDE * game->WIN_WIDTH / 2 && game->getMapOffset() < game->MAP_MAX_OFFSET)
	{
		game->addMapOffset(1);
	}
}

// Caida por agujeros
void Player::checkFall()
{
	// Si se ha caído por un agujero
	if (position.getY() > deadH)
	{
		position.setY(10 * game->TILE_SIDE);
		game->setFallen(true);

		game->reloadWorld(to_string(game->getCurrentLevel()), "../assets/maps/world");
		game->setFallen(false);
		position.setX(20);
		marioState = MARIO;
		lifes--;

	}
}

// Salto
void Player::jump()
{
	if (!jumping && grounded)
	{
		grounded = false;
		jumping = true;

		speed.setY(-speed.getY());
	}
}

// Gestion colisiones externas
void Player::manageCollisions(Collision collision)
{
	if (collision.target == Collision::PLAYER)
	{
		if (collision.result == Collision::DAMAGE)
		{
			manageDamage();
		}
	}
}

// Gestion daño
void Player::manageDamage()
{
	// No lo acaban de pegar
	if (!invencible)
	{
		if (marioState == SUPERMARIO)
		{
			marioState = MARIO;
		}
		else
		{
			if (lifes > 0)
			{
				invencible = true;
				lifes--;
			}

			if (lifes <= 0) isAlive = false;
		}
	}

	// Como le acaban de pegar...
	invencible = true;
}

// Gestion invencible (tras colision)
void Player::manageInvencible()
{
	if ((invCounter < maxInvCounter) && invencible)
	{
		invCounter++;
	}
	else
	{
		invCounter = 0;
		invencible = false;
	}
}

void Player::finishLevel()
{
	if (position.getX() >= flagPosition && game->getCurrentLevel() == 1)
	{
		cout << "FINAL" << endl;
		game->setCurrentLevel(game->getCurrentLevel() + 1);
		game->setVictory(true);

		if (game->getCurrentLevel() > game->getMaxWorlds())
		{
			game->EndGame();

		}
		else
		{
			game->loadLevel(to_string(game->getCurrentLevel()), "../assets/maps/world");
		}
	}
}

//SceneObject* Player::clone() const
//{
//	return new Player(*this);
//}
