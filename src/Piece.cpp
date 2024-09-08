#include "Board.h"
#include "Piece.h"

Piece::Piece(char type, char color) : type(type), color(color) {}
char Piece::getType() const { return type; }
char Piece::getColor() const { return color; }


