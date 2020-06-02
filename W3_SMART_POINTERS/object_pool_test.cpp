#include <iostream>
#include "object_pool.cpp"

using namespace std;

int counter = 0;
struct Counter {
    Counter() {++counter;}
    ~Counter() {--counter;}
};

void Run1() {
    ObjectPool<Counter> op;
    for (int i = 0; i < 5; ++i) {
        cout << "Alocating object # " << i << endl;
        op.Allocate();
    }
    cout << "counter after loop: " << counter << endl;
}

int main() {
    Run1();
    cout << "counter before end: " << counter << endl;

    return 0;
}