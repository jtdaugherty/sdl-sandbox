
#include "SDL.h"
#include "Board.h"
#include "Sprite.h"

class BoardUI : public Board {
 public:
    BoardUI(int sz);
    ~BoardUI();
    void blit(SDL_Surface *dest, int x, int y);
    void handleMouseClick(int x, int y);
    void reset(void);
 private:
    SDL_Surface *x, *o, *blank;
    Sprite *x_sprite, *o_sprite, *blank_sprite;
    SDL_Rect **rects;
    State cur_state;
};
