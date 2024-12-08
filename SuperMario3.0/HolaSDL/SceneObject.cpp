#include "checkML.h"
#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* g, Point2D<double> pos, Texture* t)
    : GameObject(g), position(pos), texture(t), scale(1), isAlive(true), colRect(),
    frame(0), frameTimer(0)
{
    width = g->TILE_SIDE;
    height = g->TILE_SIDE;
}

SceneObject::SceneObject(Game* g, Point2D<double> pos, Texture* texture, Vector2D<double> speed)
    : GameObject(g), position(pos), texture(texture), scale(1), isAlive(true), colRect(),
    speed(speed), frame(0), frameTimer(0)
{
    width = g->TILE_SIDE;
    height = g->TILE_SIDE;
}

SceneObject::SceneObject(const SceneObject& s) : GameObject(s.game)
{
    game = s.game;

    // movimiento
    position = s.position;
    speed = s.speed;
    direction = s.direction;

    // representacion
    width = s.width;
    height = s.height;
    texture = s.texture;
    flip = s.flip;
    flipSprite = s.flipSprite;
    scale = s.scale;
    colRect = s.colRect;

    // animacion
    frame = s.frame;
    frameTimer = s.frameTimer;

    // logica
    isAlive = s.isAlive;
    c = s.c;
    canMove = s.canMove;
}

SceneObject& SceneObject::operator=(const SceneObject& s)
{
    if (this != &s)
    {
        game = s.game;

        // Movimiento
        position = s.position;
        speed = s.speed;
        direction = s.direction;

        // Representación
        width = s.width;
        height = s.height;
        texture = s.texture;
        flip = s.flip;
        flipSprite = s.flipSprite;
        scale = s.scale;
        colRect = s.colRect;

        // Animación
        frame = s.frame;
        frameTimer = s.frameTimer;

        // Lógica
        isAlive = s.isAlive;
        c = s.c;
        canMove = s.canMove;
    }
    return *this;
}

SDL_Rect SceneObject::getCollisionRect() const
{
    return SDL_Rect{
        int(position.getX()),
        int(position.getY()),
        width,
        height
    };
}

SDL_Rect SceneObject::getRenderRect() const
{
    return SDL_Rect{
        int(position.getX() - game->getMapOffset()),
        int(position.getY() - height),
        width,
        height
    };
}

void SceneObject::render()
{
    colRect.x = position.getX() - game->getMapOffset();
    colRect.h = texture->getFrameHeight() * scale;
    colRect.w = texture->getFrameWidth() * scale;

    if (texture == game->getTexture(Game::SUPERMARIO)) // esto en el player
    {
        colRect.y = position.getY() - game->TILE_SIDE / 2;
    }
    else
    {
        colRect.y = position.getY();
    }

    texture->renderFrame(colRect, 0, frame, 0, nullptr, flip);
}

void SceneObject::manageCollisions(Collision c)
{

}

Collision SceneObject::tryToMove(const Vector2D<double>& speed, Collision::Target target)
{
    // Enunciado
    Collision c;
    SDL_Rect rect = getCollisionRect();

    // Movimiento vertical
    if (speed.getY() != 0) {
        rect.y += speed.getY();
        c = game->checkCollisions(rect, target);

        // Cantidad que se ha entrado en el obst?culo (lo que hay que deshacer)
        int fix = c.vertical * (speed.getY() > 0 ? 1 : -1);
        //position += {0, speed.getY() - fix};
        position = position + Vector2D<double>(0, speed.getY() - fix);

        rect.y -= fix; // recoloca la caja para la siguiente colisi?n
    }

    c.horizontal = 0;

    // Intenta moverse en horizontal
    // (podr?a ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
    if (speed.getX() != 0) {
        rect.x += speed.getX();

        Collision partial = game->checkCollisions(rect, target);

        // Copia la informaci?n de esta colisi?n a la que se devolver?
        c.horizontal = partial.horizontal;

        if (partial.result == Collision::DAMAGE)
            c.result = Collision::DAMAGE;

        //position += {speed.getX() - c.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
        position = position + Vector2D<double>(speed.getX() - c.horizontal * (speed.getX() > 0 ? 1 : -1), 0);
    }

    return c;
}