#ifndef TILEMAP_H
#define TILEMAP_H

#include "checkML.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Texture.h"
#include "Game.h"
#include "SceneObject.h"

using namespace std;
class Game;
class Tilemap : public SceneObject
{
private:
	vector<vector<int>> indices;
	int x, y;

public:
	//Tilemap();
	Tilemap(Game* g, std::istream& in, Point2D<double> p, Texture* t);
	~Tilemap();

	void render() override;
	void update() override;
	void load(std::istream& file);

	// detecta colisiones
	virtual Collision hit(SDL_Rect rect, Collision::Target t);

	void manageCollisions(Collision c) override;
	//SceneObject* clone() const override;

	void updateAnim() override {};
};

#endif	