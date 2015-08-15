//
// Created by julian on 8/15/15.
//

#include "Median.h"

/*
 * TODO: preguntar sobre Vector y costo amortizado. La idea es que si no podemos pasar un parametro y hacer un alloc del vector antes.
 */
Median::Median() {

}

std::list<int> Median::insert(const std::list<int> &elements) {
    std::list<int> output;

    for (auto &x : elements) {
        this->insertSingle(x);
        output.push_back(this->get());
    }

    return output;
}

int Median::get() {
    ASSERT(left.size() > 0);

    if (left.size() == right.size()) {
        return (left.top() + right.top())/2;
    } else {
        return left.top();
    }
}

void Median::insertSingle(int x) {
    if (left.size() == 0) {
        left.push(x);
    } else if (right.size() == 0) {
        if (left.top() < x) {
            right.push(left.top());
            left.pop();
            left.push(x);
        } else {
            right.push(x);
        }
    } else if (left.size() == right.size()) {
        if (x > right.top()) {
            left.push(right.top());
            right.pop();
            right.push(x);
        } else {
            left.push(x);
        }
    } else {
        // El lado izquierdo tiene 1 elemento mas
        if (x < left.top()) {
            right.push(left.top());
            left.pop();
            left.push(x);
        } else {
            right.push(x);
        }
    }
}