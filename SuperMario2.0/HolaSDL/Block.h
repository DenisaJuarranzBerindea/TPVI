#ifndef Block_h
#define Block_h

#include "checkML.h"
#include <SDL.h>
#include "Texture.h"
#include "Collision.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "SceneObject.h"

class Game;

using uint = unsigned int;
using namespace std;

class Block : public SceneObject
{

private:

	char tipoL;
	int tipo;
	enum Tipo // tipo de bloque
		// ? -> sorpresa
		// B -> ladrillo
		// H -> oculto
	{
		LADRILLO, SORPRESA, OCULTO, VACIO
	};

	char accionL;
	int accion;
	enum Accion // accion
		// P -> potenciador
		// C -> moneda
	{
		POTENCIADOR, MONEDA
	};

	bool alive;

	// Colisiones bloque
	SDL_Rect colRect = SDL_Rect();

public:

	Block(Game* g, Point2D<double> p, Texture* t, char tipoL, char accionL);

	void render() override;

	void update() override;

	Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	//Getters y setters
	int getTipo() const { return tipo; }
	bool getAlive() { return alive; }
	Point2D<double> getPos() const { return position; }

	// Setters
	void setTipo(int t) { tipo = t; }
	void setDead() { alive = false; }

	// Auxiliar para que aparezca la seta
	void manageSorpresa();

	virtual void manageCollisions(Collision col) override;

	//SceneObject* clone() const override;

	void updateAnim() override;
};

#endif