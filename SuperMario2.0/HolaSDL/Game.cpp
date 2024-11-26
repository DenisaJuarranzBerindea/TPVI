#include "Game.h"

#include <string>
#include <iostream>
#include <istream>
#include "Player.h"

using namespace std;

struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Numero de frames por fila
	uint numRows;		// Numero de frames por columna
};

// Directorio raiz de los archivos de textura
const string textureRoot = "../assets/images/";

// Especificacion de las texturas del juego
const array<TextureSpec, Game::TextureName::NUM_TEXTURES> textureSpec{
	{
		{"background.png", 9, 7},
		{"mario.png", 12, 1},
		{"supermario.png", 22, 1},
		{"goomba.png", 3, 1},
		{"koopa.png", 4, 1},
		{"mushroom.png", 1, 1},
		{"blocks.png", 6, 1},
	
	}
};

Game::Game()
{
	cout << "Game constructor" << endl;

	int winX, winY; // Posición de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	// ERRORES DE SDL
	try
	{
		// crea la ventana
		window = SDL_CreateWindow("Super Mario", winX, winY, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

		// crea el renderer para la ventana
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (window == nullptr || renderer == nullptr)
			throw "Error cargando ventana de juego o renderer"s;
	}
	catch (...)
	{
		cout << "Error cargando ventana de juego o renderer";
		EndGame();
	}

	init();
}

Game::~Game()
{
	// Elimina los objetos del juego
	delete player;
	for (int i = 0; i < blocks.size(); i++)
	{
		delete blocks[i];
	}
	for (int i = 0; i < goombas.size(); i++)
	{
		delete goombas[i];
	}
	//for (int i = 0; i < koopas.size(); i++)
	//{
	//	delete koopas[i];
	//}
	//for (int i = 0; i < mushrooms.size(); i++)
	//{
	//	delete mushrooms[i];
	//}

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Inicialización
void Game::init()
{
	loadTextures();
	loadMap();
}

// Carga texturas, mapa y objetos
void Game::loadTextures()
{
	try {
     // bucle para rellenar el array de texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {
			// crea la textura con el url, width y height
			Texture* tex = new Texture(renderer,
				(textureRoot + textureSpec[i].name).c_str(),
				textureSpec[i].numRows,
				textureSpec[i].numColumns);
			// la mete en el array
			textures[i] = tex;

			if (textures[i] == nullptr)
			{
				cout << "Textura null";
			}
		}
		for (int i = 0; i < NUM_TEXTURES; i++) {
			if (textures[i] != nullptr) {
				cout << "Texture " << i << ": " << textureSpec[i].name << " loaded successfully." << endl;
			} else {
				cout << "Texture " << i << ": " << textureSpec[i].name << " failed to load." << endl;
			}
		}
	}
	catch (...) {
		std::cout << "Textura no encontrada" << " (fichero Game.cpp)" << endl;
		EndGame();
	}

	cout << endl;
}

void Game::loadMap()
{
	const string map = "../assets/maps/world1.csv";
	mapa = new Tilemap(map, this);
	cout << "Tilemap creado (fichero Game.cpp)" << endl;

	ifstream file("../assets/maps/world1.txt");
	string line;

	while (getline(file, line)) {
		stringstream lineStream(line);
		char tipo;
		lineStream >> tipo;

		cout << "Tipo: " << tipo << endl;

		switch (tipo) {
		case 'M': {
			player = new Player(lineStream, MARIO_SPEED_X, MARIO_SPEED_Y);
			cout << "Player creado en game.cpp, loadMap" << endl;
			break;
		}
		case 'B':
			block = new Block(this, lineStream);
			blocks.push_back(block);
			break;
		case 'G':
			goomba = new Goomba(this, lineStream);
			goombas.push_back(goomba);
			break;
		case 'K':
			break;
		case 'H':
			break;
		// Add more cases as needed
		default:
			break;
		}
	}
}

Texture* Game::getTexture(TextureName name) const
{
	cout << "Textura " << name << " cargada" << " (fichero Game.cpp)\n" << endl;
	return textures[name];
}

int Game::getMarioState()
{
	return player->getState(); 
}

// Loop del juego
void Game::run()
{

	cout << "Game running" << endl;
	// get ticks al inicio del bucle
	startTime = SDL_GetTicks();

	while (!exit)
	{
		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime > TIME_BY_FRAME) {
			update(); // actualiza todos los objetos de juego
			startTime = SDL_GetTicks();
		}
		render(); // renderiza todos los objetos de juego

		handleEvents();
	}
}

// Update
void Game::update()
{
	// Actualiza los objetos del juego
	player->update();

	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->update();
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->update();
	}

	for (int i = 0; i < koopas.size(); i++)
	{
		//koopas[i]->update();
	}
	
	//mushroom->update();

}

// Render
void Game::render() const
{
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	mapa->renderMapa();
	cout << "Check 1" << endl;
	player->render();
	cout << "Check 2" << endl;
	for (int i = 0; i < goombas.size(); i++)
	{
		//cout << "Render goomba" << endl;
		goombas[i]->render();
		//goombas[0]->printPos();
	}
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->render();
	}

	//for (int i = 0; i < koopas.size(); i++)
	//{
	//	koopas[i]->render();
	//}

	//mushroom->render();

	SDL_RenderPresent(renderer);
}

// Eventos
void Game::handleEvents()
{
	SDL_Event event; 

	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {

		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) EndGame();

		// MANEJO DE EVENTOS DE OBJETOS DE JUEGO
		else {
			mapa->handleEvents(event);
			player->handleEvents(event);
		// 	mushroom->handleEvents(event);
		//  koopa->handleEvents(event);
		// 
		//	for (int i = 0; i < goombas.size(); i++)
		//	{
		//		goombas[i]->handleEvents(event);
		//	}
		//
		//	for (int i = 0; i < blocks.size(); i++)
		//	{
		//		blocks[i]->handleEvents(event);
		//	}
		}
	}
}

Collision Game::checkCollision(const SDL_Rect& rect, bool fromPlayer) {
	
	Collision c;
	c.collides = false;
	c.damages = false;

	// hit mapa
	c = mapa->hit(rect, fromPlayer);
	if (c.collides) { return c; }

	// hit goombas
	/*for (int i = 0; i < goombas.size(); i++)
	{
		c = goombas[i]->hit(rect, fromPlayer);
		if (c.collides)
		{
			if (!c.damages)
			{
				goombas[i]->killGoomba();
			}
			else
			{
				player->damage();
			}

			return c;
		}
	}*/

	// hit blocks
	for (int i = 0; i < blocks.size(); i++)
	{
		c = blocks[i]->hit(rect, fromPlayer);

		if (c.collides)
		{
			if (c.collides && !c.damages && c.killBrick)
			{
				blocks[i]->setDead();
			}
			else if (c.collides && c.spawnSeta)
			{
				//Lógica seta
				blocks[i]->setaSpawn();

				//mushroom = new Mushroom(this, blockVec[i]->getPos());
				//setas.push_back(mushroom);
			}

			return c;
		}
	}

	return c;

}

// Fin juego
void Game::EndGame()
{
	exit = true;
}

// Vidas - salida por consola
void Game::playerLife()
{
	//cout << "VIDAS RESTANTES: " <<  << endl;
}

double Game::getMapOffset() { return mapOffset; }
void Game::setMapOffset(double par_) { mapOffset = par_; }