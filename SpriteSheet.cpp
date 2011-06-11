
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Surface *surf, int cell_width, int cell_height)
{
    this->surf = surf;
    this->cell_width = cell_width;
    this->cell_height = cell_height;
}

void SpriteSheet::put(SDL_Surface *dest_surf, int dest_x, int dest_y, int cell_x, int cell_y)
{
    SDL_Rect dest;
    SDL_Rect src;

    src.x = cell_x * this->cell_width;
    src.y = cell_y * this->cell_height;
    src.w = this->cell_width;
    src.h = this->cell_height;

    dest.x = dest_x;
    dest.y = dest_y;
    dest.w = this->cell_width;
    dest.h = this->cell_height;

    SDL_BlitSurface(this->surf, &src, dest_surf, &dest);
}
