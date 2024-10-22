#include <string>

#include "Game.h"

using namespace std;

// Formato de la especificacion de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Numero de frames por fila
	uint numRows;		// Numero de frames por columna
};

// Directorio raiz de los archivos de textura
const string textureRoot = "../assets/imgs/";

// Especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	{"/imgs/background.png", 9, 7},

};

//Game::Game() : randomGenerator(time(nullptr)), exit(false)
//{
//	int winX, winY; // Posición de la ventana
//	winX = winY = SDL_WINDOWPOS_CENTERED;
//
//	// Inicialización del sistema, ventana y renderer
//	SDL_Init(SDL_INIT_EVERYTHING);
//
//	// ERRORES DE SDL
//	try
//	{
//		// crea la ventana
//		window = SDL_CreateWindow("Super Mario", winX, winY, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
//
//		// crea el renderer para la ventana
//		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//
//		if (window == nullptr || renderer == nullptr)
//			throw "Error cargando ventana de juego o renderer"s;
//	}
//	catch (...)
//	{
//		cout << "Error cargando ventana de juego o renderer";
//		EndGame();
//	}
//
//	init();
//}

Game::~Game()
{
	// Elimina los objetos del juego
	//delete player;
	//delete blocks;
	//delete mushroom;
	//delete goomba;
	//delete koopa;

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
//void Game::loadTextures()
//{
//	try {
//	    //bucle para rellenar el array de texturas
//		for (int i = 0; i < NUM_TEXTURES; i++) {
//
//			 crea la textura con el url, width y height
//			Texture* tex = new Texture(renderer,
//				(textureRoot + textureSpec[i].name).c_str(),
//				textureSpec[i].numRows,
//				textureSpec[i].numColumns);
//
//			 la mete en el array
//			textures[i] = tex;
//
//			if (textures[i] == nullptr)
//			{
//				cout << "Textura null";
//			}
//		}
//	}
//	catch (...) {
//		std::cout << "Textura no encontrada";
//		EndGame();
//	}
//}

void Game::loadMap()
{

}

// Loop del juego
void Game::run()
{
	// get ticks al inicio del bucle
	startTime = SDL_GetTicks();

	while (!exit)
	{
		handleEvents();

		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime > TIME_BY_FRAME) {
			update(); // actualiza todos los objetos de juego
			startTime = SDL_GetTicks();
		}
		render(); // renderiza todos los objetos de juego
	}
}

// Update
void Game::update()
{
	// Actualiza los objetos del juego
	//player->update();
	//mushroom->update();
	//koopa->update();
	//goomba->update();
	//blocks->update();
}

// Render
void Game::render() const
{
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	textures[BACKGROUND]->render();
	//player->render();
	//mushroom->render();
	//koopa->render();
	//goomba->render();
	//blocks->render();

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
		//else {
		//	player->handleEvents(event);
		// 	mushroom->handleEvents(event);
		//  koopa->handleEvents(event);
		//  goomba->handleEvents(event);
		//  blocks->handleEvents(event);
		// }
	}
}

// Colisiones
void Game::collides()
{

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

// Getters y Setters
int Game::getMapOffset() { return mapOffset; }