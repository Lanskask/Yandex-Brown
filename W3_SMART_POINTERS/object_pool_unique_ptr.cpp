#include "../test_runner.h"

#include <algorithm>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <unordered_map>
#include <memory>

using namespace std;

template<class T>
class ObjectPool {
public:
    T *Allocate();

    T *TryAllocate();

    void Deallocate(T *object);

private:
    queue<unique_ptr<T>> free;
//    set<unique_ptr<T>> allocated;
    unordered_map<T *, unique_ptr<T>> allocated;
};

template<typename T>
T *ObjectPool<T>::Allocate() {
    if (free.empty()) {
        free.push(make_unique<T>());
    }
//    auto ret = free.front(); // copy of ptr
    auto ptr = move(free.front()); // moving
    free.pop();
//    try {
//        allocated.insert(ret);
//    } catch (const bad_alloc&) {
//        delete ret;
//        throw;
//    }
    T* ret = ptr.get();
    allocated[ret] = move(ptr);

    return ret;
}

template<typename T>
void ObjectPool<T>::Deallocate(T *object) {
//    if (allocated.find(object) == allocated.end()) {
//        throw invalid_argument("");
//    }
//    allocated.erase(object);
//    free.push(object);
    auto it = allocated.find(object);
    if(it == allocated.end()) {
        throw invalid_argument("invalid_argument ");
    }
    free.push(move(it->second));
    allocated.erase(it);
}

template<typename T>
T *ObjectPool<T>::TryAllocate() {
    if (free.empty()) {
        return nullptr;
    }
    return Allocate();
}

