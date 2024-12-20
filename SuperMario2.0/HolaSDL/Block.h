#ifndef Block_h
#define Block_h

#include "SceneObject.h"

#include "checkML.h"
#include <SDL.h>
//#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

class Game;

using uint = unsigned int;
using namespace std;

class Block : public SceneObject
{

private:
	int blockFrame;
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

	//Point2D<double> position;	// posicion actual en Point2D
	double x, y;

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

public:

	// Colisiones bloque
	SDL_Rect colRect = SDL_Rect();

	Block(Game* g, std::istream& in);

	void render() const override;
	void update() override;
	Collision hit(SDL_Rect, Collision::Target) override;
	~Block() override;

	//Getters y setters
	int getTipo() const { return tipo; }
	bool getAlive() const { return alive; }

	// Setters
	void setTipo(int t) { tipo = t; }
	void setDead() { alive = false; }

	// Auxiliar para que aparezca la seta
	void setaSpawn();
};

#endif