#include "Tilemap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Game.h"

using namespace std;

void Tilemap::renderMapa() {
	constexpr int TILE_MAP = 32;
	constexpr int WINDOW_WIDTH = 18;
	constexpr int WINDOW_HEIGHT = 16;
	constexpr int TILE_SIDE = 16;

	int x0 = g->getMapOffset() / TILE_MAP;

	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	for (int i = 0; i < WINDOW_WIDTH; ++i) {
		for (int j = 0; j < WINDOW_HEIGHT; ++j) {
			int indice = mapaV[x0 + i][j];
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = i * TILE_SIDE;
			rect.y = j * TILE_SIDE;

			if (indice != -1) {
				background->renderFrame(rect, fy, fx);
			}
			else {
				SDL_SetRenderDrawColor(g->getRenderer(), 138, 132, 255, 255);
				fx = 0; fy = 0; //fondo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				background->renderFrame(rect, fy, fx);
			}
		}
	}
}

Tilemap::Tilemap(const string& fichero) {
	ifstream input(fichero);

	if (!input) return;
	while (!cin) {
		char cAux = ',';
		int c = 0;
		vector<int> aux;
		while (cAux == ',') {
			input >> c;
			aux.push_back(c);
			cAux = input.get();
		}
		mapaV.push_back(aux);
	}

	background = g->getTexture(Game::TextureName::BACKGROUND);
}



