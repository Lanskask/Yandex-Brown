#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <memory>
#include "../test_runner.h"

using namespace std;

template <class T>
class ObjectPool {
public:
    /**
      * Метод Allocate должен работать так:
      *     если есть хотя бы один освобождённый объект,
      *         то его надо перенести в множество выделенных
      *         и вернуть указатель на него в качестве результата функции
      *     если же освобождённых объектов нет,
      *         то создаётся новый объект,
      *         помещается в множество выделенных,
      *         и указатель на него возвращается в качестве результата функции
     **/
    T* Allocate() {
        if(!freed.empty()) {
            unique_ptr<T> el = move(freed.front());
            alocated[el.get()] = move(el);
            freed.pop();
            return el.get();
        } else {
            auto ob = make_unique<T>();
            alocated[ob.get()] = move(ob);
            return ob.get();
        }
    }

    /**
     * Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен просто возвращать nullptr.
     **/
    T* TryAllocate()  {
        if(!freed.empty()) {
            T* el = &freed.back();
            alocated.push_back(freed.back());
            freed.erase(freed.end());
            return &alocated.back();
        } else {
            return nullptr;
        }
    }


    /**Метод Deallocate переносит объект из множества выделенных в множество освобождённых;
     * если переданный объект не содержится в множестве выделенных,
     * метод Deallocate должен бросать исключение invalid_argument.
     */
    void Deallocate(T* object) {
        auto it = alocated.find(object);
        if(it == alocated.end())
            throw  invalid_argument("No such argument");
        alocated.erase(object);
        freed.push(it->second);
    }

private:
    unordered_map<T*, unique_ptr<T>> alocated;
    queue<unique_ptr<T>> freed;
//    T[]* alocated;
//    T* freed;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}