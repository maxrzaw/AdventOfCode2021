#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void processCommand(int &x, int &y, int &aim, string command, int distance) {

    if (command.compare("forward") == 0) {
        x += distance;
        y += aim * distance;
    } else if (command.compare("down") == 0) {
        aim += distance;
    } else if (command.compare("up") == 0) {
        aim -= distance;
    } else {
        cout << "Error processing command.\n" << command << " " << distance << endl;
        exit(1);
    }
}

int main() {
    int x = 0;
    int y = 0;
    int aim = 0;
    string command;
    int distance;

    while (cin.good() && !cin.eof()) {
        cin >> command;
        cin >> distance;
        if (cin.good()) {
            processCommand(x, y, aim, command, distance);
        }
    }

    cout << "X: " << x << ", Y: " << y << endl;
    cout << "Product: " << x * y << endl;
    return 0;
}
