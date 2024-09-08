
#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "Board.h"
#include "Piece.h"
class Bishop : public Piece {
public:
    explicit Bishop(char color);
    bool isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const override;
};

#endif //CHESS_BISHOP_H
