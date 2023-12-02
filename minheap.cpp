#include <iostream>
#include "minheap.h"

/**
 * minheap()
 * Description: Default Constructor for class
 */
minheap::minheap() {
    // Set pointers to nullptr
    keys = nullptr;
    values = nullptr;

    // Set variables to default values
    capacity = 0;
    size = 0;
}

/**
 * ~Minheap()
 * Description: Deallocates memory for any class variables
 */
minheap::~minheap() {
    delete[] keys;
    delete[] values;
}

/**
 * init(int)
 * Description: Initializes the key/values arrays
 * @param value - Represents the size of the arrays to create
 */
void minheap::init(int cap) {
    capacity = cap; // Set capacity to param size
    this->size = 0; // Size of initialized arrays will be 0
    // Allocate memory for keys(weights) and values(nodes)
    keys = new double[capacity];
    values = new int[capacity];
}

/**
 * push(double, int)
 * Description: Pushes a key/value to the corresponding arrays
 * @param key - Key value to be pushed
 * @param value - Vertex ID value to be pushed
 */
void minheap::push(double key, int value) {

    // Return if heap is full
    if (size == capacity) {
        return;
    }

    // Increase size
    size++;

    // Set key/value at end of array
    keys[size-1] = key;
    values[size-1] = value;

    // Call heapify up
    heapifyUp(size-1);
}

/**
 * pop()
 * Description: Removes a value from the keys array and returns it
 * @return - Double - Returns the element popped from keys
 */
int minheap::pop() {

    // Check if the heap is empty first
    if (empty()) {
        return -1;
    }

    // Get return value
    //double returnVal = keys[0];
    double returnVal = values[0];

    // Replace root w/ last elem
    //keys[0] = keys[size-1];
    values[0] = values[size - 1];

    // Decrement size & call heapify down
    size--;
    heapifyDown(0);

    return returnVal; // Return initial root value
}

/**
 * empty()
 * Description: Checks if the minHeap is empty
 * @return - Bool - Returns a boolean if the minheap is empty or not
 */
bool minheap::empty() const {
    return size == 0;
}

/**
 * heapifyUp(int)
 * Description:
 * @param index
 */
void minheap::heapifyUp(int index) {

    //
    while (index > 0 && keys[index] < keys[index / 2]) {
        // Swap index w/ parent, then
        std::swap(keys[index], keys[(index) / 2]);
        index = index / 2;
    }
}

/**
 * heapifyDown(int)
 * Description:
 * @param index -
 */
void minheap::heapifyDown(int index) {

    //Find the smallest child from left(2*index) or right(2*index+1) child of index
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Check left child
    if (left < size && keys[left] < keys[smallest])
        smallest = left;
    // Check right child
    if (right < size && keys[right] < keys[smallest])
        smallest = right;

    // Swap values in array, then call heapifydown
    if (smallest != index) {
        std::swap(values[index], values[smallest]);
        std::swap(keys[index], keys[smallest]);
        heapifyDown(smallest);
    }
}

/**
 * swap(int, int)
 * Description: Swaps keys/values at positions i and j
 * @param i - First index to swap
 * @param j - Second index to swap
 */
void minheap::swap(int i, int j) {
    std::swap(keys[i], keys[j]);
}
