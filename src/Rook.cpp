#include "Rook.h"
#include "Board.h"

Rook::Rook(char color) : Piece(ROOK_TYPE, color), moved(false){}

bool Rook::isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const {
    if (srcX != destX && srcY != destY) {
        return false;
    }
    int xDirection = (destX - srcX) == 0 ? 0 : (destX - srcX) / abs(destX - srcX);
    int yDirection = (destY - srcY) == 0 ? 0 : (destY - srcY) / abs(destY - srcY);

    int x = srcX + xDirection;
    int y = srcY + yDirection;

    while (x != destX || y != destY) {
        if (board.getPiece(x, y) != nullptr) {
            return false; // Path is blocked
        }
        x += xDirection;
        y += yDirection;
    }

    Piece* destinationPiece = board.getPiece(destX, destY);
    return destinationPiece == nullptr || destinationPiece->getColor() != this->getColor();
}
void Rook::setMoved(bool hasMoved) {
    moved = hasMoved;
}

bool Rook::hasMoved() const {
    return moved;
}
