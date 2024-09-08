#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <list>
#include <iterator>
#include <optional>
#include <iostream>

/**
 * @brief Comparator structure for comparing elements.
 *
 * This structure provides a comparison operator that can be used to compare two elements.
 * The default implementation compares the elements using the greater than operator.
 */
template<typename T>
struct MyComparator {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

/**
 * @brief Priority Queue implementation using a list.
 *
 * This class implements a priority queue using a doubly linked list (std::list).
 * The elements in the queue are ordered according to a comparator.
 *
 * @tparam T The type of elements in the priority queue.
 * @tparam Comparator The comparator used to order the elements.
 */
template<typename T, typename Comparator = MyComparator<T>>
class PriorityQueue {
public:
    /**
     * @brief Constructs a PriorityQueue with optional maximum and print sizes.
     *
     * @param max_size Optional maximum size of the priority queue. If specified, the queue will
     *                 not exceed this size.
     * @param print_size Optional number of elements to print. If specified, only this many elements
     *                   will be printed when calling printTopMoves.
     */
    explicit PriorityQueue(std::optional<size_t> max_size = std::nullopt, std::optional<size_t> print_size = std::nullopt);

    /**
     * @brief Pushes a value into the priority queue.
     *
     * The value is inserted into the queue in a position that maintains the order specified
     * by the comparator.
     *
     * @param value The value to be inserted into the queue.
     */
    void push(const T& value);

    /**
     * @brief Removes and returns the highest priority element from the queue.
     *
     * @return The highest priority element in the queue.
     * @throws std::out_of_range if the queue is empty.
     */
    T poll();

    /**
     * @brief Checks if the queue is empty.
     *
     * @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Prints the top moves in the queue.
     *
     * Prints the elements in the queue up to the number specified by print_size. If print_size
     * is not specified, all elements in the queue are printed.
     *
     * @param os The output stream to print the elements to.
     */
    void printTopMoves(std::ostream& os) const;

private:
    std::list<T> queue;                 ///< The list storing the elements of the queue.
    Comparator comparator;              ///< The comparator used to order the elements.
    std::optional<size_t> max_size;     ///< The maximum size of the queue.
    std::optional<size_t> print_size;   ///< The number of elements to print.
};

template<typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(std::optional<size_t> max_size, std::optional<size_t> print_size)
        : max_size(max_size), print_size(print_size) {}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& value) {
    auto it = queue.begin();
    while (it != queue.end() && !comparator(value, *it)) {
        ++it;
    }
    queue.insert(it, value);
    if (max_size && queue.size() > *max_size) {
        queue.pop_back();
    }
}

template<typename T, typename Comparator>
T PriorityQueue<T, Comparator>::poll() {
    if (queue.empty()) {
        throw std::out_of_range("Queue is empty");
    }
    T value = queue.front();
    queue.pop_front();
    return value;
}

template<typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::isEmpty() const {
    return queue.empty();
}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::printTopMoves(std::ostream& os) const {
    size_t count = 0;
    for (const auto& move : queue) {
        if (print_size && count >= *print_size) break;
        os << count + 1 << ". " << move << std::endl;
        ++count;
    }
}

#endif // PRIORITY_QUEUE_H
