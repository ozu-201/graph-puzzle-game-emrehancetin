//
// Created by Olcay Taner YILDIZ on 27.03.2023.
//

#include "Queue.h"

using namespace darts;

Queue::Queue(int N) {
    this->N = N;
    array = new Element[N];
    first = 0;
    last = 0;
}

Queue::~Queue() {
    delete[] array;
}

bool Queue::isFull() const {
    return (last + 1) % N == first;
}

bool Queue::isEmpty() const {
    return first == last;
}

void Queue::enqueue(const Element& element) {
    if (!isFull()) {
        array[last] = element;
        last = (last + 1) % N;
    }
}

Element Queue::dequeue() {
    if (!isEmpty()) {
        Element tmp = array[first];
        first = (first + 1) % N;
        return tmp;
    }
    return Element(State(0, ""));
}
