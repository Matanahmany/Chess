# Chess Game Project

## Overview

This project is a comprehensive implementation of a chess game in C++. It includes the representation of the chess board, the pieces, and the game logic, along with an algorithm to calculate the best moves. The game supports all standard chess moves including castling, pawn promotion, and en passant.

## Features

- Full chess game implementation with standard rules.
- Graphical User Interface (GUI) using ASCII art for displaying the board.
- Move validation for each type of piece.
- Special moves including castling and pawn promotion.
- Best move calculation using a custom algorithm.
- Custom exception handling for invalid inputs and promotion errors.

## Project Structure

- **src/**: Contains the source code files for the project.
- **include/**: Contains the header files.
- **README.md**: This file.
- **main.cpp**: The main entry point of the application.

## Exceptions

The project includes custom exception classes to handle specific error scenarios:

### InvalidInputException

This exception is thrown when an invalid input is encountered. It inherits from `std::runtime_error`.

```cpp
class InvalidInputException : public std::runtime_error {
public:
    explicit InvalidInputException(const std::string& message)
            : std::runtime_error(message) {}
};
PromotionException
This exception is thrown during pawn promotion when an invalid promotion type is specified. It also inherits from std::runtime_error.

cpp
Copy code
class PromotionException : public std::runtime_error {
public:
    explicit PromotionException(const std::string& message)
            : std::runtime_error(message) {}
};
```
## Best Move Calculation Algorithm
The algorithm to calculate the best moves is implemented in the BestMoveFinder class. This class uses a depth-first search approach to evaluate possible moves and determine the best move for the current player.

Steps of the Algorithm:
Generate All Possible Moves: For the current player's turn, generate all possible legal moves.
Evaluate Moves: Each move is evaluated based on several factors including piece value and board control.
Minimax with Alpha-Beta Pruning: The algorithm uses a minimax approach with alpha-beta pruning to recursively evaluate moves up to a specified depth. This helps in reducing the number of nodes that are evaluated in the search tree, making the algorithm more efficient.
Score Calculation:
Capture Score: Higher score for capturing high-value pieces.
Threat Score: Consider the threat posed to and by the pieces on the board.
Complexity
The time complexity of the best move calculation algorithm is O(b^d), where b is the average number of legal moves per position (branching factor), and d is the depth of the search. With alpha-beta pruning, the effective branching factor is reduced, leading to an average complexity of O(b^(d/2)) in the best case.

### How to Run
Compile the project using a C++ compiler (e.g., g++, clang++).
Run the executable generated.
Example (using g++):

sh
Copy code
g++ -std=c++20 -o chess_game main.cpp src/*.cpp
./chess_game
Conclusion
This project provides a fully functional chess game with a focus on move validation and best move calculation. The use of custom exceptions ensures robust error handling, while the minimax algorithm with alpha-beta pruning offers an efficient way to determine the best possible moves in the game.
