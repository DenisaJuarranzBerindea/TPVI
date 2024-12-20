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

#include "Texture.h"
#include "Tilemap.h"
#include "Mushroom.h"
#include "Koopa.h"

#include "gameList.h"
struct Collision;

//Objetos de juego
class Player;
class Block;
class Goomba;

class SceneObject;

using uint = unsigned int;


class Game
{
public:
	GameList<SceneObject> gameList;
protected:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;

	//Colisiones
	Collision* colisiones;

	// Constante globales
	const int FRAME_RATE = 50;
	const int TIME_BY_FRAME = 1 / FRAME_RATE;

	static constexpr double GOOMBA_SPEED = 0.01;
	static constexpr double KOOPA_SPEED = 0.01;
	static constexpr double MUSHROOM_SPEED = 0.01;

	// Interruptor para terminar el juego
	bool exit;
	// Desplazamiento del mapa
	double mapOffset = 0;

	// declaración de los elementos de juego
	Tilemap* mapa = nullptr;
	Player* player = nullptr;

	//vector<Goomba*> goombas;
	//vector<Block*> blocks;
	//vector<Koopa*> koopas;

	int startTime, frameTime;	// manejo de tiempo en run


public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND, // = 0
		MARIO, // = 1
		SUPERMARIO, // = 2
		GOOMBA, // = 3
		KOOPA, // = 4
		MUSHROOM, // = 5
		BLOCK, // = 6
		NUM_TEXTURES  // Truco C++: número de texturas definidas
	};

	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures = {};

	// Interruptor de mapa
	int map = 1;
	bool cambioMapa = false;

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
	// gestionar colisiones
	Collision checkCollision(const SDL_Rect& rect, Collision::Target);

	// getters
	double getMapOffset();
	Texture* getTexture(TextureName name) const;
	SDL_Renderer* getRenderer() { return renderer; }
	bool GetExit() const { return exit; }
	int getMarioState();

	// setters
	void setMapOffset(double);
	void EndGame();
	void setExit(bool aux) { exit = aux; }

	void cargarMapa(int map_);

private:

	// se cargan las texturas y se guardan en el array
	void loadTextures();
	// lee mapa
	void loadMap();
	// fondo
	// muestra en consola las vidas del jugador
	void playerLife();

};

#endif