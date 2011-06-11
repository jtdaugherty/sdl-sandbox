
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
    void show(void);

 private:
    bool rowWinner(void);
    bool colWinner(void);
    bool diagWinner(void);

    State **board;
    int sz;
};
