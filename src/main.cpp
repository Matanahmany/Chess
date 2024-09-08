#include "Chess.h"
#include "Board.h"
#include "Utility.h" // Include the utility functions
#include <iostream>
int main()
{
    string boardString  = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess chessGame(boardString);
    Board& board = Board::getInstance(boardString);
    int codeResponse = 0;

    int depth = getDepthFromUser();
    calculateAndSetRecommendations(chessGame, board, depth);
    string res = chessGame.getInput();

    while (res != "exit")
    {
        codeResponse=board.movePiece(res);
        if (codeResponse == MOVE_CAUSES_CHECK_ON_OPPONENT || codeResponse == VALID_MOVE || codeResponse == CASTLING_MOVE || isPromote(codeResponse)) {
            board.changeTurn();
        }
        chessGame.setCodeResponse(codeResponse);
        calculateAndSetRecommendations(chessGame, board, depth);
        res = chessGame.getInput();
    }

    cout << endl << "Exiting " << endl;
    return 0;
}