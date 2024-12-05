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
	Vector2D<int> direction;

	// Representación gráfica
	int width, height;        // Tamaño del objeto
	Texture* texture;
	double scale;
	SDL_Rect colRect;	//Colisiones
	bool flipSprite = true;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	// Animación
	int frameTimer = 0;
	int frame = 0;

	// Lógica
	bool isAlive = true;
	Collision c;
	bool canMove;
	GameList<SceneObject>::anchor _anchor; // Ancla a la lista de objetos del juego

public:

	// Constructora
	SceneObject(Game* game, Point2D<double> pos, Texture* texture, Vector2D<double> speed);

	SceneObject(Game* game, Point2D<double> pos, Texture* texture);

	// Destructora Virtual
	virtual ~SceneObject() {}

	// Constructora copia
	SceneObject(const SceneObject& s);
	// Asignación por copia
	SceneObject& operator=(const SceneObject& s); 

	virtual void render() override;

	virtual void update() override {}

	//virtual SceneObject* clone() const = 0;

	// Colisiones
	virtual Collision hit(SDL_Rect, Collision::Target) = 0;
	virtual void manageCollisions(Collision collision) = 0;

	// Animaciones
	virtual void updateAnim() = 0;

	// Getters virtuales
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;

	virtual void handleEvent(const SDL_Event& event);

	Point2D<double> getPosition() { return position; }

	void setListAnchor(GameList<SceneObject>::anchor&& anchor) {
		_anchor = std::move(anchor);
	}
protected:
	Collision tryToMove(const Vector2D<double>& speed, Collision::Target target);

	// Setters
	void setScale(double n) { scale = n; }
	void setAlive(bool a) { isAlive = a; }
};
