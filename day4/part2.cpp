#include <algorithm>
#include <cstdio>
#include <exception>
#include <iostream>
#include <ostream>
#include <queue>
#include <vector>
using namespace std;

class Spot {
    public:
        int _value;
        bool marked;
        Spot(int value = 0) {
            _value = value;
            marked = false;
        }

        void Mark() {
            marked = true;
        }

        void SetValue(int value) {
            _value = value;
        }

        bool EqualValue(int number) {
            return number == _value;
        }

        int Value() {
            return _value;
        }

        bool Marked() {
            return marked;
        }
};

ostream& operator<<(ostream& os, const Spot& s) {
    os << "(" << s._value << "," << s.marked << ")";
    return os;
}

class Board {
    bool winning;
    public:
        Spot data[5][5];
        Board() { winning = false; };

        void Mark(int number) {
            for (int i = 0; i < 5; ++i) {
               for (int j = 0; j < 5; ++j) {
                    if (data[i][j].EqualValue(number)) {
                        data[i][j].Mark();
                        return;
                    }
                }
            }
        }

        void SetSpot(const int row, const int col, const int value) {
            data[row][col].SetValue(value);
        }

        void Print() {
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    std::cout << data[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        bool CheckRow(const int row) {
            for (int i = 0; i < 5; ++i) {
                if (!data[row][i].Marked()) {
                    return false;
                }
            }

            return true;
        }

        bool CheckCol(const int col) {
            for (int i = 0; i < 5; ++i) {
                if (!data[i][col].Marked()) {
                    return false;
                }
            }

            return true;
        }

        bool IsWinning() {
            if (winning) {
                return true;
            }

            // rows
            for (int i = 0; i < 5; ++i) {
                if (CheckRow(i)) {
                    winning = true;
                    return true;
                }
            }
            // columns
            for (int i = 0; i < 5; ++i) {
                if (CheckCol(i)) {
                    winning = true;
                    return true;
                }
            }

            return false;
        }

        int SumUnmarked() {
            int sum = 0;
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (!data[i][j].Marked()) {
                        sum += data[i][j].Value();
                    }
                }
            }
            return sum;
        }
};

void readBoard(Board &b) {
    int value;
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            cin >> value;
            if (cin.eof()) {
                throw std::exception();
            }
            b.SetSpot(row, col, value);
        }
    }
}

int main() {
    std::queue<int> numbers;
    std::vector<Board> boards;

    // read in all the numbers
    string s;
    cin >> s;
    size_t pos = 0;
    string delimiter = ",";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        numbers.push(stoi(s.substr(0, pos)));
        s.erase(0, pos + delimiter.length());
    }
    numbers.push(stoi(s));

    // read in the boards
    while (true) {
        Board b;
        try {
            readBoard(b);
        } catch (const std::exception &e) {
            break;
        }
        boards.push_back(b);
    }

    size_t winners = 0;
    while (!numbers.empty()) {
        int number = numbers.front();
        numbers.pop();

        for (size_t i = 0; i < boards.size(); ++i) {
            if (!boards[i].IsWinning()) {
                boards[i].Mark(number);

                if (boards[i].IsWinning()) {
                    winners++;

                    if (winners == boards.size()) {
                        int sum = boards[i].SumUnmarked();
                        printf("Last Winning Score is: %d, %d * %d\n", sum * number, sum, number);
                        printf("Last Winning Board is:\n");
                        boards[i].Print();
                        return 0;
                    }
                }
            }
        }
    }
    cout << "No winning boards" << endl;
    return 0;
}
