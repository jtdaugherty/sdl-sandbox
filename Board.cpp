
#include <stdio.h>
#include "Board.h"

Board::Board(int sz) :
    sz(sz)
{
    this->board = new State*[this->sz];
    for (int i = 0; i < this->sz; i++) {
        this->board[i] = new State[this->sz];
        for (int j = 0; j < this->sz; j++)
            this->board[i][j] = NONE;
    }
}

Board::~Board()
{
    for (int i = 0; i < this->sz; i++)
        delete this->board[i];
    delete this->board;
}

void Board::nextMove(int x, int y, State s)
{
    if (x < 0 || y < 0 ||
        x >= this->sz || y >= this->sz)
        // XXX blow up here, this would be a bug
        return;

    if (this->board[x][y] == NONE)
        this->board[x][y] = s;
    else
        // XXX blow up here, this would also be a bug
        return;
}

bool Board::hasWinner(void)
{
    return this->rowWinner() || this->colWinner() || this->diagWinner();
}

bool Board::rowWinner(void)
{
    for (int row = 0; row < this->sz; row++) {
        bool win = true;
        State s = this->board[0][row];

        for (int col = 0; col < this->sz; col++) {
            if (this->board[col][row] != s) {
                win = false;
                break;
            }
        }
        if (win && s != NONE) return true;
    }

    return false;
}

bool Board::colWinner(void)
{
    for (int col = 0; col < this->sz; col++) {
        bool win = true;
        State s = this->board[col][0];

        for (int row = 0; row < this->sz; row++) {
            if (this->board[col][row] != s) {
                win = false;
                break;
            }
        }
        if (win && s != NONE) return true;
    }

    return false;
}

bool Board::diagWinner(void)
{
    State s;
    bool win = true;
    int i;

    s = this->board[0][0];
    for (i = 0; i < this->sz; i++) {
        if (this->board[i][i] != s) {
            win = false;
            break;
        }
    }

    if (win && s != NONE) return true;
    win = true;

    s = this->board[0][this->sz - 1];
    for (i = 0; i < this->sz; i++) {
        if (this->board[i][this->sz - i - 1] != s) {
            win = false;
            break;
        }
    }

    return (win && s != NONE);
}

void Board::show(void)
{
    for (int i = 0; i < this->sz; i++) {
        for (int j = 0; j < this->sz; j++) {
            switch(this->board[i][j]) {
            case NONE:
                printf("-");
                break;
            case PLAYER_X:
                printf("X");
                break;
            case PLAYER_O:
                printf("O");
                break;
            }
            printf(" ");
        }
        printf("\n");
    }
}
