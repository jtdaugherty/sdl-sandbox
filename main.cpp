
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"

void showImage(char *filename, SDL_Surface *screen, int x, int y)
{
    SDL_Surface *image;
    SDL_Rect dest;

    image = IMG_Load(filename);
    if (image == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", filename, SDL_GetError());
        return;
    }

    /* Blit onto the screen surface.
       The surfaces should not be locked at this point.
     */
    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;
    SDL_BlitSurface(image, NULL, screen, &dest);

    /* Update the changed portion of the screen */
    SDL_UpdateRects(screen, 1, &dest);
}

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    SDL_Event event;

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

    showImage((char *) "graphics/icons.png", screen, 0, 0);

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
