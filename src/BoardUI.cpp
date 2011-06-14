
#include "SDL_image.h"
#include "BoardUI.h"

bool in_rect(int x, int y, SDL_Rect r)
{
    return (x >= r.x &&
            y >= r.y &&
            x < (r.x + r.w) &&
            y < (r.y + r.h));
}

BoardUI::BoardUI(int sz) :
    Board(sz)
{
    this->x = IMG_Load("graphics/x.gif");
    if (this->x == NULL)
        printf("Could not load x image: %s\n", SDL_GetError());

    this->o = IMG_Load("graphics/o.gif");
    if (this->o == NULL)
        printf("Could not load o image: %s\n", SDL_GetError());

    this->blank = IMG_Load("graphics/blank.gif");
    if (this->blank == NULL)
        printf("Could not load blank image: %s\n", SDL_GetError());

    this->x_sprite = new Sprite(this->x);
    this->o_sprite = new Sprite(this->o);
    this->blank_sprite = new Sprite(this->blank);

    this->rects = new SDL_Rect*[this->size()];
    for (int i = 0; i < this->size(); i++) {
        this->rects[i] = new SDL_Rect[this->size()];
        for (int j = 0; j < this->size(); j++) {
            this->rects[i][j].x = i * this->blank_sprite->w();
            this->rects[i][j].y = j * this->blank_sprite->h();
            this->rects[i][j].w = this->blank_sprite->w();
            this->rects[i][j].h = this->blank_sprite->h();
        }
    }
}

BoardUI::~BoardUI()
{
    delete this->x_sprite;
    delete this->o_sprite;
    delete this->blank_sprite;

    SDL_FreeSurface(this->x);
    SDL_FreeSurface(this->o);
    SDL_FreeSurface(this->blank);

    for (int i = 0; i < this->size(); i++)
        delete this->rects[i];

    delete this->rects;
}

void BoardUI::blit(SDL_Surface *dest, int x, int y)
{
    State s;
    Sprite *sp;

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < this->size(); j++) {
            s = this->getState(i, j);
            switch (s) {
            case NONE:
                sp = this->blank_sprite;
                break;
            case PLAYER_X:
                sp = this->x_sprite;
                break;
            case PLAYER_O:
                sp = this->o_sprite;
                break;
            }

            sp->blit(dest,
                     this->rects[i][j].x + x,
                     this->rects[i][j].y + y);
        }
    }
}

void BoardUI::handleMouseClick(int x, int y)
{
    // Compute which board cell, if any, this corresponds to.
    for (int i = 0; i < this->size(); i++)
        for (int j = 0; j < this->size(); j++)
            if (in_rect(x, y, this->rects[i][j])) {
                this->nextMove(i, j);
                return;
            }
}
