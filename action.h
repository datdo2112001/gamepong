#include <iostream>
#include <SDL.h>
#include <bits/stdc++.h>
#include <SDL_image.h>
using namespace std;
#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED
struct character{
    int x;
int y;
int size=10;
int m=1;
character (int _x , int _y){
   x=_x;
   y=_y;
}
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
box (int _x , int _y){
   x=_x;
   y=_y;
}
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


#endif // ACTION_H_INCLUDED
