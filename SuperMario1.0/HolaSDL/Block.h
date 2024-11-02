#ifndef Block_h
#define Block_h

#include "checkML.h"
#include <SDL.h>
//#include "Vector2D.h"
#include "../Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

class Game;

using uint = unsigned int;
using namespace std;

class Block
{

private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

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


	int blockFrame;
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

public:
	Block(Game* g, std::istream& in, int _x, int _y);

	void render() const;

	void update();

	void hit(SDL_Rect* rect);
};

#endif