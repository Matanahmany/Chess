#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Piece.h"
#include <iostream>
#include <string>

constexpr int BOARD_SIZE = 8;




enum MoveCodes {
    NO_PIECE_AT_SOURCE = 11,
    NOT_PLAYER_TURN = 12,
    SAME_PLAYER_PIECE_AT_DEST = 13,
    INVALID_MOVE = 21,
    MOVE_CAUSES_CHECK = 31,
    PROMOTE_TO_QUEEN = 32,
    PROMOTE_TO_ROOK = 33,
    PROMOTE_TO_BISHOP = 34,
    PROMOTE_TO_KNIGHT = 35,
    MOVE_CAUSES_CHECK_ON_OPPONENT = 41,
    VALID_MOVE = 42,
    CASTLING_MOVE = 43,
    CHECKMATE = 44
};

class Board {
private:
    Piece* boardArr[BOARD_SIZE][BOARD_SIZE];
    char isTurn = WHITE_COLOR;
    static Board* instance;

    void placePiece(char pieceChar, int row, int col);
    Board(const std::string& boardString);

public:
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    static Board& getInstance(const std::string& boardString);
    Piece* getPiece(int x, int y) const;
    int movePiece(const std::string& res);
    void changeTurn();
    char getIsTurn() const;
    bool isSafeFromCheck(int srcX, int srcY, int destX, int destY, char pieceColor);
    bool isKingInCheck(char kingColor) const;
    void makeTempMove(int srcX, int srcY, int destX, int destY);
    void revertTempMove(int srcX, int srcY, int destX, int destY, Piece* piece);
    bool checkForThreatsForKing(int kingX, int kingY, char kingColor) const;
    bool isCheckmate(char kingColor);
    bool isSquareUnderAttack(int x, int y, char color) const;
    ~Board();
};

#endif // CHESS_BOARD_H
