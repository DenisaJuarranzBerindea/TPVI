#include "Tilemap.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Game.h"

using namespace std;

void Tilemap::renderMapa() {

	int x0 = g->getMapOffset() / g->TILE_MAP;
	int d0 = (int)g->getMapOffset() % g->TILE_MAP;
	//preguntar por esta linea porque no entiendo que es el TILE_MAP ni la division del offset,
	//esta relacionado con las expresiones estaticas en game.h

	rect.w = g->TILE_SIDE;
	rect.h = g->TILE_SIDE;

	//color de fondo
	SDL_SetRenderDrawColor(g->getRenderer(), 138, 132, 255, 255);

	for (int i = 0; i < g->TILE_WINDOW_WIDTH + 1; ++i) { //mas anchura de la necesaria, a proposito
		for (int j = 0; j < g->TILE_WINDOW_HEIGHT; ++j) {
			int indice = mapaV[j][x0+i]; //esto es el elemento del csv
			int fx = indice % 9; //esto es la fila del spritesheet
			int fy = indice / 9; //esto es la columna del spritesheet

			//cout << "(" << x0 + i << ", " << j << ") -> ";
			//cout << indice;
			//cout << ", renderizando: " << fy << ", " << fx << endl;

			rect.x = -d0 + i * g->TILE_SIDE; //la posicion del rect a dibujar, indice por pixeles del tile
			rect.y = j * g->TILE_SIDE;
	
			if (indice == -1) fx = fy = 0;
			background_spritesheet->renderFrame(rect, fy, fx);
		}
	}
}

//sobra porque ya no mueves el mapa
void Tilemap::handleEvents(const SDL_Event& event)
{
	// Recibe tecla
	SDL_Scancode key = event.key.keysym.scancode;
	bool keyA = false;
	bool keyD = false;

	int limite = 210 * 32 - 18 * 32; //nTiles * tamTile - WIN_WIDTH * tamTile
	int velScroll = 50;

	//// pulsar
	//if (event.type == SDL_KEYDOWN)
	//{
	//	// IZQD
	//	if (key == SDL_SCANCODE_A) {
	//		g->setMapOffset(g->getMapOffset() - velScroll);
	//		if (g->getMapOffset() <= 0) g->setMapOffset(0);
	//	}

	//	// DCHA
	//	else if (key == SDL_SCANCODE_D) {
	//		g->setMapOffset(g->getMapOffset() + velScroll);
	//		if (g->getMapOffset() >= limite) g->setMapOffset(limite);
	//	}

	//}

	//// despulsar
	//else if (event.type == SDL_KEYUP)
	//{
	//	// IZQ
	//	if (key == SDL_SCANCODE_A) keyA = false;

	//	// DER
	//	else if (key == SDL_SCANCODE_D) keyD = false;
	//}
}

Tilemap::Tilemap(const string& fichero, Game* game) {
	g = game;

	ifstream input(fichero);
	if (!input) return;

	string line;
	while (getline(input, line)) {
		vector<int> aux;
		stringstream ss(line);
		int c;
		while (ss >> c) {
			aux.push_back(c);
			if (ss.peek() == ',') ss.ignore();
		}
		mapaV.push_back(aux);
	}

	// Debug, imprime cada elemento del mapa y su fila y columna
	//for (size_t row = 0; row < mapaV.size(); ++row) {
	//	for (size_t col = 0; col < mapaV[row].size(); ++col) {
	//		cout << "(" << row << ", " << col << ") -> " << mapaV[row][col] << endl;
	//	}
	//	cout << endl;
	//}

	background_spritesheet = g->getTexture(Game::TextureName::BACKGROUND);
}

Collision Tilemap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision c;
	c.collides = true;
	c.damages = false;

	Texture* texture;

	constexpr int OBSTACLE_THRESHOLD = 4; // constante

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / Game::TILE_SIDE;
	int col0 = rect.x / Game::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / Game::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / Game::TILE_SIDE;

	for (int row = row0; row <= row1; ++row) {
		for (int col = col0; col <= col1; ++col) {
			int indice = mapaV[row][col];

			if (indice != -1 && indice % background_spritesheet->getNumColumns() < OBSTACLE_THRESHOLD)
				return c;
		}
	}


	return c;
}