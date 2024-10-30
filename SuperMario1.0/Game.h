#ifndef GAME_H
#define GAME_H

// Memory leaks
#include "checkML.h"

// Biblioteca estándar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>
#include "SDL_image.h"

// Nuestras clases
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <random>

#include <time.h>
#include "Texture.h"
#include "Tilemap.h"
//#include "./HolaSDL/Vector2D.h"
#include "./HolaSDL/Player.h"

#include "./HolaSDL/Block.h"
/*#include "./HolaSDL/Goomba.h"
#include "./HolaSDL/Mushroom.h"
#include "./HolaSDL/Koopa.h"*/

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;

	// Constante globales
	const int FRAME_RATE = 50;
	const int TIME_BY_FRAME = 1 / FRAME_RATE;
	const double MARIO_SPEED = 0.01;

	// Interruptor para terminar el juego
	bool exit;
	// Desplazamiento del mapa
	double mapOffset = 0; //int choca y bloquea en el borde??

	// declaración de los elementos de juego
	Tilemap* mapa;
	Player* player;
	vector<Block*> blocks;

	int startTime, frameTime;	// manejo de tiempo en run


public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND, // = 0
		MARIO, // = 1
		NUM_TEXTURES  // Truco C++: número de texturas definidas
	};

	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;


	//En tiles
	static constexpr uint TILE_MAP = 32;
	static constexpr uint TILE_SIDE = 32;
	static constexpr uint TILE_WINDOW_WIDTH = 18; // ancho ventana en tiles
	static constexpr uint TILE_WINDOW_HEIGHT = 16; // alto ventana en tiles
	static constexpr uint WIN_WIDTH = TILE_SIDE * TILE_WINDOW_WIDTH;  // ancho ventana en px
	static constexpr uint WIN_HEIGHT = TILE_SIDE * TILE_WINDOW_HEIGHT; // alto ventana en px


	//Constructora
	Game();

	//Destructora
	~Game();

	// Juego
	// inicializa elementos del juego
	void init();
	// bucle principal
	void run();
	// renderiza la pantalla
	void render() const;
	// actualiza el estado de juego
	void update();
	// input del jugador y otros eventos
	void handleEvents();
	// colisiones
	void collides();

	// getters
	int getMapOffset();
	Texture* getTexture(TextureName name) const;
	SDL_Renderer* getRenderer() { return renderer; }
	bool GetExit() const { return exit; }

	// setters
	void setMapOffset(int);
	void EndGame();
	void setExit(bool aux) { exit = aux; }

private:

	// se cargan las texturas y se guardan en el array
	void loadTextures();
	// lee mapa
	void loadMap();
	// fondo
	//void renderBackground(); // utilizar?
	// muestra en consola las vidas del jugador
	void playerLife();

};

#endif