#pragma once
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_image.h>
#include "common function.h"
using namespace std;
#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

struct racket {
    int x;
    int y;
    racket(int _x, int _y) {
        x = _x;
        y = _y;
    }
    void render(SDL_Renderer* renderer, SDL_Texture* tex) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = 20;
        filled_rect.h = 80;

        SDL_RenderCopy(renderer, tex, NULL, &filled_rect);
    }
    void up() {
        y -= 30;
        if (checkout(x, y) == false)
        y += 30;
    }
    void down() {
        y += 30;
            if (checkout(x, y) == false)
                y -= 30;
    }
};
struct ball {
    int x;
    int y;
    int size = 20;
    double step1;
    double step2;

    ball(int _x, int _y, double _step1, double _step2) {
        x = _x;
        y = _y;
        step1 = _step1;
        step2 = _step2;
    }
    void direction(double _x, double _y) {
        int xxx = crash(_x, _y, x, y);
        double a, b;
        a = 3.15, b = 3.15;

        if (xxx == 1) {
            a = 3.4;
            b = 3.8;
            step(step1, step2, a, b, x, y);

        }
        else if (xxx == 2) {
            a = 3.2;
            b = 3.5;
            step(step1, step2, a, b, x, y);

        }
        else if (xxx == 3) {
            a = 3.3;
            b = 3.3;
            step(step1, step2, a, b, x, y);

        }
        else if (xxx == 4) {
            a = 3.3;
            b = 3.6;
            step(step1, step2, a, b, x, y);

        }



        if (y + 20 >= 600 || y <= 0) {
            a = 3.15;
            b = 3.15;
            step(step1, step2, a, b, x, y);
        }
        if (x <= 0 || x >= 800) {
            x = 200;
            y = 200;
            step1 = 3.15;
            step2 = 3.15;
        }


    }
    void render(SDL_Renderer* renderer , SDL_Texture * tex) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = size;
        filled_rect.h = size;
        
        SDL_RenderCopy(renderer,tex, NULL, &filled_rect);
    }
    void moves() {
        x += step1;
        y += step2;

    }
};
struct bot {
    int x;
    int y;
    bot(int _x, int _y) {
        x = _x;
        y = _y;
    }
    void render(SDL_Renderer* renderer) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = 20;
        filled_rect.h = 80;
        SDL_SetRenderDrawColor(renderer, 225, 0, 0, 255); // green
        SDL_RenderFillRect(renderer, &filled_rect);

    }
};


#endif // ACTION_H_INCLUDED
