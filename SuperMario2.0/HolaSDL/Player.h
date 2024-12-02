#ifndef PLAYER_H
#define PLAYER_H

#include "SceneObject.h"

// para evitar inclusiones cruzadas
class Game;

using uint = unsigned int;
using namespace std;

class Player : public SceneObject
{

	private:
	// Gestión de vidas
	int maxLifes = 3;
	int lifes;
	// Invencibilidad
	int invCounter = 0;
	int maxInvCounter = 5;
	bool invencible = false;

	// Gestión de movimiento
	const double X_SPEED = 0.01;
	const double Y_SPEED = 0.015;
	bool canMove = true;
	bool grounded = false;
	bool jumping = false;
	bool isFalling = true;
	int maxHeight;

	double deadH = 15 * Game::TILE_SIDE; //Altura desde la que es muerto (15 * TILE_SIDE, pero no me deja meter el game)
	double bgSpeed = 1.0;

	char marioState; // m(mario), s(supermario)

public:

	// INPUT
	bool keyA = false; //Izqd
	bool keyD = false; //Dcha
	bool keyS = false; //Abajo
	bool keySpace = false; //Salto
	bool keyE = false; //Salir
		
	// Colisiones player
	SDL_Rect colRect;
	Collision collisionMario;

	// Fin nivel
	int flagPosition = 6306;
	
	// Estados
	enum State {
		MARIO, SUPERMARIO
	};
	int marioState = State::MARIO;

	Texture* textureM = nullptr;
	Texture* textureS = nullptr;

	//Constructora
	Player(Game* game_, std::istream& in);

	// Render
	void render() const override;
	// Actualizacion parte logica
	void update() override;
	// Actualizacion parte grafica
	void updateTexture();
	// Hit
	Collision hit(SDL_Rect, Collision::Target) override;
	// Eventos, sobre todo input   
	void handleEvent(const SDL_Event& event) override;
	// Efectos de colisiones
	virtual void manageCollisions(Collision c) override;
	void manageInvencible();
	void manageDamage();

	// Animaciones
	void updateAnim() override;

	// Para bloquear pantalla cuando avanza
	void updateOffset();

	// Salto
	void jump();

	//Caídas
	void checkFall();

	// Fin nivel
	void finishLevel();

	// Getters
	double getX() const { return position.getX(); }
	double getY() const { return position.getY(); }
	int getState() { return marioState; }
	int getLifes() { return lifes; }

	// Setters
	void setX(double newX) { position.setX(newX); }
	void setY(double newY) { position.setY(newY); }
	void setState(int newState) { marioState = newState; }
	void setLifes(int n) { lifes = n; }
	void setGrounded(bool g) { grounded = g;}

};

#endif	