
#include "King.h"
#include "Board.h"
#include "Rook.h"

King::King(char color) : Piece(KING_TYPE, color), moved(false) {}

bool King::isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const {
    int deltaX = std::abs(destX - srcX);
    int deltaY = std::abs(destY - srcY);

    // Normal king move
    if (deltaX <= 1 && deltaY <= 1) {
        Piece* destPiece = board.getPiece(destX, destY);
        if (destPiece == nullptr || destPiece->getColor() != this->getColor()) {
            return true;
        }
    }

    // Castling
    if (srcY == WHITE_KING_START_COL && (destY == CASTLING_LEFT_COL || destY == CASTLING_RIGHT_COL) && srcX == destX) {
        Piece* rook = board.getPiece(srcX, destY);
        int kingDestY = (destY == CASTLING_LEFT_COL) ? CASTLING_KING_LEFT_DEST_COL : CASTLING_KING_RIGHT_DEST_COL;
        if (rook != nullptr && rook->getType() == ROOK_TYPE && !dynamic_cast<Rook*>(rook)->hasMoved() && !this->hasMoved()) {
            if (isCastlingClear(srcX, srcY, destY, board) &&
                !board.isKingInCheck(this->getColor()) &&
                !board.isSquareUnderAttack(srcX, srcY + (destY > srcY ? 1 : -1), this->getColor()) &&
                !board.isSquareUnderAttack(srcX, kingDestY, this->getColor())) {
                return true;
            }
        }
    }

    return false;
}

bool King::isCastlingClear(int srcX, int srcY, int destY, const Board& board) const {
    int direction = destY > srcY ? 1 : -1;
    for (int y = srcY + direction; y != destY; y += direction) {
        if (board.getPiece(srcX, y) != nullptr) {
            return false;
        }
    }
    return true;
}

void King::setMoved(bool hasMoved) {
    moved = hasMoved;
}

bool King::hasMoved() const {
    return moved;
}