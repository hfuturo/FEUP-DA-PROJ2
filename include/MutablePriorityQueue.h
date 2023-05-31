/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef DA_PROJ2_MUTABLEPRIORITYQUEUE_H
#define DA_PROJ2_MUTABLEPRIORITYQUEUE_H

#include <vector>

/**
 * @brief Represents a mutable priority queue
 *
 * @note class T must have: (i) accessible field int queueIndex; (ii) operator< defined.
 * @note Implemented by João Pascoal Faria
 */
template <class T>
class MutablePriorityQueue {
    /** @brief Vector with elements of the priority queue */
    std::vector<T *> H;

    /**
     * @brief Used to insert or update the value the position of an element in the priority queue.
     *
     * @note Complexity time: O(log V)
     *
     * @param i The position we are going to update / insert
     */
    void heapifyUp(unsigned i);

    /**
     * @brief Removes an element from the priority queue an updates it.
     *
     * @note Complexity time: O(log V)
     *
     * @param i The element we are going to remove.
     */
    void heapifyDown(unsigned i);

    /**
     * @brief Moves an element to a position in the priority queue
     *
     * @note Complexity time: O(1)
     *
     * @param i The position
     * @param x The element
     */
    inline void set(unsigned i, T * x);
public:
    /** @brief Creates an empty mutable priority queue
     *
     * @note Complexity time: O(1)
     *
     */
    MutablePriorityQueue();

    /**
     * @brief Inserts an element into the priority queue
     *
     * @note Complexity time: O(log V)
     *
     * @param x The element
     */
    void insert(T * x);

    /**
     * @brief Removes the element with the lowest key in the priority queue
     *
     * @note Complexity time: O(log V)
     *
     * @return The element
     */
    T * extractMin();

    /**
     * @brief Updates the key of an element in the priority queue.
     *
     * @note Complexity time: O(log V)
     *
     * @param x The element
     */
    void decreaseKey(T * x);

    /**
     * @brief Sees if the priority queue is empty.
     *
     * @note Complexity time: O(1)
     *
     * @return True if empty. False otherwise.
     */
    bool empty();
};

// Index calculations

/** @brief Calculates the parent of an element */
#define parent(i) ((i) / 2)

/** @brief Calculates the left child of an element */
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif //DA_PROJ2_MUTABLEPRIORITYQUEUE_H
