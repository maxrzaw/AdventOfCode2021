#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int count_increases = 0;
    int prev, curr;
    cin >> prev;

    while (cin >> curr) {
        if (curr > prev) {
            count_increases++;
        }

        prev = curr;
    }
    cout << "Total increases: " << count_increases << endl;
}
