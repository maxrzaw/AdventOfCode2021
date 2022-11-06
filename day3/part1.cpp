#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    const int REPORT_LENGTH = 12;
    long ones[REPORT_LENGTH];
    for (long i = 0; i < REPORT_LENGTH; ++i) {
        ones[i] = 0;
    }
    long value = 0;
    long count = 0;
    string s;

    while (cin >> s)
    {
        //printf("string: %s\n", s.c_str());
        value = stoi(s, 0, 2);
        //printf("value: %ld\n", value);
        count++;
        for (long i = 0; i < REPORT_LENGTH; ++i)
        {
            if ((value >> i) % 2 == 1)
            {
                ones[i]++;
            }
        }
        //s = "";
        //for (int i = 0; i < REPORT_LENGTH; ++i)
        //{
        //    s.append(std::to_string(ones[i]));
        //}
        //printf("ones: %s\n", s.c_str());
    }

    long gamma = 0b0;
    long epsilon = 0b0;
    for (long i = 0; i < REPORT_LENGTH; ++i)
    {
        if (ones[i] > (count / 2))
        {
            gamma = gamma | (0b1 << i);
        }
        else
        {
            epsilon = epsilon | (0b1 << i);
        }
    }
    printf("Gamma: %ld, Epsilon: %ld\n", gamma, epsilon);
    std::cout << gamma * epsilon << std::endl;
    return 0;
}
