// Utility.h

#ifndef UTILITY_H
#define UTILITY_H

#include "Chess.h"
#include "Board.h"
#include <string>

inline bool isPromote(int code){
    return (code >= 32 && code <= 35);
}
/**
 * @brief Calculates the best moves and sets the recommendations in the chess game.
 *
 * This function uses the BestMoveFinder to calculate the best moves based on the current
 * state of the board and the given search depth. The recommendations are then set in the
 * chess game object.
 *
 * @param chessGame The Chess game object to set the recommendations in.
 * @param board The current state of the chess board.
 * @param depth The search depth for evaluating the best moves.
 */
void calculateAndSetRecommendations(Chess& chessGame, Board& board, int depth);

/**
 * @brief Prompts the user to enter the depth for move evaluation.
 *
 * This function repeatedly prompts the user to enter a valid depth for move evaluation.
 * It ensures that the input is a valid non-negative integer. If the input is invalid,
 * an exception is thrown, and the user is asked to try again.
 *
 * @return The valid depth entered by the user.
 */
int getDepthFromUser();

#endif // UTILITY_H
