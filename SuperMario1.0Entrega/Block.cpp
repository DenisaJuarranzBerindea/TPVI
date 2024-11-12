#include "Block.h"
#include "Game.h"

Block::Block(Game* g, std::istream& in)
	: game(g)
{
	cout << "Llamando constructor block" << endl;
	//in >> position;
	//position = position - Point2D<double>(0, 1);
	in >> x >> y >> tipoL;
	y -= 1;
	if (tipoL != 'B') in >> accionL;

	// Asignamos el tipo de bloque basado en el car�cter le�do
	switch (tipoL) {
	case 'B':
		tipo = LADRILLO;
		blockFrame = 5;
		break;
	case '?':
		tipo = SORPRESA;
		blockFrame = 0;  // Comienza la animaci�n del bloque sorpresa desde el primer frame
		break;
	case 'H':
		tipo = OCULTO;
		blockFrame = 4;
		break;
	}

	// Asignamos la acci�n del bloque basado en el car�cter le�do
	switch (accionL) {
	case 'P':
		accion = POTENCIADOR;
		break;
	case 'C':
		accion = MONEDA;
		break;
	}

	texture = game->getTexture(Game::BLOCK); // textura inicial del bloque
	
}

void Block::render() const
{
	SDL_Rect destRect;

	// tamano (son de 16*16, pero los queremos de 32*32, as� que * 2
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	// posicion
	destRect.x = (x * (double)game->TILE_SIDE) - game->getMapOffset();
	destRect.y = (y * (double)game->TILE_SIDE);

	texture->renderFrame(destRect, 0, blockFrame);
}

void Block::update()
{
	if (tipo == SORPRESA) {
		frameTimer++;
		if (frameTimer >= 1050) {  // Velocidad del ciclo
			frameTimer = 0;
			animationFrame = (animationFrame + 1) % 3;  // Ciclo 0,1,2,3, y luego se reinicie 

			if (animationFrame == 0) blockFrame = 1;
			else if (animationFrame == 1) blockFrame = 2;
			else if (animationFrame == 2) blockFrame = 0;
		}
	}
}

Collision Block::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision c;
	c.collides = false;
	c.damages = false;

	// si hay colision
	if (SDL_HasIntersection(&rect, &colRect))
	{
		cout << "Colisiona con bloque" << endl;
		c.collides = true;
		c.damages = false;
		// si se origina en mario...
		if (fromPlayer)
		{
			// si la colision es por: abj 
			if (rect.y <= (colRect.y + colRect.h))
			{
				if (tipo == LADRILLO && (game->getMarioState() == 1))
				{
					c.killBrick = true;
				}
				else if (tipo == SORPRESA || tipo == OCULTO)
				{
					c.spawnSeta = true;
				}
			}
		}
	}
	return c;
}

void Block::setaSpawn()
{
	setTipo(3);
	blockFrame = 4;
}
