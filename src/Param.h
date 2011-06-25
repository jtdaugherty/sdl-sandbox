
#ifndef __PARAM_H__
#define __PARAM_H__

class Param {
 public:
    Param();
    void start(int current_time_millis);
    void reset(void);

    virtual float get(int current_time_millis) = 0;

 protected:
    int start_time;
};

class LinearParam : public Param {
 public:
    void setup(float start, float stop, float velocity);

    float get(int current_time_millis);
 protected:
    float startVal, stopVal, velocity;
};

class CyclicParam : public LinearParam {
 public:
    float get(int current_time_millis);
 private:
    void invert(void);
};

#endif
