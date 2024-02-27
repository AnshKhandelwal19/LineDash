#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <string>

/*-----------------------------------------------------------------------------------------
The enemy class implements methods for changing enemy position and implementing movement
Enemies move in a direct line following a randomly generated slope and y-intercept
Inherits the Entity class
-----------------------------------------------------------------------------------------*/
class Enemy : public Entity {

    int slope;
    int y_intercept;

    public:
    Enemy(int screen_height) {
        slope = generate_random_number(10);
        y_intercept = generate_random_number(screen_height);
        set_position(0, y_intercept);
    }
    //Function increments x value and calculates y value by moving along the line
    void process_movement() {
        Coordinate pos = get_position();
        pos.x++;
        pos.y = (slope * pos.x) + y_intercept;
    }
};

#endif