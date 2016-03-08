#include "player.h"
#include <vector>
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
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
    testingMinimax = false;
    //cerr << "Initializing board" << endl;
    
    board = Board();
    
    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
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
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    
    /** Rough Outline:
     * Accept opponent's move
     * Update board
     * 
     * int minscore;
     * int tempscore;
     * vector<Move> moveList;
     * vector<int> moveScores;
     * vector<Move> opponentMoveList;
     * 
     * // Get list of all possible player moves:
     * if board has legal moves:
     *     moveList = all possible moves based on updated board
     *                (for each square, check if legal move)
     * 
     * // Iterate through moves and init minimum score for each player move
     * tempboard = board.copy
     * for each move in moveList:
     *     change tempboard based on move
     *     if tempboard has legal moves:
     *         minscore = 100 // initialize score of this player move to 100
     *         opponentMoveList = all possible moves based on updated board
     *         for each move in opponentMoveList:
     *             tempscore = calculated score
     *             if tempscore < minscore // if less than current score of this player move
     *                 minscore = tempscore;
     *             }
     *         }
     *         moveScores.push_back(minscore)
     *         // thus assigns a score to each player move that is the lowest
     *         // score of all possible subsequent opponent moves
     *     }
     * }
     * 
     * // Find which move had the highest minScore
     * minimaxScore = moveScores[0];
     * minimaxScoreIndex = 0;
     * iterate through rest of moveScores
     *    if score > minimaxScore:
     *       minimaxScore = score;
     *       minimaxScoreIndex = i; // i being current index in moveScores
     * 
     * return moveList[i] // Returns player move that had highest minScore
     * 
     */
    
    
    /** TODO: Accept opponentsMove and update board */
    
    board.doMove(opponentsMove, their_side);
    // Calculate opponent's score
    // score = # our tiles - # their tiles
    int score = board.count(our_side) - board.count(their_side);
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

/**    vector<Move> moveList;
    vector<int> moveScores;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * m = new Move(i, j);
            if (board.checkMove(m, our_side))
            {
                cerr << "Move found: " << m->x << ", " << m->y << endl;
                Board * testBoard = board.copy();
                testBoard->doMove(m, our_side);
                moveList.push_back(*m);
                moveScores.push_back(testBoard->count(our_side) - testBoard->count(their_side));
                delete testBoard;
            }
        }
    }
    int maxScoreIndex = 0;
    for (unsigned int i = 1; i  < moveList.size(); i++)
    {
        if (moveScores[i] > moveScores[maxScoreIndex])
        {
            maxScoreIndex = i;
        }
    }
    Move * best_move = &moveList[maxScoreIndex];
    cerr << "Best move found: (" << best_move->x << ", " << best_move->y << "), with score = " << moveScores[maxScoreIndex] << endl;
    board.doMove(best_move, our_side);
    return best_move;
    **/
    // ^^^ this was a really inefficient attempt at version 2 ^^^
    
    
    // Version 2: Find all valid moves, compare those scores
    if (!board.hasMoves(our_side))
    {
        return NULL;
    }
    
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
                int newScore = testBoard->count(our_side) - testBoard->count(their_side);
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
                if (best_move == NULL || newScore > maxScore)
                {
                    best_move = m;
                    maxScore = newScore;
                    //cerr << "This is a better move, new max score = " << maxScore << endl;
                }
            }
        }
    }    
    board.doMove(best_move, our_side);
    return best_move;
}
