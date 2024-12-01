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
//class Collision;
#include "Vector2D.h"
#include "Collision.h"
class TileMap;

//Objetos de juego
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Koopa.h"

using uint = unsigned int;

class Game
{
public:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;

	//Colisiones
	Collision* colisiones;

	// Constante globales
	const int FRAME_RATE = 50;
	const int TIME_BY_FRAME = 1 / FRAME_RATE;
	const double MARIO_SPEED = 0.01;
	const double GOOMBA_SPEED = 0.01;
	const double KOOPA_SPEED = 0.01;
	const double MUSHROOM_SPEED = 0.01;
	const double SPEED_LIMIT = 10;
	const double MOVE_PERIOD = 5;

	//En tiles
	static constexpr uint TILE_MAP = 32;
	static constexpr uint TILE_SIDE = 32;
	static constexpr uint TILE_WINDOW_WIDTH = 18; // ancho ventana en tiles
	static constexpr uint TILE_WINDOW_HEIGHT = 16; // alto ventana en tiles
	static constexpr uint WIN_WIDTH = TILE_SIDE * TILE_WINDOW_WIDTH;  // ancho ventana en px
	static constexpr uint WIN_HEIGHT = TILE_SIDE * TILE_WINDOW_HEIGHT; // alto ventana en px
	static constexpr uint OBSTACLE_THRESHOLD = 4; // constante
	static constexpr double MAP_MAX_OFFSET = 6100;
	static constexpr uint GRAVITY = 3;
	const Collision NO_COLLISION = { Collision::EMPTY, Collision::NONE, 0, 0 };

	// declaración de los elementos de juego
	Tilemap* mapa = nullptr;
	Player* player = nullptr;
	Goomba* goomba = nullptr;
	Koopa* koopa = nullptr;
	Block* block = nullptr;

	vector<Goomba*> goombas;
	vector<Block*> blocks;
	vector<Koopa*> koopas;

	int startTime, frameTime;	// manejo de tiempo en run


private:
	// Interruptor para terminar el juego
	bool exit;
	// Desplazamiento del mapa
	double mapOffset = 0;

	// declaración de los elementos de juego
	SceneObject* player;
	SceneObject* tilemap;

	GameList<SceneObject> gameList;

	vector<SceneObject*> objectQueue;
	int nextObject;

	// Color de fondo
	int r, g, b;

	// Puntuacion del jugador
	int points;

	// Cambio nivel
	int currentWorld;
	int maxWorlds;

	// Victoria nivel
	bool isVictory;

	int marioState;

	// Caída por agujeros
	bool fallen = false;

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
		COIN, // = 7
		LIFT, // = 8
		NUM_TEXTURES  // Truco C++: número de texturas definidas
	};

	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures = {};

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
	void render();
	// actualiza el estado de juego
	void update();
	// input del jugador y otros eventos
	void handleEvents();
	// gestionar colisiones
	Collision checkCollisions(const SDL_Rect& rect, Collision::Target target);

	// Objetos de escena
	void deleteEntities();
	void addVisibleEntities();
	void addObject(SceneObject* o);
	void createSeta(Point2D<double> p);

	// Cambio niveles 
	void reloadWorld(const string& file, const string& root);
	void loadLevel(const string& file, const string& root);

	// getters
	double getMapOffset() { return mapOffset; };
	Texture* getTexture(TextureName name) const { return textures[name]; };
	SDL_Renderer* getRenderer() { return renderer; }
	bool GetExit() { return exit; }
	int getMarioState() const { return marioState; }
	int getCurrentLevel() const { return currentWorld; }
	int getMaxWorlds() const { return maxWorlds; }
	bool getFallen() const { return fallen; }

	// setters
	void setMapOffset(double);
	void EndGame();
	void setExit(bool aux) { exit = aux; }
	void setCurrentLevel(int c) { currentWorld = c; }
	void setFallen(bool f) { fallen = f; }
	void setMarioState(int s) { marioState = s; }
	void setMapOffset(int newOffset) { mapOffset = newOffset; }
	void setVictory(bool v) { isVictory = v; }

	void addMapOffset(int newOffset) { mapOffset += newOffset; }
	void addPoints(int p)
	{
		points += p;
	}

private:

	// se cargan las texturas y se guardan en el array
	void loadTextures();
	// lee mapa
	void loadMap(std::ifstream& mapa);
	// fondo
	// muestra en consola las vidas del jugador
	void playerLife();

};

#endif