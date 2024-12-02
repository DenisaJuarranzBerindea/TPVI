#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Texture.h"
#include "Collision.h"
#include "SceneObject.h"

using namespace std;
class Game;

class Tilemap : public SceneObject
{
private:
	vector<vector<int>> indices;
	int x, y;

public:
	//TileMap();
	TileMap(Game* g, std::istream& in, Point2D<double> p, Texture* t);
	~TileMap();

	void render() override;
	void update() override;
	void load(std::istream& file);

	// detecta colisiones
	Collision hit(const SDL_Rect& rect, Collision::Target t);

	void manageCollisions(Collision c) override;
	SceneObject* clone() const override;

	void updateAnim() override {};
};