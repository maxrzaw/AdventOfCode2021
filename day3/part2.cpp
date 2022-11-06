#include <bitset>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <list>

using namespace std;

int MASK = 0b0;
bool isZero(int n) { return (n & MASK) == 0; }
bool isOne(int n) { return (n & MASK) != 0; }

void Print(const std::list<int>& list) {
    for (std::list<int>::const_iterator i = list.begin(); i != list.end(); i++) {
        std::cout << std::bitset<16>(*i) << std::endl;
    }
    std::cout << '\n';
}

int main()
{
    list<int> oxygen;
    list<int> carbon;
    list<int> oxygen_save;
    list<int> carbon_save;

    int carbon_rating = 0b0;
    int oxygen_rating = 0b0;
    const int REPORT_LENGTH = 12;
    int value = 0;
    string s;

    while (cin >> s)
    {
        value = stoi(s, 0, 2);
        oxygen.push_back(value);
        carbon.push_back(value);
    }

    for (int i = 0; i < REPORT_LENGTH; ++i)
    {
        // reset counters
        int mask = 0b100000000000>> i;
        MASK = mask;
        size_t ones_counter = 0;

        // calculate most common bit
        for (list<int>::iterator it = carbon.begin(); it != carbon.end(); it++)
        {
            if (*it & mask)
            {
                ones_counter++;
            }
        }

        // remove elements
        if (ones_counter > (carbon.size() / 2) || (2 * ones_counter) == carbon.size())
        {
            // remove ones
            std::list<int> carbon_save(carbon);
            carbon.erase(std::remove_if(carbon.begin(), carbon.end(), isOne), carbon.end());
            if (carbon.size() == 0) {
                carbon = carbon_save;
                break;
            }
        }
        else
        {
            // remove zeros
            std::list<int> carbon_save(carbon);
            carbon.erase(std::remove_if(carbon.begin(), carbon.end(), isZero), carbon.end());
            if (carbon.size() == 0) {
                carbon = carbon_save;
                break;
            }
        }
    }

    for (int i = 0; i < REPORT_LENGTH; ++i)
    {
        // reset counters
        int mask = 0b100000000000>> i;
        MASK = mask;
        size_t ones_counter = 0;

        // calculate most common bit
        for (list<int>::iterator it = oxygen.begin(); it != oxygen.end(); it++)
        {
            if (*it & mask)
            {
                ones_counter++;
            }
        }

        // remove elements
        if (ones_counter > (oxygen.size() / 2) || (2 * ones_counter) == oxygen.size())
        {
            // remove zeros
            oxygen.erase(std::remove_if(oxygen.begin(), oxygen.end(), isZero), oxygen.end());
        }
        else
        {
            // remove ones
            std::list<int> oxygen_save(oxygen);
            oxygen.erase(std::remove_if(oxygen.begin(), oxygen.end(), isOne), oxygen.end());
            if (oxygen.size() == 0) {
                oxygen = oxygen_save;
                break;
            }
        }
    }

    oxygen_rating = oxygen.front();
    carbon_rating = carbon.front();
    printf("Oxygen: %d, Carbon: %d\n", oxygen_rating, carbon_rating);
    std::cout << oxygen_rating * carbon_rating << std::endl;
    return 0;
}
