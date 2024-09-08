#include "Board.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
#include "Exceptions.h"
#include <iostream>



// Move codes and Promotion constants are already defined in the header

Board* Board::instance = nullptr;

void Board::placePiece(char pieceChar, int row, int col) {
    char color = (std::isupper(pieceChar)) ? WHITE_COLOR : BLACK_COLOR;
    pieceChar = std::toupper(pieceChar);

    switch (pieceChar) {
        case ROOK_TYPE: boardArr[row][col] = new Rook(color); break;
        case KNIGHT_TYPE: boardArr[row][col] = new Knight(color); break;
        case BISHOP_TYPE: boardArr[row][col] = new Bishop(color); break;
        case KING_TYPE: boardArr[row][col] = new King(color); break;
        case QUEEN_TYPE: boardArr[row][col] = new Queen(color); break;
        case PAWN_TYPE: boardArr[row][col] = new Pawn(color); break;
        case EMPTY: boardArr[row][col] = nullptr; break;
        default: throw std::invalid_argument("Invalid piece character");
    }
}

Board::Board(const std::string &boardString) {
    if (boardString.size() != BOARD_SIZE * BOARD_SIZE) {
        throw std::invalid_argument("Invalid board string length");
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            boardArr[i][j] = nullptr;
        }
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            placePiece(boardString[i * BOARD_SIZE + j], i, j);
        }
    }
}

void Board::changeTurn() {
    isTurn = (isTurn == WHITE_COLOR) ? BLACK_COLOR : WHITE_COLOR;
}

char Board::getIsTurn() const {
    return isTurn;
}

Piece* Board::getPiece(int x, int y) const {
    return boardArr[x][y];
}

int Board::movePiece(const std::string& res) {
    int srcX = res[0] - 'a';
    int srcY = res[1] - '1';
    int destX = res[2] - 'a';
    int destY = res[3] - '1';
    Piece* sourcePiece = getPiece(srcX, srcY);
    if (!sourcePiece) {
        return NO_PIECE_AT_SOURCE;
    }
    if (sourcePiece->getColor() != isTurn) {
        return NOT_PLAYER_TURN;
    }
    if (getPiece(destX, destY) && sourcePiece->getColor() == getPiece(destX, destY)->getColor() && !(sourcePiece->getType() == 'K' && getPiece(destX, destY)->getType() == 'R')) {
        return SAME_PLAYER_PIECE_AT_DEST;
    }
    if (!sourcePiece->isValidMove(srcX, srcY, destX, destY, *this)) {
        return INVALID_MOVE;
    }

    if (isSafeFromCheck(srcX, srcY, destX, destY, getIsTurn())) {
        return MOVE_CAUSES_CHECK;
    }

    // Handle castling
    if (sourcePiece->getType() == 'K' && srcY == 4 && (destY == 0 || destY == 7)) {
        int rookSrcY = destY;
        int rookDestY = (destY == 0) ? 3 : 5;
        int kingDestY = (destY == 0) ? 2 : 6;

        // Move the king
        boardArr[srcX][kingDestY] = boardArr[srcX][srcY];
        boardArr[srcX][srcY] = nullptr;

        // Move the rook
        boardArr[srcX][rookDestY] = boardArr[srcX][rookSrcY];
        boardArr[srcX][rookSrcY] = nullptr;

        dynamic_cast<King*>(sourcePiece)->setMoved(true);
        dynamic_cast<Rook*>(boardArr[srcX][rookDestY])->setMoved(true);

        return CASTLING_MOVE;
    }

    // Handle promotion
    if (sourcePiece->getType() == 'P' && (destX == 0 || destX == 7)) {
        char promotionType;
        bool validPromotion = false;
        while (!validPromotion) {
            try {
                std::cout << "Promote pawn to (Q, R, B, N): ";
                std::cin >> promotionType;
                if (promotionType != 'Q' && promotionType != 'R' && promotionType != 'B' && promotionType != 'N') {
                    throw PromotionException("Invalid promotion type.");
                }
                Piece* promotedPiece = dynamic_cast<Pawn*>(sourcePiece)->promote(promotionType);
                boardArr[destX][destY] = promotedPiece;
                boardArr[srcX][srcY] = nullptr;
                validPromotion = true;

                switch (promotionType) {
                    case QUEEN_TYPE: return PROMOTE_TO_QUEEN;
                    case ROOK_TYPE: return PROMOTE_TO_ROOK;
                    case BISHOP_TYPE: return PROMOTE_TO_BISHOP;
                    case KNIGHT_TYPE: return PROMOTE_TO_KNIGHT;
                }
            } catch (const PromotionException& e) {
                std::cerr << e.what() << " Please try again." << std::endl;
            }
        }
    } else {
        boardArr[destX][destY] = boardArr[srcX][srcY];
        boardArr[srcX][srcY] = nullptr;
    }

    // Update the moved flag for King or Rook
    if (sourcePiece->getType() == 'K' || sourcePiece->getType() == 'k') {
        dynamic_cast<King*>(sourcePiece)->setMoved(true);
    } else if (sourcePiece->getType() == 'R' || sourcePiece->getType() == 'r') {
        dynamic_cast<Rook*>(sourcePiece)->setMoved(true);
    }

    char opponentColor = (getIsTurn() == WHITE_COLOR) ? BLACK_COLOR : WHITE_COLOR;
    if (isKingInCheck(opponentColor)) {
        if (isCheckmate(opponentColor)) {
            return CHECKMATE;
        }
        return MOVE_CAUSES_CHECK_ON_OPPONENT;
    }
    return VALID_MOVE;
}

