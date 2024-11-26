#ifndef PLAYER_H
#define PLAYER_H

#include "SceneObject.h"

#include "checkML.h"
#include "Texture.h"
#include <istream>
#include <fstream>
#include <string>

// para evitar inclusiones cruzadas
class Game;

using uint = unsigned int;
using namespace std;

class Player : public SceneObject
{

private:
	Texture* texture;	// puntero a su textura

	int maxLifes = 3;
	int lifes;					// numero de vidas restantes, 3 al inicio

	bool isAlive = true;

	Vector2D<int> direction;	// direccion de movimiento
	double fallSpeed = 0.01;

public:

	char marioState; // m(mario), s(supermario)

	// ANIMACION
	int marioFrame = 0;

	// INPUT
	bool keyA = false; //Izqd
	bool keyD = false; //Dcha
	bool keyS = false; //Abajo
	bool keySpace = false; //Salto
	bool keyE = false; //Salir
		

	// Colisiones player
	SDL_Rect colRect = SDL_Rect();
	Collision collisionMario;

	bool isFalling = true;
	bool canJump = false;
	bool grounded = false;		// si esta en el suelo, solo puede saltar cuando lo este
	int maxHeight;

	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;
	bool flipSprite = false;

public:
	//Constructora
	Player(Game* game_, std::istream& in, double speedX_, double speedY_); // La textura tambien?

	//Destructora
	//~Player() override;

	// Render
	void render() const override;
	// Actualizacion
	void update() override;
	// Hit (no necesario?) No implementado
	Collision hit(SDL_Rect, bool) override;
	// Eventos, sobre todo input   
	void handleEvents(const SDL_Event& event);
	// Efectos de colisiones
	void damage();

	// Animaciones
	void updateAnims();
	// Para bloquear pantalla cuando avanza
	void updateOffset();


	// Getters
	double getX() const { return position.getX(); }
	double getY() const { return position.getY(); }
	int getDx() const { return direction.getX(); }
	int getDy() const { return direction.getY(); }
	char getState() { return marioState; }

	// Setters
	void setX(double newX) { position.setX(newX); }
	void setY(double newY) { position.setY(newY); }
	void setDx(int newDx) { direction.setX(newDx); }
	void setDy(int newDy) { direction.setY(newDy); }
	void setState(char newState) { marioState = newState; }

private:
	// Movimiento
	void moveMario(bool, bool);

	//Ca das
	bool checkFall();
};

#endif	