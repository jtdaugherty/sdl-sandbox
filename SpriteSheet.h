
#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__

#include "SDL.h"
#include "Sprite.h"

class SpriteSheet {
public:
    SpriteSheet(SDL_Surface *surf, int cell_width, int cell_height);

    Sprite* get(int cell_x, int cell_y);

private:
    int cell_width, cell_height;
    SDL_Surface *surf;
};

#endif
