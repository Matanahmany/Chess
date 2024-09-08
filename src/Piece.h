#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <string>
#include "Board.h"
using namespace std;

#define KING_TYPE 'K'
#define QUEEN_TYPE 'Q'
#define ROOK_TYPE 'R'
#define BISHOP_TYPE 'B'
#define KNIGHT_TYPE 'N'
#define PAWN_TYPE 'P'
#define WHITE_COLOR 'W'
#define BLACK_COLOR 'B'
#define EMPTY '#'

class Board;
class Piece {
public:
    Piece(char type, char color);
    virtual ~Piece() = default;
    virtual bool isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const = 0;
    virtual Piece* promote(char promotionType) const { return nullptr; }
    char getType() const;
    char getColor() const;
protected:
    char type;
    char color;
};


#endif //CHESS_PIECE_H
