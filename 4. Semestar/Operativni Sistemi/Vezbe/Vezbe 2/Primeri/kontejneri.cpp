#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

using std::accumulate;
using std::copy_if;
using std::cout;
using std::endl;
using std::iota;
using std::map;
using std::stack;
using std::string;
using std::vector;

void vektor_primer() {
    vector<int> v = {3, 1, 4, 1, 5, 9, 2};
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    v.push_back(99);
    v.push_back(98);
    v.insert(v.begin() + 2, 77);
    v.pop_back();
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

void mapa_primer() {
    map<string, int> m = {{"abc", 1}, {"def", 2}, {"xyz", 907}};
    for (const auto &n : m) {
        cout << "m[" << n.first << "] = " << n.second << endl;
    }
    m["abc"] = 5;
    m["qux"] = 9;

    for (const auto &n : m) {
        cout << "m[" << n.first << "] = " << n.second << endl;
    }
}

void stek_primer() {
    stack<int> s;
    s.push(3);
    s.push(1);
    s.push(4);
    s.push(1);
    s.push(5);
    s.push(9);
    s.push(2);
    s.push(6);
    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
}

bool div_three(int i) { return i % 3 == 0; }

void algo_primer() {
    vector<int> v(1024);
    vector<int> vv(1024);
    iota(v.begin(), v.end(), 1);
    copy_if(v.begin(), v.end(), vv.begin(), div_three);
    int r = accumulate(vv.begin(), vv.end(), 0);
    cout << r << endl;
}

int main() {
    vektor_primer();
    // mapa_primer();
    // stek_primer();
    // algo_primer();
    return 0;
}
