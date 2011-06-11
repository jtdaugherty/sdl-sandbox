
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

    void nextMove(int x, int y, State s);
    bool hasWinner(void);
    bool hasMovesLeft(void);
    void show(void);
    int size(void);
    State getState(int x, int y);
    void reset(void);

 private:
    bool rowWinner(void);
    bool colWinner(void);
    bool diagWinner(void);

    State **board;
    int sz;
};

#endif
