
#include "Animation.h"
#include "Param.h"

#include "SDL.h"

Animation::Animation(int fps)
{
    this->fps = fps;
    this->reset();
}

void Animation::add_frame(Sprite *s)
{
    this->frames.push_back(s);
}

void Animation::start(int current_time_millis)
{
    this->frame_num.setup(0.0, this->frames.size() - 1, this->fps);
    this->frame_num.start(current_time_millis);
}

void Animation::reset(void)
{
    this->frame_num.reset();
}

Sprite * Animation::current_frame(int current_time_millis)
{
    float val = this->frame_num.get(current_time_millis);

    // for now, cycle.
    int i = ((int) val) % this->frames.size();

    return this->frames[i];
}

void Animation::blit(SDL_Surface *dest, int x, int y,
                     int current_time_millis)
{
    Sprite *s = this->current_frame(current_time_millis);

    if (s)
        s->blit(dest, x, y);
}
