#include "Game.h"

#include <string>
#include <iostream>
#include <istream>

#include "Tilemap.h"


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
		{"coin.png", 4, 1},
		{"lift.png", 1, 1}
	}
};

Game::Game()
{
	cout << "Game constructor" << endl;

	nextObject = 0;
	maxWorlds = 3;
	currentWorld = 1;
	isVictory = false;
	marioState = 0;
	mapOffset = 0;

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
	// Elimina las texturas
	for (Texture* texture : textures) delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Inicialización
void Game::init()
{
	loadTextures();
	loadLevel(to_string(currentWorld), "../assets/maps/world");
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

void Game::loadMap(std::ifstream& mapa)
{
	cout << "Tilemap creado (fichero Game.cpp)" << endl;

	string line;

	int i = 0;
	while (getline(mapa, line)) {
		stringstream lineStream(line);

		// Color fondo
		if (i == 0)
		{
			lineStream >> r >> g >> b;
		}

		Point2D<double> pos;
		char tipo;
		lineStream >> tipo;

		cout << "Tipo: " << tipo << endl;

		// Mario
		if (tipo == 'M' && !fallen)
		{
			int lifes;
			cout << fallen << endl;
			lineStream >> pos;

			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			lineStream >> lifes;

			if (player == nullptr)
			{
				cout << "Nuevo jugador" << endl;
				//player = new Player(this, pos, getTexture(MARIO), lifes, Vector2D<double>(0, 0));
				objectQueue.push_back(new Player(this, pos, getTexture(MARIO), lifes, Vector2D<double>(0, 0)));
			}
		}
		//Goomba
		else if (tipo == 'G')
		{
			lineStream >> pos;

			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			//goomba = new Goomba(this, pos, getTexture(GOOMBA), Vector2D<double>(-7, 0));
			objectQueue.push_back(new Goomba(this, pos, getTexture(GOOMBA), Vector2D<double>(-7, 0)));
		}
		//Block
		else if (tipo == 'B')
		{
			char tipoL;
			char accionL;

			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			lineStream >> tipoL;
			lineStream >> accionL;

			//block = new Block(this, pos, getTexture(BLOCK), tipoL, accionL);
			objectQueue.push_back(new Block(this, pos, getTexture(BLOCK), tipoL, accionL));
		}
		//Koopa
		else if (tipo == 'K')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - (TILE_SIDE * 2));

			//SceneObject* koopa = new Koopa(this, pos, getTexture(KOOPA), Vector2D<double>(-7, 0));
			objectQueue.push_back(new Koopa(this, pos, getTexture(KOOPA), Vector2D<double>(-7, 0)));
		}
		// Lift
		/*else if (tipo == 'L')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);


			Vector2D<int> speed;
			double x = 0;
			double y = 0;
			lineStream >> y;
			speed.setY(y);

			SceneObject* lift = new Lift(this, pos, getTexture(LIFT), speed);
			objectQueue.push_back(lift);
		}*/
		// Coin
		else if (tipo == 'C')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			//Pickable* coin = new Coin(this, pos, getTexture(COIN));
			objectQueue.push_back(new Coin(this, pos, getTexture(COIN)));
		}
		// Piranha
		else if (tipo == 'P')
		{

		}

		getline(mapa, line);

		i++;
	}
}

void Game::loadLevel(const string& file, const string& root)
{
	// TILEMAP
	std::ifstream tiles(root + file + ".csv");
	//std::ifstream tiles("../assets/maps/world1.csv");
	cout << root + file + ".csv" << endl;
	// control de errores
	if (!tiles.is_open())
	{
		std::cout << "Error cargando el tilemap";
	}

	Point2D<double> pos = Point2D<double>(0, 0);
	//tilemap = new Tilemap(this, tiles, pos, getTexture(BACKGROUND));
	objectQueue.push_back(new Tilemap(this, tiles, pos, getTexture(BACKGROUND)));
	tiles.close();

	// MAPA
	std::ifstream mapa(root + file + ".txt");
	// control de errores
	if (!mapa.is_open())
	{
		std::cout << "Error cargando el mapa";
	}
	loadMap(mapa);

	mapa.close();

	if (isVictory)
	{
		mapOffset = 0;
		nextObject = 2;
	}
}

