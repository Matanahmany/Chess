
#include "Queen.h"
Queen::Queen(char color) : Piece(QUEEN_TYPE, color) {}

bool Queen::isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const {
    // Check if the move is a straight line or a diagonal move
    if (srcX != destX && srcY != destY && abs(destX - srcX) != abs(destY - srcY)) {
        return false;
    }
    int stepX = (destX > srcX) ? 1 : (destX < srcX) ? -1 : 0;
    int stepY = (destY > srcY) ? 1 : (destY < srcY) ? -1 : 0;

    int x = srcX + stepX;
    int y = srcY + stepY;

    // Check each square along the way for other pieces
    while (x != destX || y != destY) {
        if (board.getPiece(x, y) != nullptr) {
            return false;  // Path is blocked
        }
        x += stepX;
        y += stepY;
    }
    // Check the destination square
    Piece* destinationPiece = board.getPiece(destX, destY);
    if (destinationPiece != nullptr && destinationPiece->getColor() == this->getColor()) {
        return false;  // Cannot capture your own piece
    }
    return true;
}