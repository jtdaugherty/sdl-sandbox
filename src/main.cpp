
#include <stdlib.h>
#include <stdexcept>
#include "SDL.h"
#include "SDL_Image.h"

#include "Param.h"
#include "BoardUI.h"
#include "SpriteSheet.h"
#include "Timer.h"
#include "Animation.h"

#define FRAMES_PER_SECOND 30

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    SDL_Event event;
    BoardUI b(3);
    Timer fps_timer;

    Animation a1(4), a2(30);
    SpriteSheet *s;

    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_EnableUNICODE(1);

    if (!SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE)) {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        exit(1);
    }

    screen = SDL_GetVideoSurface();

    SDL_Surface *i = IMG_Load("graphics/icons.png");
    s = new SpriteSheet(i, 34, 34);

    a1.add_frame(s->get(0, 0));
    a1.add_frame(s->get(0, 1));
    a1.add_frame(s->get(0, 2));
    a1.add_frame(s->get(0, 3));

    a2.add_frame(s->get(1, 0));
    a2.add_frame(s->get(1, 1));
    a2.add_frame(s->get(1, 2));
    a2.add_frame(s->get(1, 3));
    a2.add_frame(s->get(1, 4));
    a2.add_frame(s->get(1, 5));
    a2.add_frame(s->get(1, 6));
    a2.add_frame(s->get(1, 7));

    int t = SDL_GetTicks();

    a1.start(t);
    a2.start(t);

    while (1) {
        t = SDL_GetTicks();

        fps_timer.start();

        SDL_FillRect(screen, NULL, 0x0);

        b.blit(screen, 20, 20);

        a1.blit(screen, 200, 200, t);
        a2.blit(screen, 200, 300, t);

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

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse button %d pressed at (%d,%d)\n",
                       event.button.button, event.button.x, event.button.y);

                b.handleMouseClick(event.button.x - 20, event.button.y - 20);

                if (b.hasWinner()) {
                    printf("HAS WINNER!\n");
                    b.reset();
                } else if (!b.hasMovesLeft()) {
                    printf("No moves left, it's a draw!\n");
                    b.reset();
                }

                if (b.getCurrentState() == PLAYER_X)
                    printf("Player turn: X\n");
                else if (b.getCurrentState() == PLAYER_O)
                    printf("Player turn: O\n");
                else
                    printf("YIKES!\n");

                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.unicode > 0 &&
                    event.key.keysym.unicode < 0x80)
                    printf("Key: %c\n", (char) event.key.keysym.unicode);

                switch (event.key.keysym.unicode) {
                case 'q':
                    SDL_Quit();
                    exit(0);
                    break;
                }

                break;
            case SDL_QUIT:
                exit(0);
            }
        }

        // Imprecise but it's better than using all of the CPU time.
        // In this sort of game we don't actually need to render until
        // we get an event anyway, but this moves in the direction of
        // having a less input-driven engine.  Ideally we'll use
        // interpolation to determine everything else in the engine
        // and render as often as we can and we won't use the delay
        // technique at all.
        int t = fps_timer.get_ticks();
        if (t < (1000 / FRAMES_PER_SECOND))
            SDL_Delay((1000 / FRAMES_PER_SECOND) - t);
    }

    return 0;
}
