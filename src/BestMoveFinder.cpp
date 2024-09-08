#include "BestMoveFinder.h"
#include <iostream>
#include <climits>

BestMoveFinder::BestMoveFinder(Board& board, int depth)
        : board(board), depth(depth), pq(MAX_QUEUE_SIZE, PRINT_ELEMENT_SIZE) {}

// Generates all possible moves for the given player
std::vector<std::string> BestMoveFinder::generateAllMoves(char player) {
    std::vector<std::string> moves;
    for (int srcX = 0; srcX < BOARD_SIZE; ++srcX) {
        for (int srcY = 0; srcY < BOARD_SIZE; ++srcY) {
            Piece* piece = board.getPiece(srcX, srcY);
            if (piece && piece->getColor() == player) {
                for (int destX = 0; destX < BOARD_SIZE; ++destX) {
                    for (int destY = 0; destY < BOARD_SIZE; ++destY) {
                        if (piece->isValidMove(srcX, srcY, destX, destY, board)) {
                            moves.push_back({static_cast<char>('a' + srcX), static_cast<char>('1' + srcY), static_cast<char>('a' + destX), static_cast<char>('1' + destY)});
                        }
                    }
                }
            }
        }
    }
    return moves;
}

// Evaluates a move at the given depth
int BestMoveFinder::evaluateMove(const std::string& move, int depth) {
    return evaluateMoveWithDepth(move, depth, board.getIsTurn());
}

// Evaluates a move with depth and player consideration
int BestMoveFinder::evaluateMoveWithDepth(const std::string& move, int depth, char player) {
    int srcX = move[0] - 'a';
    int srcY = move[1] - '1';
    int destX = move[2] - 'a';
    int destY = move[3] - '1';

    Piece* movingPiece = board.getPiece(srcX, srcY);
    Piece* targetPiece = board.getPiece(destX, destY);

    // Calculate score for capturing a piece
    int score = calculateCaptureScore(targetPiece);
    score += calculateThreatScore(movingPiece, destX, destY);
    score -= calculateThreatScore(movingPiece, srcX, srcY);

    // Evaluate opponent's response
    if (depth > 0) {
        std::vector<std::string> opponentMoves = generateAllMoves(player == WHITE_COLOR ? BLACK_COLOR : WHITE_COLOR);
        int bestOpponentScore = INT_MIN;
        for (const auto& opponentMove : opponentMoves) {
            int opponentScore = evaluateMoveWithDepth(opponentMove, depth - 1, player == WHITE_COLOR ? BLACK_COLOR : WHITE_COLOR);
            if (opponentScore > bestOpponentScore) {
                bestOpponentScore = opponentScore;
            }
        }
        score -= bestOpponentScore;
    }

    // Evaluate player's further response
    if (depth > 1) {
        std::vector<std::string> playerMoves = generateAllMoves(player);
        int bestPlayerScore = INT_MIN;
        for (const auto& playerMove : playerMoves) {
            int playerScore = evaluateMoveWithDepth(playerMove, depth - 2, player);
            if (playerScore > bestPlayerScore) {
                bestPlayerScore = playerScore;
            }
        }
        score += bestPlayerScore;
    }

    return score;
}

// Returns the value of a piece
int BestMoveFinder::getPieceValue(const Piece* piece) const {
    switch (piece->getType()) {
        case PAWN_TYPE: return 1;
        case KNIGHT_TYPE: return 3;
        case BISHOP_TYPE: return 3;
        case ROOK_TYPE: return 5;
        case QUEEN_TYPE: return 9;
        case KING_TYPE: return 1000;
        default: return 0;
    }
}

// Calculates score for capturing a piece
int BestMoveFinder::calculateCaptureScore(Piece* targetPiece) {
    if (targetPiece) {
        return getPieceValue(targetPiece);
    }
    return 0;
}

// Evaluates threat from one piece to another
int BestMoveFinder::evaluateThreat(const Piece* attacker, const Piece* target, int srcX, int srcY, int destX, int destY) const {
    if (attacker->isValidMove(srcX, srcY, destX, destY, board)) {
        int attackerValue = getPieceValue(attacker);
        int targetValue = getPieceValue(target);
        return targetValue - attackerValue;
    }
    return 0;
}

// Calculates threat score for a piece at a given position
int BestMoveFinder::calculateThreatScore(Piece* movingPiece, int x, int y) {
    int score = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Piece* opponentPiece = board.getPiece(i, j);
            if (opponentPiece && opponentPiece->getColor() != movingPiece->getColor()) {
                score += evaluateThreat(opponentPiece, movingPiece, i, j, x, y);
                score += evaluateThreat(movingPiece, opponentPiece, x, y, i, j);
            }
        }
    }
    return score;
}

// Finds the best moves based on evaluation
void BestMoveFinder::findBestMoves() {
    std::vector<std::string> allMoves = generateAllMoves(board.getIsTurn());
    for (const auto& move : allMoves) {
        int score = evaluateMove(move, depth);
        pq.push(Move(move, score));
    }
}

// Prints the best moves
void BestMoveFinder::printBestMoves(std::ostream& os) const {
    pq.printTopMoves(os);
}
