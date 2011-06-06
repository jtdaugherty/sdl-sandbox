
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

    SDL_UpdateRects(dest_surf, 1, &dest);
}

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Event event;
    SDL_Rect clip;

    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        exit(1);
    }

    clip.x = 34;
    clip.y = 34;
    clip.w = 34;
    clip.h = 34;

    image = IMG_Load("graphics/icons.png");
    if (image == NULL) {
        printf("Could not load image: %s\n", SDL_GetError());
    } else {
        ImageGrid *g = new ImageGrid(image, 34, 34);
        g->put(screen, 10, 10, 0, 0);
        g->put(screen, 50, 50, 0, 1);
    }

    while (1) {
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_KEYDOWN:
            printf("The %s key was pressed!\n",
                   SDL_GetKeyName(event.key.keysym.sym));
            break;
        case SDL_KEYUP:
            printf("The %s key was released.\n",
                   SDL_GetKeyName(event.key.keysym.sym));
            break;
        case SDL_QUIT:
            printf("Some quit stuff happened\n");
            exit(0);
        }
    }

    return 0;
}
