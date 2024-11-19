#ifndef GameObject_h
#define GameObject_h

class Game;

class GameObject
{
public:
	//Estos métodos no tienen implementación, se overridean desde cada GO.
	virtual void render() const = 0;
	virtual void update() = 0;
	
	//~GameObject();

protected:
	Game* game;

};

#endif