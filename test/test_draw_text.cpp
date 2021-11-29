#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("cycle. ", 
                                          100,
                                          100,
                                          600,
                                          600,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer *screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(screen, 230, 230, 230, 255);
    SDL_RenderFillRect(screen, NULL);
    SDL_RenderPresent(screen);

    /////////////////////////
    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = {255, 255, 255};

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, "put your text here", White); 

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(screen, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate 
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture
    SDL_RenderCopy(screen, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    //////////////////////////
    SDL_Delay(2000);
    SDL_DestroyRenderer(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();
}