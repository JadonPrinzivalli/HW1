#include <iostream>
#include <string>

using namespace std;

// Used ChatGPT to help with command line input and error checking.

// Average times per day I thought about digit sums of a^b last week: 0

bool isValidNumber(string input)
{
    // Makes sure the input is not empty.
    if (input.empty())
    {
        return false;
    }

    // Checks that every character is a digit.
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] < '0' || input[i] > '9')
        {
            return false;
        }
    }

    return true;
}

unsigned int power(unsigned short a, unsigned short b)
{
    // Multiplies a by itself b times.
    unsigned int result = 1;

    for (unsigned short i = 0; i < b; i++)
    {
        result *= a;
    }

    return result;
}

unsigned int sumDigits(unsigned int n)
{
    unsigned int sum = 0;

    // Takes off each digit and adds it to the sum.
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

int main(int argc, char* argv[])
{
    // Need the program name plus two inputs.
    if (argc != 3)
    {
        cout << "Usage: ./pds <base> <exponent>" << endl;
        return 1;
    }

    string aInput = argv[1];
    string bInput = argv[2];

    if (!isValidNumber(aInput) || !isValidNumber(bInput))
    {
        cout << "Error: positive integers only." << endl;
        return 1;
    }

    int aValue;
    int bValue;

    // Handles numbers that are too large for stoi.
    try
    {
        aValue = stoi(aInput);
        bValue = stoi(bInput);
    }
    catch (...)
    {
        cout << "Error: value too large." << endl;
        return 1;
    }

    // unsigned short max is 65535.
    if (aValue > 65535 || bValue > 65535)
    {
        cout << "Error: value too large." << endl;
        return 1;
    }

    unsigned short a = aValue;
    unsigned short b = bValue;

    unsigned int result = power(a, b);
    unsigned int digitSum = sumDigits(result);

    cout << a << "^" << b << " = " << result << endl;
    cout << "Sum Of Digits: " << digitSum << endl;

    return 0;
}