#include "Tilemap.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Game.h"

using namespace std;

void Tilemap::renderMapa() {

	static constexpr int TILE_MAP = 32;
	static constexpr int TILE_SIDE = 32;
	static constexpr int WIN_WIDTH = 18;
	static constexpr int WIN_HEIGHT = 16;

	int x0 = g->getMapOffset() / TILE_MAP;
	int d0 = g->getMapOffset() % TILE_MAP;
	//preguntar por esta linea porque no entiendo que es el TILE_MAP ni la division del offset,
	//esta relacionado con las expresiones estaticas en game.h

	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	//color de fondo
	SDL_SetRenderDrawColor(g->getRenderer(), 138, 132, 255, 255);

	for (int i = 0; WIN_WIDTH + 1; ++i) { //mas anchura de la necesaria, a proposito
		for (int j = 0; j < WIN_HEIGHT; ++j) {
			int indice = mapaV[j][x0+i]; //esto es el elemento del csv
			int fx = indice % 9; //esto es la fila del spritesheet
			int fy = indice / 9; //esto es la columna del spritesheet
	
			rect.x = -d0 + i * TILE_SIDE; //la posicion del rect a dibujar, indice por pixeles del tile
			rect.y = j * TILE_SIDE;
	
			background_spritesheet->renderFrame(rect, fy, fx); //no hace falta if porque para indice -1, fy y fx son 0

			//cout << "(" << x0 + i << ", " << j << ") -> ";
			//cout << indice;
			//cout << ", renderizando: " << fy << ", " << fx << endl;
		}
	}
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



