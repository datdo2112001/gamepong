#include <iostream>
#include <SDL.h>
#include <string>
#include <time.h>
#include <SDL_image.h>
#include "action.h"
#include "common function.h"
#include <SDL_ttf.h>
using namespace std;
void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal = false);
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "PONG GAME ^.^";
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
// từ dòng 10 - 18 tham khảo slide cô Châu.
SDL_Texture* balltex;
SDL_Texture* player1tex;
SDL_Texture* form;
SDL_Texture* start;
SDL_Texture* endgame;
// khai báo các texture để ghép đồ họa.
int main(int argc, char* argv[])
{
    TTF_Init();                   // khởi tạo TTF.
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    // khởi tạo cửa sổ SDL.
    background open;
    bool signal = false;
    while (signal != true) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // tạo phông nền màu trắng cho cửa sổ.
        SDL_RenderClear(renderer);        // xóa hết hình ảnh cũ.
        open.render(renderer, start);     // in background ra màn hình.
        SDL_RenderPresent(renderer);      // in hình ảnh hiện tại.
        SDL_Event e;                      // tạo 1 biến để nhận sự kiện từ bàn phím.
        SDL_Delay(5);
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;

            case SDLK_a: signal = true;
                break;
            default: break;
            }
        }
    }
    ///// Từ dòng 27 - 53 mục đích tạo 1 cửa sổ ban đầu , cho phép nhập a vào để bắt đầu game , nếu nhận được tín hiệu a thì sẽ chuyển cảnh.

    if (signal == true) {
        bool quit = false;
        while (quit == false) {
            srand(time(0));
            SDL_RenderClear(renderer);
            //// Từ dòng 60 - 67 khởi tạo các obj về player 1 , player 2 , ball ;
            racket player1(10, 200);
            racket player2(770, 200);
            ball bounce(200, 300, -3.15, -3.15);
            background bg;
            int point1 = 0;
            int point2 = 0;
            // điểm số trong game.

            while (point1 <= 5 && point2 <= 5) {
                bounce.moves();
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_Event e;

                //////// xác định phương hướng cho quả bóng để nó nảy.(78 - 86)
                if (bounce.x >= -10 && bounce.x <= 400) {
                    bounce.direction(player1.x, player1.y);
                }
                else if (bounce.x >= 400 && bounce.y <= 810) {
                    bounce.direction(player2.x, player2.y);
                }
                // Xác định tọa độ của bóng để tính point1 , point2.
                if (bounce.x <= 5) {
                    point2++;
                    cout << point1 << " " << point2 << endl;
                }
                else if (bounce.x >= 797) {
                    point1++;
                    cout << point1 << " " << point2 << endl;
                }

                bg.render(renderer, form);
                bounce.render(renderer, balltex);
                player2.render(renderer, player1tex);
                player1.render(renderer, player1tex);
                rendertext(renderer, to_string(point1), 300, 20);
                rendertext(renderer, to_string(point2), 500, 20);
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

            // khi game over thì nhập backspace để chơi lại .
            SDL_RenderClear(renderer);
            bool node = false;
            background endtask;
            while (node != true) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                endtask.render(renderer, endgame);
                SDL_RenderPresent(renderer);
                SDL_Event m;
                SDL_Delay(5);
                if (SDL_PollEvent(&m) == 0) continue;
                if (m.type == SDL_QUIT) {
                    quit = true;
                    break;
                }
                if (m.type == SDL_KEYDOWN) {
                    switch (m.key.keysym.sym) {
                    case SDLK_ESCAPE break;

                    case SDLK_BACKSPACE: node = true;
                        break;
                    default: break;
                    }
                }
            }
        }



        
            quitSDL(window, renderer);
            TTF_Quit();
            return 0;
    }
}
    /////// toàn bộ các cách nhận tín hiệu từ bàn phím được tham khảo từ video của cô Châu trên youtube.


void logSDLError(std::ostream& os,
        const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
         SDL_Quit();
         exit(1);
    }
}
///// hàm trên dc tham khảo từ slide cô châu.
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    ///// đoạn code trên tham khảo từ slide cô Châu.
    SDL_Surface* surface1 = IMG_Load("ball.png");
    balltex = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_FreeSurface(surface1);
    SDL_Surface* surface2 = IMG_Load("racket.png");
    player1tex = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
    SDL_Surface* surface3 = IMG_Load("background2.png");
    form = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_FreeSurface(surface3);
    SDL_Surface* sf = IMG_Load("startbackground.png");
    start = SDL_CreateTextureFromSurface(renderer, sf);
    SDL_FreeSurface(sf);
    SDL_Surface* sf2 = IMG_Load("endtask.png");
    endgame = SDL_CreateTextureFromSurface(renderer, sf2);
    SDL_FreeSurface(sf2);
    
    ////// tạo các surface để gán đồ họa (163 - 174) : có xem hướng dẫn qua 1 video trên youtube.
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
///// Từ dòng 211 đến 225 đều được tham khảo từ slide cô Châu.









