
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Surface *surf, int cell_width, int cell_height)
{
    this->surf = surf;
    this->cell_width = cell_width;
    this->cell_height = cell_height;
}

Sprite* SpriteSheet::get(int cell_x, int cell_y)
{
    SDL_Rect src;

    src.x = cell_x * this->cell_width;
    src.y = cell_y * this->cell_height;
    src.w = this->cell_width;
    src.h = this->cell_height;

    return new Sprite(this->surf, src);
}
