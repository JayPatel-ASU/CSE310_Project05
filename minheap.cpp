//
// Created by Jay on 11/28/2023.
//

#include "minheap.h"


int minheap::getParent(int i) {
    return ((i - 1) / 2);
}

int minheap::getLeftChild(int i) {
    return (2 * i + 1);
}

int minheap::getRightChild(int i) {
    return (2 * i + 2);
}


minheap::minheap() {

}

minheap::~minheap() {

}