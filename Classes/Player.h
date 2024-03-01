#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <string>

/*-----------------------------------------------------------------------------------------
The player class implements methods for changing player position and implementing abilities
Inherits the Entity class
-----------------------------------------------------------------------------------------*/
class Player : public Entity {
    public:
    void jump(Velocity v) {
        set_position(get_position().x + v.x, get_position().y + v.y);
    }
};

#endif