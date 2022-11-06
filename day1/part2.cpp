#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> window = queue<int>();
    int curr_sum = 0;
    int depth;
    for (int i = 0; i < 3; ++i) {
        cin >> depth;
        curr_sum += depth;
        window.push(depth);
    }

    int prev_sum = curr_sum;
    int count_increases = 0;

    while (cin >> depth) {
        curr_sum += depth;
        curr_sum -= window.front();
        window.pop();
        window.push(depth);

        if (curr_sum > prev_sum) {
            count_increases++;
        }

        prev_sum = curr_sum;
    }
    cout << "Total increases: " << count_increases << endl;
}
