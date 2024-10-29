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
#include <array>
#include <vector>
#include <fstream>
#include <random>
#include <string>
#include <time.h>
#include "Texture.h"
#include "Tilemap.h"
#include "Vector2D.h"

#include "Player.h"
/*#include "Block.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Koopa.h"*/

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

	//En tiles
	static constexpr int TILE_SIDE = 32; 
	static constexpr int TILE_WINDOW_WIDTH = 18;
	static constexpr int TILE_WINDOW_HEIGHT = 16;

	// Interruptor para terminar el juego
	bool exit;
	// Desplazamiento del mapa
	int mapOffset = 0;

	// declaración de los elementos de juego
	Tilemap* mapa;
	Player* player;

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

	static constexpr uint WIN_WIDTH = TILE_SIDE * TILE_WINDOW_WIDTH;  // ancho ventana
	static constexpr uint WIN_HEIGHT = TILE_SIDE * TILE_WINDOW_HEIGHT; // alto ventana

	
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
	void EndGame();
	void setExit(bool aux) { exit = aux; }

private:

	// se cargan las texturas y se guardan en el array
	void loadTextures();
	// lee mapa
	void loadMap();
	// fondo
	void renderBackground(); // utilizar?
	// muestra en consola las vidas del jugador
	void playerLife();

};

inline Texture*
Game::getTexture(TextureName name) const { return textures[name]; }

#endif