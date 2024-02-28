#include "Classes/Enemy.h"
#include "Classes/Player.h"
#include "Classes/Line.h"

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

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
    SDL_Surface* surface = IMG_Load(mediaLocation);
    if (surface == nullptr) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return nullptr;
    }

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
    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
    IMG_Quit();
}

int main() {
    Player player = Player();

    //Sprite array for image paths
    const char* sprites[] = {
        "Sprites/Player.png",
        "Sprites/Enemy.png",
        "Sprites/Player.png"
    };

    //Initialize SDL and Sprites
    if (!init(sprites)) {
        std::cerr << "Initialization failed!" << std::endl;
        return 1;
    }

    int playerWidth, playerHeight;
    SDL_QueryTexture(player_texture, NULL, NULL, &playerWidth, &playerHeight);

    // Set the initial position of the player
    player.set_position(SCREEN_WIDTH / 2 - playerWidth / 2, SCREEN_HEIGHT / 2 - playerHeight / 2);

    // Game Loop
    SDL_Event e;
    bool quit = false;

    while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_w:
                            player.set_velocity(0, -5);
                            break;
                        case SDLK_s:
                            player.set_velocity(0, 5);
                            break;
                        case SDLK_a:
                            player.set_velocity(-5, 0);
                            break;
                        case SDLK_d:
                            player.set_velocity(5, 0);
                            break;
                    }
                } else if (e.type == SDL_KEYUP) {
                    switch (e.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_s:
                            player.set_velocity(player.get_velocity().x, 0);
                            break;
                        case SDLK_a:
                        case SDLK_d:
                            player.set_velocity(0, player.get_velocity().y);
                            break;
                    }
                }
            }
        // Update player position based on velocity
        player.move(player.get_velocity());

        // Your game logic goes here

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the player texture
        SDL_Rect playerRect = { player.get_position().x, player.get_position().y, playerWidth, playerHeight };
        SDL_RenderCopy(renderer, player_texture, NULL, &playerRect);

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Delay to control frame rate (adjust as needed)
        SDL_Delay(16);  // 16 milliseconds for approximately 60 frames per second
    }

    close(); //Clean up pointers
}