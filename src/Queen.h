
#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Board.h"
#include "Piece.h"


class Queen : public Piece {
public:
    explicit Queen(char color);
    bool isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const override;
};



#endif //CHESS_QUEEN_H
