
#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Sprite.h"
#include "Param.h"

#include "SDL.h"
#include <vector>

using namespace std;

class Animation {
 public:
    Animation(int fps);
    void add_frame(Sprite *s);
    void start(int current_time_millis);
    void reset(void);

    void blit(SDL_Surface *dest, int x, int y,
              int current_time_millis);

 private:
    Sprite * current_frame(int current_time_millis);

    vector<Sprite *> frames;
    LinearParam frame_num;
    int fps;
};

#endif
