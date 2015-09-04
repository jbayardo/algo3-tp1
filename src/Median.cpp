#include "Median.h"

Median::Median() {  }

int Median::get() {
    if (left.size() == right.size()) {
        return (left.top() + right.top())/2;
    } else {
        return left.top();
    }
}

void Median::insertSingle(int x) {
    if (left.size() == 0) {
        left.push(x);
    } else if (left.size() != right.size()) {
        if (left.top() < x) {
			right.push(x);
        } else {
			right.push(left.top());
			left.pop();
			left.push(x);
        }
    } else {
        if (x > right.top()) {
            left.push(right.top());
            right.pop();
            right.push(x);
        } else {
            left.push(x);
        }
    }
}