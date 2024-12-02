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
	Texture* texture;	

	// Gestión de vidas
	int maxLifes = 3;
	int lifes;
	bool immune;
	bool isAlive = true;
	// Invencibilidad
	int invCounter = 0;
	int maxInvCounter = 5;
	bool invencible = false;

	// Gestión de movimiento
	Vector2D<int> direction;	
	double fallSpeed = 0.01;
	bool grounded, jumping;
	bool isFalling = true;
	int maxHeight;

	// Animación
	int walkFrame;
	bool flipSprite = false;
	int marioFrame = 0;

	double deadH = 15 * 32; //Altura desde la que es muerto (15 * TILE_SIDE, pero no me deja meter el game)
	double bgSpeed = 1.0;
	double velX;

	char marioState; // m(mario), s(supermario)

public:

	// INPUT
	bool keyA = false; //Izqd
	bool keyD = false; //Dcha
	bool keyS = false; //Abajo
	bool keySpace = false; //Salto
	bool keyE = false; //Salir
	bool keyDcha = false; //Offset mapa
		
	// Colisiones player
	SDL_Rect colRect = SDL_Rect();
	Collision collisionMario;

	// Animacion
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;
	bool flipSprite = false;

	// Fin nivel
	int flagPosition = 6306;
	
	// Estados
	int marioState;
	enum State {
		MARIO, SUPERMARIO
	};

	Texture* textureM = nullptr;
	Texture* textureS = nullptr;

	//Constructora
	Player(Game* game, Point2D<double> pos, Texture* t, int l, Vector2D<double> s);
	
	// Render
	void render() override;
	// Actualizacion parte logica
	void update() override;
	// Actualizacion parte grafica
	void updateTexture();
	// Hit
	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	// Clon
	SceneObject* clone() const override;
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

	// Movimiento
	void moveMario(bool, bool);

	// Fin nivel
	void finishLevel();

	// Getters
	double getX() const { return position.getX(); }
	double getY() const { return position.getY(); }
	int getDx() const { return direction.getX(); }
	int getDy() const { return direction.getY(); }
	int getState() { return marioState; }
	int getLifes() { return lifes; }

	// Setters
	void setX(double newX) { position.setX(newX); }
	void setY(double newY) { position.setY(newY); }
	void setDx(int newDx) { direction.setX(newDx); }
	void setDy(int newDy) { direction.setY(newDy); }
	void setState(int newState) { marioState = newState; }
	void setLifes(int n) { lifes = n; }
	void setGrounded(bool g) { grounded = g;}

};

#endif	