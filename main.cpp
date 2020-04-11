#include <iostream>
#include <SDL.h>
#include <bits/stdc++.h>
#include <SDL_image.h>
#include "action.h"

using namespace std;
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
int main(int argc, char* argv[])
{    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    //
    box Box(400,10);
    box boss1(200,300);
    character boy(10,200);
    while(true){
    Box.moves();
    boss1.moves();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    Box.render(renderer);
    SDL_Event e;
    boss1.render(renderer);
    boy.render(renderer);

    SDL_RenderPresent(renderer);

    // Your drawing code here
    // use SDL_RenderPresent(renderer) to show it

    SDL_Delay(10);
    if ( SDL_PollEvent(&e) == 0) continue;
    if (e.type == SDL_QUIT) break;
    if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: break;
        		case SDLK_LEFT: boy.left();break;

            	case SDLK_RIGHT: boy.right();
            		break;
            	case SDLK_DOWN: boy.down();
					break;
            	case SDLK_UP: boy.up();
            		break;
        		default: break;
			}


    }}

    quitSDL(window, renderer);
    return 0;
}
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

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
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}





