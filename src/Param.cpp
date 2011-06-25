
#include <stdlib.h>
#include <stdio.h>
#include "Param.h"

Param::Param()
{
    this->reset();
}

void Param::start(int current_time_millis)
{
    this->start_time = current_time_millis;
}

void Param::reset(void)
{
    this->start_time = 0;
}

void LinearParam::setup(float start, float stop, float velocity)
{
    this->startVal = start;
    this->stopVal = stop;
    this->velocity = velocity;
}

float LinearParam::get(int current_time_millis)
{
    float value = this->stopVal - this->startVal;
    float total_time = (abs(value) / this->velocity) * 1000.0;
    float timefrac = ((float) current_time_millis - this->start_time) /
        total_time;

    return this->startVal + (timefrac * value);
}

void CyclicParam::invert(void)
{
    float t;

    t = this->startVal;
    this->startVal = this->stopVal;
    this->stopVal = t;

    this->start_time += ((abs(this->stopVal - this->startVal)) /
                         this->velocity) * 1000;
}

float CyclicParam::get(int current_time_millis)
{
    float val = LinearParam::get(current_time_millis);

    // If the position has past the terminal boundary, we want to
    // bounce back in the other direction.  So we invert the velocity
    // and calculate how far past the boundar the value is, then
    // return the appropriate value.
    if (this->stopVal > this->startVal && val > this->stopVal) {
        this->invert();
        return this->startVal - (val - this->startVal);
    } else if (this->stopVal < this->startVal && val < this->stopVal) {
        this->invert();
        return this->startVal + (this->stopVal - val);
    } else
        return val;
}
