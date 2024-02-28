#ifndef ENTITY_H
#define ENTITY_H

#include <random>
//Function generates random number
int generate_random_number(int max) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd());  // Seed the Mersenne Twister engine

    // Define the distribution (e.g., integers between 1 and 100)
    std::uniform_int_distribution<int> distribution(0, max);

    // Generate a random number
    return distribution(gen);
}

/*-------------------------------------------------------------------------------
Coordinate structure is used to tell the position of an entity in the game window
Has two values: 
    x-coordinate (horizontal position)
    y-coordinate (vertical position)
-------------------------------------------------------------------------------*/
struct Coordinate {
    int x;
    int y;
};

/*-------------------------------------------------------------------------------
Velocity structure is used to tell the velocity of an entity in the game window
Has two values: 
    x-coordinate (horizontal velocity)
    y-coordinate (vertical velocity)
-------------------------------------------------------------------------------*/
struct Velocity {
    int x;
    int y;
};

/*-----------------------------------------------------------------------
Entity class is a derived class that initializes the coordinate structure
Implements common methods for enemies and player such as getters
-----------------------------------------------------------------------*/
class Entity {

    Coordinate pos;
    Velocity vel;

    public:
    //Set position coordinate with x,y input
    void set_position(int x, int y) {
        pos.x = x;
        pos.y = y;
    }
    void set_position(Coordinate newPos) {
        pos.x = newPos.x;
        pos.y = newPos.y;
    }
    //Get position coordinate
    Coordinate get_position() { return pos; }
    Velocity get_velocity() { return vel; }
    void set_velocity(int new_x, int new_y) { vel.x = new_x; vel.y = new_y; }

};

#endif