bool Board::isSafeFromCheck(int srcX, int srcY, int destX, int destY, char pieceColor) {
    // Store the piece at the destination to revert later
    Piece* temp = boardArr[destX][destY];

    if (boardArr[srcX][srcY]->getType() == 'K' && srcY == 4 && (destY == 0 || destY == 7)) {
        int kingDestY = (destY == 7) ? 6 : 2;
        int direction = (destY == 7) ? 1 : -1;

        for (int y = srcY + direction; y != kingDestY + direction; y += direction) {
            makeTempMove(srcX, srcY, srcX, y);
            bool inCheck = isKingInCheck(pieceColor);
            revertTempMove(srcX, srcY, srcX, y, temp);
            if (inCheck) {
                return true;
            }
        }
        makeTempMove(srcX, srcY, srcX, kingDestY);
        bool inCheck = isKingInCheck(pieceColor);
        revertTempMove(srcX, srcY, srcX, kingDestY, temp);
        return inCheck;
    }

    // Simulate the move
    makeTempMove(srcX, srcY, destX, destY);
    // Check if the king of the same color is in check
    bool inCheck = isKingInCheck(pieceColor);
    // Revert the move
    revertTempMove(srcX, srcY, destX, destY, temp);

    return inCheck;
}

void Board::makeTempMove(int srcX, int srcY, int destX, int destY) {
    boardArr[destX][destY] = boardArr[srcX][srcY];
    boardArr[srcX][srcY] = nullptr;  // Null pointer represents an empty square
}

void Board::revertTempMove(int srcX, int srcY, int destX, int destY, Piece* piece) {
    boardArr[srcX][srcY] = boardArr[destX][destY];
    boardArr[destX][destY] = piece;
}

bool Board::isKingInCheck(char kingColor) const {
    // This function needs to determine if the king of the given color is in check
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            Piece* piece = boardArr[x][y];
            if (piece && piece->getType() == 'K' && piece->getColor() == kingColor) {
                // Check if any opposing piece can attack this king's position
                return checkForThreatsForKing(x, y, kingColor);
            }
        }
    }
    return false;  // If no king found or no threats detected
}

bool Board::checkForThreatsForKing(int kingX, int kingY, char kingColor) const {
    // This method should implement actual checks for pawns, knights, bishops, rooks, queens, and kings
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (boardArr[i][j] && boardArr[i][j]->getColor() != kingColor) {
                if (boardArr[i][j]->isValidMove(i, j, kingX, kingY, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

Board::~Board() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            delete boardArr[i][j];
        }
    }
}

Board& Board::getInstance(const std::string& boardString) {
    if (!instance) {
        instance = new Board(boardString);
    }
    return *instance;
}

bool Board::isCheckmate(char kingColor) {
    for (int srcX = 0; srcX < BOARD_SIZE; ++srcX) {
        for (int srcY = 0;srcY < BOARD_SIZE; ++srcY) {
            Piece* piece = boardArr[srcX][srcY];
            if (piece && piece->getColor() == kingColor) {
                for (int destX = 0; destX < BOARD_SIZE; ++destX) {
                    for (int destY = 0; destY < BOARD_SIZE; ++destY) {
                        if (piece->isValidMove(srcX, srcY, destX, destY, *this)) {
                            Piece* temp = boardArr[destX][destY];
                            makeTempMove(srcX, srcY, destX, destY);
                            bool kingInCheckStatus = isKingInCheck(kingColor);
                            revertTempMove(srcX, srcY, destX, destY, temp);
                            if (!kingInCheckStatus) {
                                return false; // If any move is possible that doesn't result in check
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // No valid moves left, checkmate
}

bool Board::isSquareUnderAttack(int x, int y, char color) const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0;j < BOARD_SIZE; ++j) {
            Piece* piece = boardArr[i][j];
            if (piece && piece->getColor() != color && piece->isValidMove(i, j, x, y, *this)) {
                return true;
            }
        }
    }
    return false;
}
