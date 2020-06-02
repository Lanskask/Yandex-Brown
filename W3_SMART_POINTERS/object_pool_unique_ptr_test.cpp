#include <iostream>
#include "object_pool_unique_ptr.cpp"

using namespace std;

int counter = 0;

struct Counter {
    Counter() { ++counter; }

    ~Counter() { --counter; }
};

void Run1() {
    ObjectPool<Counter> op;
    for (int i = 0; i < 5; ++i) {
        cout << "Alocating object # " << i << endl;
        op.Allocate();
    }
    cout << "counter after loop: " << counter << endl;
}

void Run2_Test2() {
    ObjectPool<Counter> pool;

    //    pool.Deallocate(nullptr);
    try {
        for (int i = 0; i < 1000; ++i) {
            cout << "Alocating object # " << i << endl;
            pool.Allocate();
        }
    } catch (const bad_alloc& e) {
        cout << e.what() << endl;
    }
    cout << "counter after loop: " << counter << endl;
}

int main() {
//    Run1();
    Run2_Test2();

    cout << "counter before end: " << counter << endl;

    return 0;
}