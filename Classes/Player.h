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
    //Set new position based on input (up,down,left,right)
    void move(Velocity v) {
        Coordinate pos = get_position();
        set_position(pos.x + v.x, pos.y + v.y);
    }
};

#endif