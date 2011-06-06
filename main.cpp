
#include <stdlib.h>
#include <stdexcept>
#include "SDL.h"
#include "SDL_image.h"

class ImageGrid {
public:
    ImageGrid(SDL_Surface *surf, int cell_width, int cell_height);

    void put(SDL_Surface *dest, int dest_x, int dest_y, int cell_x, int cell_y);

private:
    int cell_width, cell_height;
    SDL_Surface *surf;
};

ImageGrid::ImageGrid(SDL_Surface *surf, int cell_width, int cell_height)
{
    this->surf = surf;
    this->cell_width = cell_width;
    this->cell_height = cell_height;
}

void ImageGrid::put(SDL_Surface *dest_surf, int dest_x, int dest_y, int cell_x, int cell_y)
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

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    if (!SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE)) {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        exit(1);
    }

    image = IMG_Load("graphics/icons.png");
    if (image == NULL) {
        printf("Could not load image: %s\n", SDL_GetError());
        exit(1);
    }

    ImageGrid *g = new ImageGrid(image, 34, 34);
    int x, y;

    screen = SDL_GetVideoSurface();

    while (1) {
        SDL_FillRect(screen, NULL, 0x0);
        g->put(screen, x, y, 0, 0);
        // We'd call this, but then we'd have to figure out where the
        // image *was* before it got moved, and where it is now, in
        // order to ensure that the correct area gets updated.  We
        // probably don't care, though, since in general we'll just
        // clear the buffer, draw everything in the right order, and
        // copy it to the screen without trying to be too clever about
        // which areas can be skipped safely.
        //
        // SDL_UpdateRects(dest_surf, 1, &dest);
        SDL_Flip(screen);

        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LEFT) {
                x -= 5;
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                x += 5;
            } else if (event.key.keysym.sym == SDLK_UP) {
                y -= 5;
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                y += 5;
            }
            break;
        case SDL_QUIT:
            printf("Some quit stuff happened\n");
            exit(0);
        }
    }

    return 0;
}
