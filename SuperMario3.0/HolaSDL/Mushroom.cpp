#include "checkML.h"
#include "Mushroom.h"
#include "Game.h"
#include "Collision.h"

Mushroom::Mushroom(Game* g, Point2D<double> p, Texture* t)
	: Pickable(g, p, t)
{
	setScale(2);
	speed.setX(5);
	speed.setY(0);
}

void Mushroom::render()
{
	Pickable::render();
}

void Mushroom::update()
{
	cout << position.getY() << endl;

	moveSeta();
}

void Mushroom::moveSeta()
{
	// Acelra la velocidad con la gravedad
	if (speed.getY() < game->SPEED_LIMIT)
		speed = speed + Vector2D<double>(0, game->GRAVITY);

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<double> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = game->MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de direccion
	if (collision.horizontal)
		speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	// SceneObject::update(); // si hiciera falta
}

void Mushroom::triggerAction()
{
	game->setMarioState(1);
}

void Mushroom::updateAnim()
{

}

SceneObject* Mushroom::clone() const
{
	return new Mushroom(*this);
}