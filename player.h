#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>

using namespace std;

class Player {

private:
	Board board;
	Side our_side;
	Side their_side;

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    void deleteMoves(vector<Move *> moves);
    int getScore(Board * b, Side us, Side them, Move * m);
    int pvs(Board * board, int depth, int alpha, int beta, Side color);
    Side opposite(Side s);
    vector<Move *> findMoves(Board *aboard, Side side);
    void setBoard(char data[]);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
