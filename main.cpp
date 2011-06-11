
#include <stdlib.h>
#include <stdexcept>
#include "SDL.h"
#include "SDL_image.h"

#include "SpriteSheet.h"

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_EnableUNICODE(1);

    if (!SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE)) {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        exit(1);
    }

    image = IMG_Load("graphics/icons.png");
    if (image == NULL) {
        printf("Could not load image: %s\n", SDL_GetError());
        exit(1);
    }

    SpriteSheet *sh = new SpriteSheet(image, 34, 34);
    int x, y;
    Sprite *s = sh->get(0, 0);

    screen = SDL_GetVideoSurface();

    while (1) {
        SDL_FillRect(screen, NULL, 0x0);

        s->blit(screen, x, y);

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
            } else {
                if (event.key.keysym.unicode > 0 &&
                    event.key.keysym.unicode < 0x80)
                    printf("Key: %c\n", (char) event.key.keysym.unicode);

                switch (event.key.keysym.unicode) {
                case 'q':
                    SDL_Quit();
                    exit(0);
                    break;
                }
            }
            break;
        case SDL_QUIT:
            exit(0);
        }
    }

    return 0;
}
