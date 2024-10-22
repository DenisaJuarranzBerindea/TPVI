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
#include <array>
#include <vector>
#include <fstream>
#include <random>
#include <time.h>
#include "Texture.h"
//#include "Vector2D.h"

/*#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Koopa.h"*/

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:

	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;

	// Constante globales
	static constexpr uint WIN_WIDTH = 800;  // ancho ventana
	static constexpr uint WIN_HEIGHT = 600; // alto ventana
	const int FRAME_RATE = 50;
	const int TIME_BY_FRAME = 1 / FRAME_RATE;

	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;

	// Interruptor para terminar el juego
	bool exit;
	// Desplazamiento del mapa
	int mapOffset = 0;

	// declaración de los elementos de juego


	int startTime, frameTime;	// manejo de tiempo en run


public:

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
	uint getWinWidth() { return WIN_HEIGHT; }
	uint getWinHeight() { return WIN_HEIGHT; }
	int getMapOffset() { return mapOffset; }
	Texture* getTexture(TextureName name) const;
	SDL_Renderer* getRenderer() { return renderer; }
	bool GetExit() { return exit; }

	// setters
	void EndGame();
	void setExit(bool aux) { exit = aux; }

private:

	// se cargan las texturas y se guardan en el array
	void loadTextures();
	// lee mapa
	void loadMap();
	// fondo
	void renderBackground();
	// muestra en consola las vidas del jugador
	void playerLife();

};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif