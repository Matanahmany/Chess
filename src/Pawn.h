
#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "Board.h"
#include "Piece.h"


class Pawn : public Piece {
public:
    explicit Pawn(char color);
    bool isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const override;
    Piece* promote(char promotionType) const override;

};


#endif //CHESS_PAWN_H
