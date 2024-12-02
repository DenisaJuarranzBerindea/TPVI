#pragma once

#include "GameObject.h"
#include "Collision.h"

#include "Vector2D.h"

class Game;

class SceneObject : public GameObject 
{
protected:
	// Movimiento
	Point2D<double> position;	// Coordenadas (x, y)
	Vector2D<double> speed;		// Velocidad (vx, vy)

	// Representación gráfica
	int width, height;        // Tamaño del objeto
	Texture* texture;
	double scale;
	SDL_Rect colRect;	//Colisiones

	// Animación
	int animationFrame = 0;   // Contador para el ciclo de caminar
	bool flipSprite = true;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int walkFrame = 0;
	int frameTimer = 0;
	int frame = 0;
	bool isAlive = true;
	//GameList<SceneObject>::anchor _anchor; // Ancla a la lista de objetos del juego

public:

	// Constructora
	//SceneObject(Game* game, Point2D<double> pos, Texture* texture, Vector2D<double> speed);

	//SceneObject(Game* game, Point2D<double> pos, Texture* texture);

	// Destructora Virtual
	virtual ~SceneObject() {}

	// Constructora copia
	SceneObject(const SceneObject& s);
	// Asignación por copia
	SceneObject& operator=(const SceneObject& s); 


	// Colisiones
	virtual Collision hit(SDL_Rect, Collision::Target) = 0;
	virtual void manageCollisions(Collision collision) = 0;

	// Animaciones
	virtual void updateAnim() = 0;

	// Getters virtuales
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;

	//void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
		//_anchor = std::move(anchor);
	//}
protected:
	Collision tryToMove(const Vector2D<double>& speed, Collision::Target target);

	// Setters
	void setScale(double n) { scale = n; }
	void setAlive(bool a) { isAlive = a; }

	// Getters
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
};
