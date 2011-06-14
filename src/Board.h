
#ifndef __BOARD_H__
#define __BOARD_H__

enum State {
    NONE,
    PLAYER_X,
    PLAYER_O
};

class Board {
 public:
    Board(int sz);
    ~Board();

    void nextMove(int x, int y);
    bool hasWinner(void);
    bool hasMovesLeft(void);
    void show(void);
    int size(void);
    State getState(int x, int y);
    void reset(void);
    State getCurrentState(void);

 private:
    bool rowWinner(void);
    bool colWinner(void);
    bool diagWinner(void);

    State cur_state;
    State **board;
    int sz;
};

#endif
