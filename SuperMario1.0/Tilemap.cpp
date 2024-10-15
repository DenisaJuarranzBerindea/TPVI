#include "Tilemap.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Tilemap::leeMapa(const string& fichero) {
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
}

void Tilemap::renderMapa() {

}
