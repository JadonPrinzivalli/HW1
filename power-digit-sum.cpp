#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Used ChatGPT to help with command line input, error checking,
// and organizing parts of the program.

// Average times per day I thought about digit sums of a^b last week: 0

bool isValidNumber(string input)
{
    // Makes sure the input can be treated as a whole number.
    if (input.empty())
    {
        return false;
    }

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] < '0' || input[i] > '9')
        {
            return false;
        }
    }

    return true;
}

unsigned long long int power(unsigned int a, unsigned int b)
{
    // Starts at 1 so a^0 returns 1 correctly.
    unsigned long long int result = 1;

    for (unsigned int i = 0; i < b; i++)
    {
        result *= a;
    }

    return result;
}

vector<int> vectorize_digits(unsigned long long n)
{
    // A vector is used so each digit can be stored separately.
    vector<int> digits;

    string number = to_string(n);

    for (int i = 0; i < number.length(); i++)
    {
        // Subtracting '0' changes the digit character into an integer.
        digits.push_back(number[i] - '0');
    }

    return digits;
}

int sum_vector(vector<int> v)
{
    // Keeps one running total as the vector is read.
    int sum = 0;

    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i];
    }

    return sum;
}

string vec_to_string(vector<int> vec)
{
    // Builds the string in the exact bracket and comma format needed.
    string result = "[";

    for (int i = 0; i < vec.size(); i++)
    {
        result += to_string(vec[i]);

        // Avoids putting a comma after the final value.
        if (i < vec.size() - 1)
        {
            result += ", ";
        }
    }

    result += "]";

    return result;
}

int main(int argc, char* argv[])
{
    // argc must be 3 because the program name also counts as an argument.
    if (argc != 3)
    {
        cout << "Usage: ./pds <base> <exponent>" << endl;
        return 1;
    }

    string aInput = argv[1];
    string bInput = argv[2];

    // Checks negatives first so they get their own error message.
    if ((!aInput.empty() && aInput[0] == '-') ||
        (!bInput.empty() && bInput[0] == '-'))
    {
        cout << "Error: negative numbers are not allowed." << endl;
        return 1;
    }

    // Rejects letters, decimals, and other non-integer input.
    if (!isValidNumber(aInput) || !isValidNumber(bInput))
    {
        cout << "Error: integers only." << endl;
        return 1;
    }

    unsigned long long int aValue;
    unsigned long long int bValue;

    // stoull gives enough room to check the values before using unsigned int.
    try
    {
        aValue = stoull(aInput);
        bValue = stoull(bInput);
    }
    catch (...)
    {
        cout << "Error: value too large." << endl;
        return 1;
    }

    // power() takes unsigned int values, so the inputs must fit that type.
    if (aValue > 4294967295ULL || bValue > 4294967295ULL)
    {
        cout << "Error: value too large." << endl;
        return 1;
    }

    unsigned int a = aValue;
    unsigned int b = bValue;

    // Uses logs to check the size of a^b before actually calculating it.
    if (a > 0 && b > 0 &&
        b * log10(a) >= 64 * log10(2))
    {
        cout << "Error: result would cause overflow." << endl;
        return 1;
    }

    // Uses the required functions in order to get the final digit sum.
    unsigned long long int result = power(a, b);
    vector<int> digits = vectorize_digits(result);
    int digitSum = sum_vector(digits);

    cout << a << "^" << b << " = " << result << endl;
    cout << "Sum Of Digits: " << digitSum << endl;

    return 0;
}