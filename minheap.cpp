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
    int capacity = 0;
    int size = 0;
}

/**
 *
 * @param size
 */
void minheap::init(int size) {
    //set capacity and size
    //allocate memory for keys(weights) and values(nodes)
}

/**
 *
 * @param key
 * @param value
 */
void minheap::push(double key, int value) {
    /*
    if heap is full
        return

    increase size
    set key and value at the end with index as size
    heapify up
    */
}

/**
 *
 * @return
 */
int minheap::pop() {
    /*
    if heap is empty
        return sentinel value

    get root value
    replace root with the last element
    decrease size
    heapify down

    return root value
    */
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
 *
 * @param index
 */
void minheap::heapifyUp(int index) {
    /*
    while index > 1 and current key is less than parent key (parent key is index / 2)
        swap index with parent
        update index to parent
    */
}

/**
 *
 * @param index
 */
void minheap::heapifyDown(int index) {
    /*
    find the smallest child from left(2*index) or right(2*index+1) child of index
    if smallest child is smaller than current key
        swap with smallest child with index
        update index
        heapify down
    */
}

/**
 *
 * @param i
 * @param j
 */
void minheap::swap(int i, int j) {
    //swap keys and values at positions i and j
}