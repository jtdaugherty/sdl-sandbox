
#include <stdlib.h>
#include <stdexcept>
#include "SDL.h"
#include "SDL_Image.h"

#include "Param.h"
#include "BoardUI.h"
#include "SpriteSheet.h"
#include "Animation.h"

#define FRAMES_PER_SECOND 30

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    SDL_Event event;
    BoardUI board(3);

    Animation a(10), b(10), c(10), d(10);
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

    SDL_Surface *i = IMG_Load("graphics/rpg_sprite_walk.png");
    s = new SpriteSheet(i, 24, 32);

    a.add_frame(s->get(0, 0));
    a.add_frame(s->get(1, 0));
    a.add_frame(s->get(2, 0));
    a.add_frame(s->get(3, 0));
    a.add_frame(s->get(4, 0));
    a.add_frame(s->get(5, 0));
    a.add_frame(s->get(6, 0));
    a.add_frame(s->get(7, 0));

    b.add_frame(s->get(0, 1));
    b.add_frame(s->get(1, 1));
    b.add_frame(s->get(2, 1));
    b.add_frame(s->get(3, 1));
    b.add_frame(s->get(4, 1));
    b.add_frame(s->get(5, 1));
    b.add_frame(s->get(6, 1));
    b.add_frame(s->get(7, 1));

    c.add_frame(s->get(0, 2));
    c.add_frame(s->get(1, 2));
    c.add_frame(s->get(2, 2));
    c.add_frame(s->get(3, 2));
    c.add_frame(s->get(4, 2));
    c.add_frame(s->get(5, 2));
    c.add_frame(s->get(6, 2));
    c.add_frame(s->get(7, 2));

    d.add_frame(s->get(0, 3));
    d.add_frame(s->get(1, 3));
    d.add_frame(s->get(2, 3));
    d.add_frame(s->get(3, 3));
    d.add_frame(s->get(4, 3));
    d.add_frame(s->get(5, 3));
    d.add_frame(s->get(6, 3));
    d.add_frame(s->get(7, 3));

    // 24 wide, 32 high

    int t = SDL_GetTicks();

    a.start(t);
    b.start(t);
    c.start(t);
    d.start(t);

    while (1) {
        t = SDL_GetTicks();

        SDL_FillRect(screen, NULL, 0x0);

        board.blit(screen, 20, 20);

        a.blit(screen, 200, 200, t);
        b.blit(screen, 200, 250, t);
        c.blit(screen, 200, 300, t);
        d.blit(screen, 200, 350, t);

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

                board.handleMouseClick(event.button.x - 20, event.button.y - 20);

                if (board.hasWinner()) {
                    printf("HAS WINNER!\n");
                    board.reset();
                } else if (!board.hasMovesLeft()) {
                    printf("No moves left, it's a draw!\n");
                    board.reset();
                }

                if (board.getCurrentState() == PLAYER_X)
                    printf("Player turn: X\n");
                else if (board.getCurrentState() == PLAYER_O)
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
    }

    return 0;
}
