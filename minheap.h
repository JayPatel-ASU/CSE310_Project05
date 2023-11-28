//
//
//

#ifndef PROJECT05_MINHEAP_H
#define PROJECT05_MINHEAP_H

#include <vector>

using namespace std;

class minheap {
private:

    vector<int> heap;

    int getParent(int i);

    int getLeftChild(int i);

    int getRightChild(int i);

public:
    minheap();
    ~minheap();


};


#endif //PROJECT05_MINHEAP_H
