#include <iostream>
#include <SDL.h>
#include <bits/stdc++.h>


using namespace std;
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
struct character{
    int x;
int y;
int size=10;
int m=1;
void render(SDL_Renderer* renderer){
SDL_Rect filled_rect;
    filled_rect.x = x;
    filled_rect.y = y;
    filled_rect.w = size;
    filled_rect.h = size;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);

}
void left(){
  x-=15;
}
void right(){
    x+=15;
}
void up(){
  y-=15;
}
void down(){
  y+=15;
}
};
struct box{
int x;
int y;
int size=10;
int m=1;
void render(SDL_Renderer* renderer){
SDL_Rect filled_rect;
    filled_rect.x = x;
    filled_rect.y = y;
    filled_rect.w = size;
    filled_rect.h = size;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);

}
void moves(){

   if ( y<=500 && m==1 ){
    y+=5;
    if (y>500){
        m=0;
    }
   } else {
    y=y-5;
    if (y<10){
        m=1;
    }
   }
}
};
void waitUntilKeyPressed();
int main(int argc, char* argv[])
{    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    //
    box Box;
    Box.x=400;
    Box.y=10;
    box boss1;
    boss1.x=200;
    boss1.y=300;
    character boy;
    boy.x=10;
    boy.y=200;
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





