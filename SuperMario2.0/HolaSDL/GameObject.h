#ifndef GameObject_h
#define GameObject_h

class Game;

class GameObject
{
public:
	//Estos métodos no tienen implementación, se overridean desde cada GO.
	virtual void render() const;
	virtual void update();
	//Destructora para qué?
	virtual ~GameObject();

protected:
	Game* game;

};

#endif

