#include<iostream>
#include <memory>

using namespace std;

struct Actor {
    Actor() {cout << "I was born" << endl;}
    ~Actor() {cout << "I am dead! :(" << endl;}
    void DoWork() {cout << "I did some work" << endl;}
};

void run(Actor* ptr) {
    if(ptr)
        ptr->DoWork();
    else
        cout << "An actor was expected! :/" << endl;
}

int main() {
//    auto ptr = new Actor;
//    ptr->DoWork();
//    delete ptr;

//    auto ptr = unique_ptr<Actor>(new Actor);
    auto ptr = make_unique<Actor>();
//    ptr->DoWork();
    run(ptr.get());

    auto ptr2 = move(ptr);
    run(ptr2.get());
    run(ptr.get());

    return EXIT_SUCCESS;
}