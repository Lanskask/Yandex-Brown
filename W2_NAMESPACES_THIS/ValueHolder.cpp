#include <iostream>

using namespace std;

struct ValueHolder {
    int x;

    void SetValue(int value) {
        this->x = value;
        cout << this->x << ' ';
    }
};

//void SetValue(ValueHolder* this_, int value) {
//    this_->x = value;
//    cout << this_->x << ' ';
//}

int main() {
    ValueHolder a, b;
    a.SetValue(3);
    b.SetValue(5);

    cout << a.x << ' ' << b.x << ' ' << endl;
    return 0;
}