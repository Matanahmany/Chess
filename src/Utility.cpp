#include "Utility.h"
#include "BestMoveFinder.h"
#include "Exceptions.h"
#include <sstream>
#include <iostream>
#include <cstdlib>


const std::string RECOMMENDED_MOVE_HEADER = "Recommended move: ";
const std::string DEPTH_PROMPT = "Enter the depth for move evaluation: ";
const std::string INVALID_INPUT_MSG = "Input is not a valid integer.";
const std::string RETRY_MSG = " Please try again.";


void calculateAndSetRecommendations(Chess& chessGame, Board& board, int depth) {
    BestMoveFinder bestMoveFinder(board, depth);
    bestMoveFinder.findBestMoves();
    std::ostringstream oss;
    oss << RECOMMENDED_MOVE_HEADER << std::endl;
    bestMoveFinder.printBestMoves(oss);
    chessGame.setRecommendations(oss.str());
}

int getDepthFromUser() {
    std::string input;
    int depth = -1;
    bool checkValidOfDepth = false;
    while (!checkValidOfDepth) {
        try {
            std::cout << DEPTH_PROMPT;
            std::getline(std::cin, input);

            // Check if the input is a valid integer
            if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit)) {
                depth = std::atoi(input.c_str());
                checkValidOfDepth = true;
            } else {
                throw InvalidInputException(INVALID_INPUT_MSG);
            }
        } catch (const InvalidInputException& e) {
            std::cerr << e.what() << RETRY_MSG << std::endl;
        }
    }
    return depth;
}
