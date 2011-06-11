
#include "SDL.h"

class SpriteSheet {
public:
    SpriteSheet(SDL_Surface *surf, int cell_width, int cell_height);

    void put(SDL_Surface *dest, int dest_x, int dest_y, int cell_x, int cell_y);

private:
    int cell_width, cell_height;
    SDL_Surface *surf;
};
