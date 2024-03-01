#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <iostream>
#include <math.h>

/*-----------------------------------------------------------------------------------------
The enemy class implements methods for changing enemy position and implementing movement
Enemies move in a direct line toward player
Inherits the Entity class
-----------------------------------------------------------------------------------------*/
class Enemy : public Entity {
    int quadrant;  //Values can be 1,2,3,4 to specify which corner to spawn the sprite
    public:
    Enemy(int screen_width, int screen_height, int quad) {
        quadrant = quad;
        set_position(screen_height, screen_width);
        std::cout << "Quad: " << quadrant << " Position: " << get_position().x << " " << get_position().y << std::endl;
    }

    void set_velocity(Coordinate pPos, int staticV) {
        Coordinate ePos = get_position();
        Velocity v;

        //Create initial velocity vector pointing toward player position
        v.x = pPos.x - ePos.x;
        v.y = pPos.y - ePos.y;

        //Transform vector magnitute to requested velocity
        int mag = sqrt(v.x*v.x + v.y*v.y); //Pythagorean Theorem to get magnitude

        //Use magnitute to transform vector
        v.x = v.x/(mag/staticV);
        v.y = v.y/(mag/staticV);
        Entity::set_velocity(v.x, v.y);
    }

    int get_quadrant() { return quadrant; }
    void set_position(int screen_height, int screen_width) {
        switch (quadrant) {
        case 1:
            Entity::set_position(0, screen_height);
            break;
        case 2:
            Entity::set_position(screen_width, screen_height);
            break;
        case 3:
            Entity::set_position(screen_width, 0);
            break;
        case 4:
            Entity::set_position(0, 0);
            break;
        default:
            std::cout << "Invaild Quadrant" << std::endl;
            Entity::set_position(0,0);
            break;
        }
    }
};

#endif