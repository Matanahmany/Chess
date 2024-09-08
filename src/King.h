
#ifndef CHESS_KING_H
#define CHESS_KING_H
#include "Board.h"
#include "Piece.h"

#define WHITE_KING_START_COL 4
#define CASTLING_LEFT_COL 0
#define CASTLING_RIGHT_COL 7
#define CASTLING_KING_LEFT_DEST_COL 2
#define CASTLING_KING_RIGHT_DEST_COL 6

class King : public Piece {
private:
    bool moved;
    bool isCastlingClear(int srcX, int srcY, int destY, const Board& board) const;
public:
    explicit King(char color);
    bool isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const override;
    void setMoved(bool hasMoved);
    bool hasMoved() const;
};



#endif //CHESS_KING_H