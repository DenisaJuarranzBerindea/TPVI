#include "Tilemap.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Tilemap::leeMapa(const string& fichero) {
	ifstream input(fichero);

	if (!input) return;

	while (!input) {
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
}

void Tilemap::renderMapa() {

}


/*

vector<vector<int>> indices;
int mapOffset;
constexpr int TILE_MAP = 32;
constexpr int WINDOW_WIDTH = 18;
constexpr int WINDOW_HEIGHT = 16;
Texture* background;

int x0 = mapOffset / TILE_MAP;

SDL_Rect rect;
rect.w = TILE_SIDE;
rect.h = TILE_SIDE;

for (int i = 0; i < WINDOW_WIDTH; ++i){
	for (int j = 0; j < WINDOW_HEIGHT; ++j){
		int indice = indices[x0 + i][j];
		int fx = indice % 9;
		int fy = indice / 9;
		
		rect.x = i*TILE_SIDE;
		rect.y = j*TILE_SIDE;

		background->renderFrame(rect, fx, fy);
	}
}

//para leer colisiones (a futuro), utilizar STRINGSTREAM //#include <sstream>

*/