// Loop del juego
void Game::run()
{
	cout << "Game running" << endl;

	while (!exit)
	{
		// get ticks al inicio del bucle
		startTime = SDL_GetTicks();

		handleEvents();
		update(); // actualiza todos los objetos de juego
		render(); // renderiza todos los objetos de juego

		// Tiempo que se ha tardado en ejecutar lo anterior
		int elapsed = SDL_GetTicks() - startTime;

		// Duerme el resto de la duracion del frame
		if (elapsed < FRAME_RATE) SDL_Delay(FRAME_RATE - elapsed);
	}

	// Al salir, se borra todo
	deleteEntities();
}

// Update
void Game::update()
{
	addVisibleEntities();

	for (auto obj : gameList) {
		obj->update();
	}

	// si muere el player acaba el juego
	//if (!player->getAlive()) EndGame();

}

// Render
void Game::render()
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	// Fondo azul
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	for (auto obj : gameList) {
		obj->render();
	}

	// presenta la escena en pantalla
	SDL_RenderPresent(renderer);
}

// Eventos
void Game::handleEvents()
{
	SDL_Event event; 

	while (SDL_PollEvent(&event) && !exit) {

		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) EndGame();

		else {
			player->handleEvent(event);
		}
	}
}

Collision Game::checkCollisions(const SDL_Rect& rect, Collision::Target target) {
	
	Collision c;

	for (auto obj : gameList)
	{
		c = obj->hit(rect, target);

		if (c.result != Collision::NONE)
		{
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

void Game::addObject(SceneObject* o)
{
	if (nextObject == 1)
	{
		gameList.push_front(o);
	}
	else if (nextObject == 2)
	{
		player = o;
		gameList.push_back(o);
	}
	else
	{
		gameList.push_back(o);
	}
}

void Game::addVisibleEntities()
{
	// Borde derecho del mapa (+ una casilla)
	const int rightThreshold = mapOffset + WIN_WIDTH + TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getPosition().getX() < rightThreshold)
	{
		//addObject(objectQueue[nextObject++]->clone());
	}
}

void Game::deleteEntities()
{
	// Si se ha perdido
	if (exit)
	{
		for (SceneObject* obj : gameList)
		{
			delete obj;
		}
		for (auto obj : objectQueue)
		{
			delete obj;
		}
	}
}

void Game::reloadWorld(const string& file, const string& root)
{
	// todos los objetos del juego (salvo el jugador y el tilemap) se destruyen
	for (auto obj : gameList)
	{
		if (obj != player && obj != tilemap)
		{

			delete obj;
		}
	}

	// Reseteamos el offset
	mapOffset = 0;
	// Ya se ha cargado mario y mapa
	nextObject = 2;

	// Tilemap (csv)
	std::ifstream tiles(root + file + ".csv");
	//std::ifstream tiles("../assets/maps/world1.csv");
	cout << root + file + ".csv" << endl;
	// control de errores
	if (!tiles.is_open())
	{
		std::cout << "Error cargando el tilemap";
	}

	Point2D<double> pos = Point2D<double>(0, 0);
	//tilemap = new Tilemap(this, tiles, pos, getTexture(BACKGROUND));
	gameList.push_front(new Tilemap(this, tiles, pos, getTexture(BACKGROUND)));
	tiles.close();

	// Objetos del mapa (txt entidades)
	std::ifstream mapa(root + file + ".txt");
	// control de errores
	if (!mapa.is_open())
	{
		std::cout << "Error cargando el mapa";
	}
	loadMap(mapa);

	mapa.close();
}


void Game::createSeta(Point2D<double> p)
{
	p.setY(p.getY() - TILE_SIDE);

	//SceneObject* seta = new Mushroom(this, p, getTexture(MUSHROOM));
	gameList.push_back(new Mushroom(this, p, getTexture(MUSHROOM)));
}

double Game::getMapOffset() { return mapOffset; }
void Game::setMapOffset(double par_) { mapOffset = par_; }
