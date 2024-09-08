
#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "Board.h"
#include "Piece.h"

class Rook : public Piece {
private:
    bool moved;
public:
    explicit Rook(char color);
    bool isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const override;
    void setMoved(bool hasMoved);
    bool hasMoved() const;
};


#endif //CHESS_ROOK_H