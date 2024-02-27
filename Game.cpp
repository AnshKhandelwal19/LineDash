#include "Classes/Enemy.h"
#include "Classes/Player.h"
#include "Classes/Line.h"

#include <iostream>
#include <vector>
#include <SDL.h>

//Screen Dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//SDL Variables
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* player_texture;
SDL_Texture* enemy_texture;
SDL_Texture* line_texture;

/*-----------------------------------
Load game sprites (images)
Return null if texture fails to load
Expects char* input for file location
-----------------------------------*/
SDL_Texture* loadMedia(const char* mediaLocation) {
    // Load texture from file location
    SDL_Surface* surface = SDL_LoadBMP(mediaLocation);
    if (surface == nullptr) {
        printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
        return nullptr;
    }
    //Create texture pointer using renderer and free surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        return nullptr;
    }
    return texture;
}

/*--------------------------------------------------
Initialize SDL Window, SDL Renderer, and SDL Surface
Initializes textures for game sprites
Expects char*[] input for sprite file location
Order: Player, Enemy, Line
Return false if initialization fails
--------------------------------------------------*/
bool init(const char* sprites[]) {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    // Create window
    window = SDL_CreateWindow("Line Jump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Load Game Sprites
    player_texture = loadMedia(sprites[0]);
    enemy_texture = loadMedia(sprites[1]);
    line_texture = loadMedia(sprites[2]);

    if(player_texture == nullptr || enemy_texture == nullptr || line_texture == nullptr)
        return false;

    return true;
}

/*---------------
Destroys pointers
Returns nothing
---------------*/
void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(enemy_texture);
    SDL_DestroyTexture(line_texture);
    SDL_Quit();
}

int main() {
    //Sprite array for image paths
    const char* sprites[] = {
        "path/to/player.bmp",
        "path/to/enemy.bmp",
        "path/to/line.bmp"
    };

    //Initialize SDL and Sprites
    if (!init(sprites)) {
        std::cerr << "Initialization failed!" << std::endl;
        return 1;
    }

    close(); //Clean up pointers
}