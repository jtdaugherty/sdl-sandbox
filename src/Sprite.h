
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "SDL.h"

class Sprite {
 public:
    // Takes a surface but does NOT free it at any time.  The sprite
    // creator should take care of that.
    Sprite(SDL_Surface *surf);
    Sprite(SDL_Surface *surf, SDL_Rect src_rect);

    void blit(SDL_Surface *dest);
    void blit(SDL_Surface *dest, int x, int y);

    void setXY(int x, int y);
    int getX(void);
    int getY(void);
    int w(void);
    int h(void);

    void show(void);
    void hide(void);

 private:
    void defaults(void);

    SDL_Surface *surf;
    SDL_Rect src_rect;
    SDL_Rect dest_rect;
    int x, y;
    bool visible;
};

#endif
