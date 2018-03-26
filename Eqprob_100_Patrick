/*Patrick Catalin Alexandru Sava
The University of Manchester
O(N ^ 3)
Expected : Accepted*/
 
#include <fstream>
#include <iomanip>
#include <cassert>
#include <vector>
 
using namespace std;
 
bool isBetween (int inf, int num, int sup)
{
    // self-explanatory method
    return inf <= num and num <= sup;
}
 
long double computeAndSolve(string &str)
{
    int sizeOfString = (int)str.size();
    vector < vector <long long> > dp (sizeOfString + 2, vector <long long> (sizeOfString + 2, 0LL));
    long long correctCases = 0;
    for (int startingSubstringPosition = 0 ; startingSubstringPosition < sizeOfString; ++ startingSubstringPosition)
    {
        // for a fixed starting position for the matching substring
        for (int currentLength = 0; currentLength <= sizeOfString; ++ currentLength)
        {
            // initialise the whole matrix with 0
            for (int endPosition = 0; endPosition <= sizeOfString; ++ endPosition)
            {
                dp [currentLength][endPosition] = 0;
            }
        }
        for (int currentEndPosition = 0; currentEndPosition <= sizeOfString ; ++ currentEndPosition)
        {
            // treat the case in which the length of match is 0 as a base/trivial case
            dp[0][currentEndPosition] = 1;
        }
        for (int lengthOfMatching = 1; lengthOfMatching + startingSubstringPosition - 1 < sizeOfString; ++ lengthOfMatching)
        {
            // iterate through all the possible lengths of matching
            for (int currentEndPosition = lengthOfMatching; currentEndPosition - 1 < sizeOfString; ++ currentEndPosition)
            {
                // iterate through all the possible end positions
                dp[lengthOfMatching][currentEndPosition] += dp[lengthOfMatching][currentEndPosition - 1];
                if (str [currentEndPosition - 1] == str [lengthOfMatching + startingSubstringPosition - 1])
                {
                    // if match
                    dp [lengthOfMatching][currentEndPosition] += dp [lengthOfMatching - 1][currentEndPosition - 1];
                }
            }
        }
        for (int lenMatch = 1; lenMatch + startingSubstringPosition - 1 < sizeOfString; ++lenMatch)
        {
            // compute the amount of correct cases
            correctCases += dp[lenMatch][sizeOfString];
        }
    }
    return (long double) correctCases / (((1LL << sizeOfString) - 1) * (((sizeOfString + 1) * sizeOfString) / 2LL));
}
 
int main() {
    ifstream fin("eqprob.in");
    ofstream fout("eqprob.out");
    assert(fin.is_open());
    assert(fout.is_open());
    int numberOfTests;
    assert(fin >> numberOfTests);
    assert(isBetween(1, numberOfTests, 10));
    for (int currentTest = 1; currentTest <= numberOfTests; ++ currentTest)
    {
        int lengthOfString;
        assert(fin >> lengthOfString);
        string currentString;
        assert(fin >> currentString);
        assert(lengthOfString == (int)currentString.size());
        assert(isBetween(1, lengthOfString, 50));
        fout << fixed << setprecision(14) << computeAndSolve(currentString) << '\n';
    }
    return 0;
}
