
#include "SDL.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Surface *surf)
{
    this->surf = surf;
    this->defaults();
}

Sprite::Sprite(SDL_Surface *surf, SDL_Rect src_rect)
{
    this->surf = surf;
    this->defaults();
    this->src_rect = src_rect;
}

// Must set surf before calling.
void Sprite::defaults(void)
{
    this->visible = true;

    this->src_rect.x = 0;
    this->src_rect.y = 0;
    this->src_rect.w = this->surf->w;
    this->src_rect.h = this->surf->h;

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

int Sprite::w(void)
{
    return this->surf->w;
}

int Sprite::h(void)
{
    return this->surf->h;
}

void Sprite::blit(SDL_Surface *dest)
{
    if (this->visible)
        SDL_BlitSurface(this->surf, &this->src_rect,
                        dest, &this->dest_rect);
}

void Sprite::blit(SDL_Surface *dest, int x, int y)
{
    this->setXY(x, y);
    this->blit(dest);
}

void Sprite::show(void)
{
    this->visible = true;
}

void Sprite::hide(void)
{
    this->visible = false;
}
