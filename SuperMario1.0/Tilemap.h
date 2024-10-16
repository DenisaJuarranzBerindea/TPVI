#pragma once

#include <vector>
#include <fstream>

using namespace std;

class Tilemap
{
	vector<vector<int> > mapaV;
public:
	void leeMapa(const string& fichero);
	void renderMapa();
};


