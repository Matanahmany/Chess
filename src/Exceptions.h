//
// Created by Matan on 02/07/2024.
//

#ifndef CHESS_EXCEPTIONS_H
#define CHESS_EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * @brief Exception class for invalid input errors.
 *
 * This class represents an exception that is thrown when invalid input is encountered.
 */
class InvalidInputException : public std::runtime_error {
public:
    /**
     * @brief Constructs an InvalidInputException with the specified error message.
     *
     * @param message The error message.
     */
    explicit InvalidInputException(const std::string& message)
            : std::runtime_error(message) {}
};

/**
 * @brief Exception class for promotion errors.
 *
 * This class represents an exception that is thrown when there is an error during pawn promotion.
 */
class PromotionException : public std::runtime_error {
public:
    /**
     * @brief Constructs a PromotionException with the specified error message.
     *
     * @param message The error message.
     */
    explicit PromotionException(const std::string& message)
            : std::runtime_error(message) {}
};

#endif // CHESS_EXCEPTIONS_H
