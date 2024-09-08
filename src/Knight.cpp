
#include "Knight.h"
Knight::Knight(char color) : Piece(KNIGHT_TYPE, color) {}
bool Knight::isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const {
    int dx = abs(destX - srcX);
    int dy = abs(destY - srcY);
    // Check if the move is an L-shape: 2 by 1 or 1 by 2
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
        return false;  // Not a valid knight move
    }
    // Check the destination square
    Piece* destinationPiece = board.getPiece(destX, destY);
    if (destinationPiece != nullptr && destinationPiece->getColor() == this->getColor()) {
        return false;  // Cannot capture your own piece
    }
    return true;
}