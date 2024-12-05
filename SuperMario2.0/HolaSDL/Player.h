#ifndef PLAYER_H
#define PLAYER_H

#include "SceneObject.h"

//// para evitar inclusiones cruzadas
//class Game;
//
//using uint = unsigned int;
//using namespace std;

class Player : public SceneObject
{

private:
	Texture* texture;	

	// Gestión de vidas
	//int maxLifes = 3;
	int lifes;
	bool immune;
	//bool isAlive = true;

	// Invencibilidad
	int invCounter = 0;
	int maxInvCounter = 5;
	bool invencible = false;

	// Gestión de movimiento
	//Vector2D<int> direction;	
	//double fallSpeed = 0.01;
	bool grounded, jumping;
	//bool isFalling = true;
	//int maxHeight;

	// Animación
	int walkFrame;
	bool flipSprite = false;
	int marioFrame = 0;

	double deadH = 14 * 32;
	double bgSpeed = 1.0;
	int velX = 1;

	char marioState; // m(mario), s(supermario)

	// INPUT
	bool keyA = false; //Izqd
	bool keyD = false; //Dcha
	bool keyS = false; //Abajo
	bool keySpace = false; //Salto
	bool keyE = false; //Salir
	bool keyDcha = false; //Offset mapa

public:
		
	Player(Game* game, Vector2D<double> pos, Texture* t, int l, Vector2D<double> s);

	void render() override;
	void update() override;
	void updateAnim() override;

	void updateTexture();

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	virtual void manageCollisions(Collision c) override;
	void manageInvencible();
	void manageDamage();

	//SceneObject* clone() const override;

	void jump();


	void handleEvent(const SDL_Event& event) override;

	int marioState;
	enum State {
		MARIO, SUPERMARIO
	};

	void finishLevel();

	Texture* textureM = nullptr;
	Texture* textureS = nullptr;

	int flagPosition = 6306;

	void updateOffset();

	int getLifes() { return lifes; }
	int getState() { return marioState;	}

	void setLifes(int n) { lifes = n; }
	void setState(int s) { marioState = s; }
	void setGrounded(bool g) { grounded = g; }

	void checkFall();

};

#endif	