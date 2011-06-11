
#include "SDL.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Surface *surf, SDL_Rect *src_rect)
{
    this->surf = surf;
    this->src_rect = src_rect;

    this->dest_rect.x = 0;
    this->dest_rect.y = 0;
    this->dest_rect.w = this->surf->w;
    this->dest_rect.h = this->surf->h;
}

void Sprite::setXY(int x, int y)
{
    this->dest_rect.x = x;
    this->dest_rect.y = y;
}

int Sprite::getX(void)
{
    return this->dest_rect.x;
}

int Sprite::getY(void)
{
    return this->dest_rect.y;
}

void Sprite::blit(SDL_Surface *dest)
{
    SDL_BlitSurface(this->surf, this->src_rect,
                    dest, &this->dest_rect);
}