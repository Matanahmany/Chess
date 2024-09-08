#ifndef BEST_MOVE_FINDER_H
#define BEST_MOVE_FINDER_H

#include "PriorityQueue.h"
#include "Move.h"
#include "Board.h"
#include <vector>
#include <string>

constexpr size_t MAX_QUEUE_SIZE = 5;
constexpr size_t PRINT_ELEMENT_SIZE = 3;
class BestMoveFinder {
public:
    explicit BestMoveFinder(Board& board,int depth);
    void findBestMoves();
    void printBestMoves(std::ostream& os) const;

private:
    int depth;
    Board& board;
    PriorityQueue<Move> pq;
    std::vector<std::string> generateAllMoves(char player);
    int evaluateMove(const std::string& move,int depth);
    int evaluateMoveWithDepth(const std::string& move, int depth, char player);
    int getPieceValue(const Piece* piece) const;

    int calculateCaptureScore(Piece* targetPiece);
    int calculateThreatScore(Piece* movingPiece, int destX, int destY);
    int evaluateThreat(const Piece* attacker, const Piece* target, int srcX, int srcY, int destX, int destY) const;
};

#endif // BEST_MOVE_FINDER_H
