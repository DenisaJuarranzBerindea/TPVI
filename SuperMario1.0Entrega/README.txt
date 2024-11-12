# Informaci�n sobre la Pr�ctica SUPER MARIO V1.0 (Semientrega el 29/10)

- Solo 1 Nivel.
- Enemigos Goomba y Koopa
- UI en consola (vidas restantes, ganar/perder)
- Animaci�n solo en personajes y bloques sorpresa
- NO TIEMPO, NO PUNTOS.

# Dise�o por clases:

- class Texture (dada en clase)
- class Vector2D (solo .h):
	https://github.com/ElkMonster/Point2D/blob/master/Point2D.cpp
	Representa vectores o puntos en 2 dimensiones (propiedades tipo T x, y)
	Constructora
	Getters/Setters de x e y
	operador+ Suma(), operador- Resta(), producto escalar()
	Template para el USING Vector2D (T2, DIAPO 21)
- class Tilemap
	Dibuja escenario. Accede a Texture. 
	Puntero a textura del bg. 
	Matriz [][] para el mapa. 
	Constructora - lee el csv.
	M�todos: Render, Update y Hit
- class Block
	Contiene Point2D, enum tipo(), enum acci�n(), puntero textura, puntero juego.
	Constructora
	M�todos: render, update, hit.
- class Goomba
	Contiene Point2D, direcci�n (point2D), puntero textura, puntero juego.
	Constructora
	M�todos: render, update, hit
- class Koopa
	Contiene Point2D, direcci�n (point2D), puntero textura, puntero juego.
	Constructora
	M�todos: render, update, hit
	*Se ampliar� en V2.0
- class Mushroom
	Contiene Point2D, direcci�n (point2D), puntero textura, puntero juego. 
- class Player
	Contiene Point2D, direcci�n (point2D), puntero textura, puntero juego, int vidas, aspecto (bool SuperMario)
	Constructora
	M�todos: render, update, hit, handleEvents
- class Game
	Contiene tama�o ventana, mapOffset, punteros a ventana y a renderer, punteros a gameElems (Point2D), bool exit, array tecturas. 
	Constantes
	M�todos p�blicos: inicio y destrucci�n, run
	M�todos privados: render, update, handleEvents
	Getter: getMapOffset
	Collides






