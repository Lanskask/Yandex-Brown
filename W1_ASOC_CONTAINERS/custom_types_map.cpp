#include<iostream>
#include<iomanip>
#include<tuple>
#include<set>
#include<unordered_set>
#include<random>
#include "../profiler.h"

using namespace std;

struct Plate {
    char C1;
    int Number;
    char C2;
    char C3;
    int Region;

    bool operator==(const Plate &r) const {
        return C1 == r.C1
               && Number == r.Number
               && C2 == r.C2
               && C3 == r.C3
               && Region == r.Region;
    }


    ostream &operator<<(ostream &out) {
        out << C1;
        out << setw(3) << setfill('0') << Number;
        out << C2;
        out << C3;
        out << setw(2) << setfill('0') << Region;
        return out;
    }

    bool operator<(const Plate &r) const {
        return tie(C1, Number, C2, C3, Region)
               < tie(r.C1, r.Number, r.C2, r.C3, r.Region);
    }
};

//namespace std {
//    template<>
//    struct hash<Plate> {
//        size_t operator()(const Plate &p) const {
//            return p.Number;
//        }
//    };
//}

namespace std {
    template<>
    struct hash<Plate> {
        size_t operator()(const Plate &p) const {
            size_t result = p.Number;
            result = result * 100 + p.Region;
            result = result * 100 + (p.C1 - 'A');
            result = result * 100 + (p.C2 - 'A');
            result = result * 100 + (p.C3 - 'A');

            return result;
        }
    };
}

struct MyType {
    double d;
    string str;
    Plate plate;
};

struct MyTypeHasher {
    size_t operator()(const MyType &p) const {
        size_t r1 = dhash(p.d);
        size_t r2 = shash(p.str);
        size_t r3 = plate_hash(p.plate);
        // Ax^2 + Bx + C
        size_t x = 37;
        return r1*x*x + r2*x + r3;
    }

    hash<double> dhash;
    hash<string> shash;
    hash<Plate> plate_hash;
};

//struct PlateHasher {
//    size_t operator()(const Plate &p) const {
//        return p.Number;
//    }
//};

class PlateGenerator {
public:
    Plate GetRandomPlate() {
        Plate p;
        p.C1 = Letters[LetterDist(RandEng)];
        p.Number = NumberDist(RandEng);
        p.C2 = Letters[LetterDist(RandEng)];
        p.C3 = Letters[LetterDist(RandEng)];
        p.Region = RegionDist(RandEng);
        return p;
    }

private:
    const static int N = 12;
    const array<char, N> Letters = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'K', 'L', 'M', 'N', 'O'
    };
    default_random_engine RandEng;
    uniform_int_distribution<int> LetterDist{0, N - 1};
    uniform_int_distribution<int> NumberDist{1, 999};
    uniform_int_distribution<int> RegionDist{1, 99};
};

void Run1() {
    PlateGenerator pg;
    set<Plate> s_plates;
//    unordered_set<Plate, PlateHasher> h_plates;
    unordered_set<Plate> h_plates;
    const int N = 10;

    for (int i = 0; i < N; ++i) {
        Plate p = pg.GetRandomPlate();
        s_plates.insert(p);
        h_plates.insert(p);
    }

//    cout << "-- s_plates --" << endl;
//    for (const auto &p : s_plates) {
//        cout << p << endl;
//    }
//    cout << "-- h_plates --" << endl;
//    for (const auto &p : h_plates) {
//        cout << p << endl;
//    }
}

void Run2_Test_performance() {
    PlateGenerator pg;
    set<Plate> s_plates;
//    unordered_set<Plate, PlateHasher> h_plates;
    unordered_set<Plate> h_plates;
    const int N = 50'000;

    {
        LOG_DURATION("set");
        for (int i = 0; i < N; ++i) {
            s_plates.insert(pg.GetRandomPlate());
        }
        for (int i = 0; i < N; ++i) {
            s_plates.find(pg.GetRandomPlate());
        }
    }
    {
        LOG_DURATION("unordered_set");
        for (int i = 0; i < N; ++i) {
            h_plates.insert(pg.GetRandomPlate());
        }
        for (int i = 0; i < N; ++i) {
            h_plates.find(pg.GetRandomPlate());
        }
    }
}

void Run3_MyTypeHasher() {
    unordered_set<MyType, MyTypeHasher> mytype_set;
}

int main() {
//    Run1();
    Run2_Test_performance();
    Run3_MyTypeHasher();

    return EXIT_SUCCESS;
}