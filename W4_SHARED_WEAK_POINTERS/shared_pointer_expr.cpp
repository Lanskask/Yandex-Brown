#include <iostream>
#include <vector>
#include <algorithm>

#include "../profiler.h"

using namespace std;

vector<int> Sorted(vector<int> data) {
    sort(data.begin(), data.end());
    return data;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &vect) {
    for (const auto &x : vect)
        out << x << ", ";
    out << endl;
}

void Run1() {
    const vector<int> sorted_unique_numbers = []() {
        vector<int> sorted = Sorted(
                {7, 9, 4, 6, 2, 3, 5, 8, 9, 5}
        );
        auto it = unique(sorted.begin(), sorted.end());
        sorted.erase(it, sorted.end());
        return sorted;
    }();

    cout << sorted_unique_numbers << endl;
}

void Run2_Test_log_duration_of_object_creation() {
    const vector<int> result = []() {
        LOG_DURATION("Sorted number build");
        return Sorted(
                {7, 9, 4, 6, 2, 3, 5, 8, 9, 5}
        );
    }();
}

int main() {
//    Run1();
    Run2_Test_log_duration_of_object_creation();

    return 0;
}