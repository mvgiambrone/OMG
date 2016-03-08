#include "player.h"
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    our_side = side;
    //cerr << "Our side is: " << our_side << endl;
    if (our_side == WHITE)
    {
        their_side = BLACK;
    }
    else
    {
        their_side = WHITE;
    }
    
    //cerr << "Initializing board" << endl;
    
    board = Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    board.doMove(opponentsMove, their_side);
    // Calculate opponent's score
    // score = # our tiles - # their tiles
    //int score = board.count(our_side) - board.count(their_side);
   // cerr << "Score of current board" << score << endl;

/**
	// Version 1: Find first valid move and return that
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * m = new Move(i, j);
            if (board.checkMove(m, our_side))
            {
                cerr << "First move found = (" << i << ", " << j << ")" << endl;
                board.doMove(m, our_side);
                return m;
            }
            delete m;
        }
    }
   **/
    /**
    // Version 2: Find all valid moves, compare those scores
    // If no valid moves, pass
    if (!board.hasMoves(our_side))
    {
        return NULL;
    }
    // Keep track of the best move
    int maxScore = score;
    Move * best_move = NULL;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * m = new Move(i, j);
            if (board.checkMove(m, our_side))
            {
                //cerr << "Move found: " << m->x << ", " << m->y << endl;
                Board * testBoard = board.copy();
                testBoard->doMove(m, our_side);
                int newScore = getScore(testBoard, our_side, their_side, i, j);
               
                if (best_move == NULL || newScore > maxScore)
                {
					delete best_move;
                    best_move = m;
                    maxScore = newScore;
                    //cerr << "This is a better move, new max score = " << maxScore << endl;
                }
            }
            else
            {
				delete m;
			}
        }
    }    
    board.doMove(best_move, our_side);
    return best_move;
    **/
    // Version 3: Minimax
    int minScore;
    int tempScore;
    int minimaxScoreIndex;
    vector<Move *> moveList;
    vector<int> moveScores;
    vector<Move *> opponentMoveList;

    /** Return NULL if no valid moves on our side */
    if (!board.hasMoves(our_side)) {
        return NULL;
    }

    /** Populate moveList with all valid moves we can make */
    moveList = findMoves(&board, our_side);
    
    /** Populate moveScores with minimum score for each player move */
    for (unsigned i=0; i < moveList.size(); i++) {
        Board * tempBoard = board.copy();
        tempBoard->doMove(moveList[i], our_side);
        minScore = 100;
        if (tempBoard->hasMoves(their_side)) {
            opponentMoveList = findMoves(tempBoard, their_side);
            /** Go through possible subsequent opponent moves and get minimum score */
            for (unsigned j=0; j < opponentMoveList.size(); j++) {
				tempScore = getScore(tempBoard, their_side, our_side, opponentMoveList[j]->x, opponentMoveList[j]->y);
                /** Update minimum score for this particular player move if less than
                    previously calculated minScore for the move */
                if (tempScore < minScore) {
                    minScore = tempScore;
                }
            }
            /** Free opponentMoveList */
            deleteMoves(opponentMoveList);
        }
        /** Add minimum score of this player move to moveScores */
        moveScores.push_back(minScore);
        
        delete tempBoard;
    }
    
    /** Maximize minimum score */
    minimaxScoreIndex = 0;
    for (unsigned k=1; k < moveScores.size(); k++) {
        if (moveScores[k] > moveScores[minimaxScoreIndex]) {
            minimaxScoreIndex = k;
        }
    }
    
    /** Make copy of the best move so that we can free moveList */
    Move * best_move = new Move(moveList[minimaxScoreIndex]->x, moveList[minimaxScoreIndex]->y);
    deleteMoves(moveList);
    
    board.doMove(best_move, our_side);
    return best_move;
}

void Player::deleteMoves(vector<Move *> moves)
{
	for (unsigned int i = 0; i < moves.size(); i++)
	{
		delete moves[i];
	}
}

int Player::getScore(Board * b, Side us, Side them, int i, int j)
{
	/** Calculate baseline score **/
	int newScore = b->count(us) - b->count(them);
	/** Adjust for edge and corner tiles **/
	if ((i == 0 && j == 0) || (i == 7 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 7))
	{
		newScore *= 5;
	}
	else if ((i == 1 && j == 1) || (i == 1 && j == 6) || (i == 6 && j == 1) || (i == 6 && j == 6))
	{
		newScore *= -3;
	}
	else if (((i == 0 || i == 7) && (j == 1 || j == 6)) || ((j == 0 || j == 7) && (i == 1 || i == 6)))
	{
		newScore *= 3;
	}
	else if ((i == 1 || i == 6) && (j == 1 || j == 6))
	{
		newScore *= -5;
	}
	return newScore;
}

vector<Move *> Player::findMoves(Board * aboard, Side side)
{
    vector<Move *> moveList;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * m = new Move(i, j);
            if (aboard->checkMove(m, side))
            {
                moveList.push_back(m);
            }
            else {
                delete m;
            }
        }
    }
    return moveList;
}

void Player::setBoard(char data[])
{
	board.setBoard(data);
}
