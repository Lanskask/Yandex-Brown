#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void Run1() {
    int* in = new int;
    *in = 1;
    cout << *in << endl;
}

void Run2() {
    vector<int> v = {1,2,3,4};
    int* el = &v.back();
    cout << el << endl;
    cout << *el << endl;
}

template<typename T>
class ObjectPool {
public:
    T *Allocate() {
        if (!freed.empty()) {
            T *el = &freed.back();
            alocated.push_back(move(freed.back()));
            freed.erase(freed.end());
            return &alocated.back();
        } else {
            T *ob = new T;
            alocated.push_back(move(*ob));
            return &alocated.back();
        }
    }

private:
    vector<T> freed;
    vector<T> alocated;
};

void Run3() {
    ObjectPool<int> op;
    op.Allocate();
}

int* ret_int_ptr() {
    int* i = new int;
    *i = 5;

    queue<int> q1;
    q1.push(5);
    int i2 = q1.front();
    cout << "i2: " << i2 << endl;
    int* tmp = &i2;
    return tmp;
//    return &i2;
//    return i;
}

void Run4() {
    int* i3 = ret_int_ptr();
    cout << *i3 << endl;
}

int main() {
//    Run1();
//    Run2();
    Run4();

    return 0;
}