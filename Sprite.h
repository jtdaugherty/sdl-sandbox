
#include "SDL.h"

class Sprite {
 public:
    // Takes a surface but does NOT free it at any time.  The sprite
    // creator should take care of that.
    Sprite(SDL_Surface *surf, SDL_Rect src_rect);

    void blit(SDL_Surface *dest);
    void setXY(int x, int y);
    int getX(void);
    int getY(void);

 private:
    SDL_Surface *surf;
    SDL_Rect src_rect;
    SDL_Rect dest_rect;
    int x, y;
};
