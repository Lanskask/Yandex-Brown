#include<iostream>
#include<set>
#include <algorithm>
#include <fstream>
#include "../profiler.h"

using namespace std;

struct NCString : public string {
    using string::string;
//    NCString(const NCString&) = delete;
//    NCString(NCString&&) = default;
};

template<typename T>
void PrintSet(set<T> s) {
    for (const auto &x : s) {
        cout << x << ", ";
    }
    cout << endl;
}

template<typename T>
void PrintFirstNInSet(set<T> set_, int counter) {
    for (const auto &x : set_) {
        cout << x << ", ";
        if (counter <= 0) return;
        counter--;
    }
}



void Run1() {
    set<string> ss;
    ss.insert("Aaa");
    ss.insert("Bbb");
    ss.insert("Ccc");

    PrintSet(ss);

    auto it = ss.begin();
    string temp = *it;
    temp[0] = tolower(temp[0]);
    ss.erase(it);
    ss.insert(temp);

    PrintSet(ss);
}

void Run2() {
    set<NCString> ss;
    ss.insert("Aaa");
    ss.insert("Bbb");
    ss.insert("Ccc");

    PrintSet(ss);

    auto it = ss.begin();
    auto node = ss.extract(it);
    string &temp = node.value();

//    temp[0] = tolower(temp[0]);
//    temp = to_lower(temp);
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    //    ss.erase(it);
    ss.insert(move(node));

    PrintSet(ss);
}

void Run3() {
//    set<NCString> ss;
    set<string> ss;
    ss.insert("Aaa");
    ss.insert("Bbb");
    ss.insert("Ccc");

    set<string> ss2;
    ss2.insert("Aaa2");
    ss2.insert("Bbb2");
    ss2.insert("Ccc2");

    ss.merge(ss2);
    cout << "ss: ";
    PrintSet(ss);
    cout << "ss2: ";
    PrintSet(ss2);
}

void Run4() {
    set<string> s_words;

    ifstream fs("input.txt");
    if(!fs) {
        cout << "File not found" << endl;
        return;
    }
    string text;
    while (fs >> text) {
        if(!isdigit(text[0]))
            s_words.insert(text);
    }

    PrintFirstNInSet(s_words, 5);

//    filter(s_words.begin(), s_words.end(), [](string& word) {
//        return isdigit(word[0]);
//    });
    // filter Set
//    for(const auto& x : s_words) {
//        if(isdigit(x[0]))
//            s_words.erase(x);
//    }
    auto it2 = s_words.begin() + 4;

    LOG_DURATION() {
        for (char c = 'a'; c < 'z'; ++c) {
            string s(1, c);
            s_words.lower_bound(s);
        }
    }
    LOG_DURATION() {
        for (char c = 'a'; c < 'z'; ++c) {
            string s(1, c);
            lower_bound(s_words.begin(), s_words.end(), s);
        }
    }
}


int main() {
//    Run1();
//    Run2();
//    Run3();
    Run4();

    return EXIT_SUCCESS;
}