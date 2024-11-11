#ifndef Block_h
#define Block_h

#include "checkML.h"
#include <SDL.h>
//#include "Vector2D.h"
#include "../Texture.h"
#include "./Collision.h"
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

public:

	// Colisiones bloque
	SDL_Rect colRect = SDL_Rect();

	Block(Game* g, std::istream& in);

	void render() const;

	void update();

	// Los bloques son obstaculos para todos los personajes cuando lo golpeen desde arriba o desde un lateral
	// Si Mario lo golpa desde abajo:
	//	-> si el bloque es de ladrillo y el player es SuperMario: bloque se rompe
	//	-> si el bloque es sorpresa/oculto y accion es potenciador: saca mushroom sobre el bloque y lo hace vacio
	//	-> nada en el resto de casos
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	//Getters y setters
	char getLTipo() const { return tipoL; }
	int getTipo() const { return tipo; }
	char getLAccion() const { return accionL; }
	int getAccion() const { return accion; }

	// Setters

};

#endif