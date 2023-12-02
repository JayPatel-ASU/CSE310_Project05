#ifndef MINHEAP_H
#define MINHEAP_H

class minheap {
private:
    /** Instance Variables **/
    double* keys; // Array to store weights of edges
    int* values;  // Array to store vertice Ids
    int capacity; // Maximum size of the heap
    int size;     // Current number of elements in the heap

    /** Private Methods **/
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);

public:

    /** Default Constructor **/
    minheap();
    ~minheap();

    /** Public Methods **/
    void init(int cap);  // Initialize the min-heap with a given size
    void push(double key, int value);
    int pop();
    bool empty() const;
    void print();
};

#endif
