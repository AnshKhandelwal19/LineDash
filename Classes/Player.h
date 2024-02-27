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
    void move(std::string direction) {
        Coordinate pos = get_position();
        if (direction == "up")
            pos.y++;
        else if (direction == "down")
            pos.y--;
        else if (direction == "left")
            pos.x--;
        else if (direction == "right")
            pos.x++;
        else 
            return;
        set_position(pos);
    }
};

#endif