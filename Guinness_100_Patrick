/*Patrick Catalin Alexandru Sava
The University of Manchester
Guinness
Expected : Accepted*/
 
#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
template <typename T>
bool isBetween (T inf, T number, T sup)
{
    return inf <= number and number <= sup;
}
 
int main() {
    const char inputStream[] = "guinness.in";
    const char outputStream[] = "guinness.out";
 
    ifstream input(inputStream);
    ofstream output(outputStream);
 
    assert(input.is_open());
    assert(output.is_open());
 
    const auto MaxNumberOfDigits = static_cast<const int>(1e5);
    const auto MaxValueOfBase = static_cast<const int>(1e9);
    const auto MaxValueOfModulo = static_cast<const int>(1e9);
    const auto MaxNumberOfTests = 10;
    int numberOfTests;
    assert(input >> numberOfTests);
    assert(isBetween(1, numberOfTests, MaxNumberOfTests));
    for (int currentTest = 1; currentTest <= numberOfTests; ++ currentTest)
    {
        int base, modulo;
        string exponent;
        assert(input >> base >> exponent >> modulo);
        assert(isBetween(0, base, MaxValueOfBase));
        assert(isBetween(1, (int) exponent.size(), MaxNumberOfDigits));
        assert(isBetween(1, modulo, MaxValueOfModulo));
        reverse(exponent.begin(), exponent.end());
        int currentResult = 1;
        int lastPowerOfTen = base;
        for (auto lastDigitOf: exponent) {
            auto digit = lastDigitOf - '0';
            int remainingTimes = 10 - digit;
            int nextPowerOfTen = 1;
            for (int times = 1; times <= digit; ++times) {
                nextPowerOfTen = static_cast<int>(1LL * nextPowerOfTen * lastPowerOfTen % modulo);
            }
            currentResult = static_cast<int>(1LL * currentResult * nextPowerOfTen % modulo);
            for (int times = 1; times <= remainingTimes; ++times) {
                nextPowerOfTen = static_cast<int>(1LL * nextPowerOfTen * lastPowerOfTen % modulo);
            }
            lastPowerOfTen = nextPowerOfTen;
        }
        output << currentResult << '\n';
    }
    return 0;
}
