#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unordered_map>
#include <tuple>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    Point() { Point(0,0); }

    Point(string s) {
        size_t pos = 0;
        string delimiter = ",";
        pos = s.find(delimiter);

        x = stoi(s.substr(0, pos));
        y = stoi(s.substr(pos + delimiter.length()));
    }

    friend bool operator<(const Point& l, const Point& r) {
        if (l.x == r.x) {
            return l.y < r.y;
        }
        return l.x < r.x;
    }

    friend bool operator==(const Point& l, const Point& r) {
        return l.x == r.x && l.y == r.y;
    }

    friend bool operator!=(const Point& l, const Point& r) {
        return l.x != r.x || l.y != r.y;
    }

    friend ostream& operator<<(ostream& os, const Point &p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

};

namespace std {
    template<>
        struct hash<Point> {
            inline size_t operator()(const Point& p) const {
                size_t temp = (size_t)(p.y + ((p.x+1)/2));
                return (size_t)p.x + (temp * temp);
            }
        };
}


void parseLine(string s, Point& start, Point& end) {
    // process the string to get starting and ending point
    size_t pos = 0;
    string delimiter = " -> ";
    pos = s.find(delimiter);

    start = s.substr(0, pos);
    end = s.substr(pos + delimiter.length());
}

int plotPoint(unordered_map<Point, int> &points, const Point &p) {
    if (points.find(p) == points.end()) {
        points[p] = 0;
    }
    points[p]++;
    return points[p];
}

// Returns the number of new points equal to threshold
int plotLine(unordered_map<Point, int>& points, const Point& start, const Point& end, int threshold = 2) {
    // check for diagonal and ignore
    int y_sign = 0;
    int x_sign = 0;

    if (start.x != end.x) { // Horizontal
        x_sign = (end.x - start.x) > 0 ? 1 : -1;
    }

    if (start.y != end.y) { // Vertical
        y_sign = (end.y - start.y) > 0 ? 1 : -1;
    }

    int count = 0;
    Point p = start;

    // Plot the first point
    if (plotPoint(points, p) == threshold) {
        count++;
    }

    // Plot the rest of the points
    while (p != end) {
        p.y += y_sign;
        p.x += x_sign;
        if (plotPoint(points, p) == threshold) {
            count++;
        }
    }

    return count;
}



int main() {
    unordered_map<Point, int> points;
    string s = "";
    int threshold = 2;
    int count = 0;
    while (getline(cin, s)) {
        Point first, second;

        parseLine(s, first, second);

        count += plotLine(points, first, second, threshold);
    }
    cout << "Dangerous Points: " << count << endl;
}
