
#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Board.h"
#include "Piece.h"


class Knight : public Piece {
public:
    explicit Knight(char color);
    bool isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const override;
};

#endif //CHESS_KNIGHT_H
