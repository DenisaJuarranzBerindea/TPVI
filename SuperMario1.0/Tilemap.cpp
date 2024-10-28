#include "Tilemap.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Game.h"

using namespace std;

void Tilemap::renderMapa() {

	static constexpr int TILE_MAP = 32;
	static constexpr int TILE_SIDE = 16;
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


	//ZONA DE PRUEBAS (hace lo mismo que el bucle pero solo tres casos, cuando funcione esto aplicar al bucle)
	// DUDA PRINCIPAL: cómo utilizar renderFrame y si hay que utilizar una textura
	// nueva background (líneas 34-36), o background_spritesheet (inicializada en el constructor)
//----------------------------------------------------------------------------------------------------
	SDL_Surface* background_surface = SDL_CreateRGBSurface(0, 16, 210, 0, 138, 132, 255, 255);
	background_texture = SDL_CreateTextureFromSurface(g->getRenderer(), background_surface);
	background = new Texture(g->getRenderer(), background_texture, 16, 210);

	//(6, 9) -> 40, renderizando: 4, 4 (o sea, indice / 9, indice % 9)
	rect.x = 9;
	rect.y = 6;
	int indice = 40;
	background_spritesheet->renderFrame(rect, indice / 9, indice % 9);
	//background->renderFrame(rect, indice / 9, indice % 9);

	//(6, 10) -> 41, renderizando: 4, 5
	rect.x = 10 * TILE_SIDE;
	rect.y = 6 * TILE_SIDE;
	indice = 41;
	background_spritesheet->renderFrame(rect, indice / 9, indice % 9);
	//background->renderFrame(rect, indice / 9, indice % 9);

	//(6, 11) -> 42, renderizando: 4, 6
	rect.x = 11 * TILE_SIDE;
	rect.y = 6 * TILE_SIDE;
	indice = 42;
	background_spritesheet->renderFrame(rect, indice / 9, indice % 9);
	//background->renderFrame(rect, indice / 9, indice % 9);
//----------------------------------------------------------------------------------------------------

	//for (int i = 0; i < WIN_WIDTH+1; ++i) { //mas anchura de la necesaria, a proposito
	//	for (int j = 0; j < WIN_HEIGHT; ++j) {
	//		cout << "(" << x0 + i << ", " << j << ") -> ";
	//		int indice = mapaV[j][x0+i]; //esto es el elemento del csv
	//		cout << indice;
	//		int fx = indice % 9; //esto es la fila del spritesheet
	//		int fy = indice / 9; //esto es la columna del spritesheet
	//
	//		rect.x = -d0 + i * TILE_SIDE; //la posicion del rect a dibujar, indice por pixeles del tile
	//		rect.y = j * TILE_SIDE;
	//
	//		if (indice != -1) {
	//			background->renderFrame(rect, fy, fx);
	//			cout << ", renderizando: " << fy << ", " << fx << endl;
	//		}
	//		else {
	//			fx = 0; fy = 0;
	//			background->renderFrame(rect, fy, fx);
	//			cout << ", renderizando: " << fy << ", " << fx << endl;
	//		}
	//	}
	//}

	cout << "Renderizado" << endl;
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



