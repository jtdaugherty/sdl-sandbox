
#include <stdlib.h>
#include <stdexcept>
#include "SDL.h"
#include "SDL_image.h"

#include "Board.h"
#include "SpriteSheet.h"

bool in_rect(int x, int y, SDL_Rect r)
{
    return (x >= r.x &&
            y >= r.y &&
            x < (r.x + r.w) &&
            y < (r.y + r.h));
}

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Event event;
    Board b(3);

    SDL_Surface *x;
    SDL_Surface *o;
    SDL_Surface *blank;

    Sprite *x_sprite;
    Sprite *o_sprite;
    Sprite *blank_sprite;

    SDL_Rect **board_rects;

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

    x = IMG_Load("graphics/x.gif");
    if (x == NULL) {
        printf("Could not load x image: %s\n", SDL_GetError());
        exit(1);
    }

    o = IMG_Load("graphics/o.gif");
    if (o == NULL) {
        printf("Could not load o image: %s\n", SDL_GetError());
        exit(1);
    }

    blank = IMG_Load("graphics/blank.gif");
    if (blank == NULL) {
        printf("Could not load blank image: %s\n", SDL_GetError());
        exit(1);
    }

    x_sprite = new Sprite(x);
    o_sprite = new Sprite(o);
    blank_sprite = new Sprite(blank);

    screen = SDL_GetVideoSurface();

    board_rects = new SDL_Rect*[b.size()];
    for (int i = 0; i < b.size(); i++) {
        board_rects[i] = new SDL_Rect[b.size()];
        for (int j = 0; j < b.size(); j++) {
            board_rects[i][j].x = i * blank_sprite->w();
            board_rects[i][j].y = j * blank_sprite->h();
            board_rects[i][j].w = blank_sprite->w();
            board_rects[i][j].h = blank_sprite->h();
        }
    }

    State cur_state = PLAYER_X;

    while (1) {
        SDL_FillRect(screen, NULL, 0x0);

        // Inspect the board state to determine which things to draw,
        // and where.
        int sz = b.size();
        State s;
        Sprite *sp;

        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                s = b.getState(i, j);
                switch (s) {
                case NONE:
                    sp = blank_sprite;
                    break;
                case PLAYER_X:
                    sp = x_sprite;
                    break;
                case PLAYER_O:
                    sp = o_sprite;
                    break;
                }

                sp->blit(screen, board_rects[i][j].x, board_rects[i][j].y);
            }
        }

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
        case SDL_MOUSEBUTTONDOWN:
            printf("Mouse button %d pressed at (%d,%d)\n",
                   event.button.button, event.button.x, event.button.y);

            // Compute which board cell, if any, this corresponds to.
            for (int i = 0; i < b.size(); i++)
                for (int j = 0; j < b.size(); j++)
                    if (in_rect(event.button.x, event.button.y,
                                board_rects[i][j])) {
                        b.nextMove(i, j, cur_state);
                        cur_state = ((cur_state == PLAYER_X) ? PLAYER_O : PLAYER_X);
                    }

            if (b.hasWinner()) {
                printf("HAS WINNER!\n");
                b.reset();
                cur_state = PLAYER_X;
            }

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

    return 0;
}
