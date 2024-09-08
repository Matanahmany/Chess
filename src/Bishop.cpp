#include "Bishop.h"
Bishop::Bishop(char color) : Piece(BISHOP_TYPE, color) {}


bool Bishop::isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const {
    if (abs(destX - srcX) != abs(destY - srcY)) {
        return false;  // Move is not diagonal
    }
    auto calculateStep = [](int start, int end) {
        return (end > start) ? 1 : -1;
    };

    int stepX = calculateStep(srcX, destX);
    int stepY = calculateStep(srcY, destY);
    for (int x = srcX + stepX, y = srcY + stepY; x != destX && y != destY; x += stepX, y += stepY) {
        if (board.getPiece(x, y) != nullptr) {
            return false;  // Path is blocked by another piece
        }
    }
    // Check the destination square
    Piece* destinationPiece = board.getPiece(destX, destY);
    if (destinationPiece != nullptr && destinationPiece->getColor() == this->getColor()) {
        return false;  // Cannot capture your own piece
    }
    return true;
}
