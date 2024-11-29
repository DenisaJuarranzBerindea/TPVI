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
	SDL_RendererFlip flip;
	bool flipSprite;
	double scale;
	SDL_Rect colRect;	//Colisiones

	// Animaciones
	int frame;
	int frameTimer;

	// 
	bool isAlive;
	Collision c;
	bool canMove; 
	//GameList<SceneObject>::anchor _anchor; // Ancla a la lista de objetos del juego

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


	// Colisiones
	virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;
	virtual void manageCollisions(Collision collision) = 0;

	// Render
	virtual void render() override;

	// Update
	virtual void update() override {}

	// Animaciones
	virtual void updateAnim() = 0;

	// Clonar
	virtual SceneObject* clone() const = 0;

	// Getters
	Point2D<double> getPosition() { return position; }

	// Getters virtuales
	virtual SDL_Rect getCollisionRect() const;
	virtual SDL_Rect getRenderRect() const;

	// Input y demás events
	virtual void handleEvent(const SDL_Event& event);

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
