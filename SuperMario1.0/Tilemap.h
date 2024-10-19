#pragma once

#include <vector>
#include <fstream>

using namespace std;

class Tilemap
{

public:
	vector<vector<int> > mapaV;
	void leeMapa(const string& fichero);
	void renderMapa();

private: 

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
	}

	// Constructora
};


