#ifndef GameObject_h
#define GameObject_h

class Game;

class GameObject
{
public:
	//Estos m�todos no tienen implementaci�n, se overridean desde cada GO.
	virtual void render() const;
	virtual void update();
	//Destructora para qu�?
	virtual ~GameObject();

protected:
	Game* game;

};

#endif

