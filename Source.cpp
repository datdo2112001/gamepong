#include <iostream>
#include <SDL.h>
#include <string>
#include <time.h>
#include <SDL_image.h>
#include "action.h"


using namespace std;
void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal = false);
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "PONG GAME ^.^";
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* balltex;
SDL_Texture* player1tex;
SDL_Texture* player2tex;

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    //
    racket player1(10, 200);
    racket player2(770, 200);
    bot computer(770, 200);
    ball bounce(200, 300, -3.15, -3.15);
    while (true) {
        bounce.moves();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Event e;
        int turn = 0;

       
        if (bounce.x >= -10 && bounce.x <= 400 ) {
           
                bounce.direction(player1.x, player1.y);
                

        } 
        else if (bounce.x >= 400 && bounce.y <= 810 ) {
            
                bounce.direction(player2.x, player2.y);
            
        }
        
        
        bounce.render(renderer,balltex);
        player2.render(renderer,player1tex);
        player1.render(renderer,player1tex);

        SDL_RenderPresent(renderer);
         
        // Your drawing code here
        // use SDL_RenderPresent(renderer) to show it

        SDL_Delay(5);
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;
      
            case SDLK_2: player1.down();
                break;
            case SDLK_1: player1.up();
                break;
            
            default: break;
            }


        }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;

            case SDLK_UP: player2.up();
                break;
            case SDLK_DOWN: player2.down();
                break;
            default: break;
            }


        }
    }

    quitSDL(window, renderer);
    return 0;
}
void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface* surface1 = IMG_Load("C:/Users/DO DINH DAT/source/repos/gameproject/gameproject/platformIndustrial_057.png");
    balltex = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_FreeSurface(surface1);
    SDL_Surface* surface2 = IMG_Load("C:/Users/DO DINH DAT/source/repos/gameproject/gameproject/platformIndustrial_064.png");
    player1tex = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
    SDL_Surface* surface3 = IMG_Load("C:/Users/DO DINH DAT/source/repos/gameproject/gameproject/platformIndustrial_064.png");
    player1tex = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_FreeSurface(surface3);

}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}








