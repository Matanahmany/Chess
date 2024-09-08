#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Exceptions.h"
#include <cmath> // For abs

// Define macros for initial and double move rows
#define WHITE_INITIAL_ROW 1
#define WHITE_DOUBLE_MOVE_ROW 3
#define BLACK_INITIAL_ROW 6
#define BLACK_DOUBLE_MOVE_ROW 4

Pawn::Pawn(char color) : Piece(PAWN_TYPE, color) {}

bool Pawn::isValidMove(int srcX, int srcY, int destX, int destY, const Board& board) const {
    int direction = (getColor() == WHITE_COLOR) ? 1 : -1; // Direction of movement based on piece color
    int initialRow = (getColor() == WHITE_COLOR) ? WHITE_INITIAL_ROW : BLACK_INITIAL_ROW; // Initial row based on color
    int doubleMoveRow = (getColor() == WHITE_COLOR) ? WHITE_DOUBLE_MOVE_ROW : BLACK_DOUBLE_MOVE_ROW; // Double move row

    // Normal forward movement
    if (srcY == destY) { // Moving in the same column
        if (destX == srcX + direction && board.getPiece(destX, destY) == nullptr) {
            return true; // Move forward one square to an empty square
        }
        if (srcX == initialRow && destX == doubleMoveRow &&
            board.getPiece(srcX + direction, destY) == nullptr && board.getPiece(doubleMoveRow, destY) == nullptr) {
            return true; // Move two squares forward from the initial position
        }
    }

    // Capturing diagonally
    if (std::abs(srcY - destY) == 1 && destX == srcX + direction) {
        Piece* targetPiece = board.getPiece(destX, destY);
        if (targetPiece != nullptr && targetPiece->getColor() != this->getColor()) {
            return true; // Capture opponent's piece diagonally
        }
    }

    return false; // Invalid move
}

Piece* Pawn::promote(char promotionType) const {
    switch (promotionType) {
        case QUEEN_TYPE: return new Queen(color);
        case ROOK_TYPE: return new Rook(color);
        case BISHOP_TYPE: return new Bishop(color);
        case KNIGHT_TYPE: return new Knight(color);
        default: throw PromotionException("Invalid promotion type.");
    }
}
