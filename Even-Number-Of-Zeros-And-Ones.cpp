// WAP to implement DFA which accept even number of 0's and even number of 1's

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, rem, one = 0, zero = 0;

    // Enter the number in binary
    cin >> n;

    while (n > 0)
    {
        rem = n % 10;

        // Check the number of ones and zeros
        if (rem == 1)
        {
            one++;
        }
        else if (rem == 0)
        {
            zero++;
        }

        n /= 10;
    }

    // if zero and one are even in number then the string is acceptable otherwise not acceptable
    if (zero % 2 == 0 and one % 2 == 0)
    {
        cout << "String accepted";
    }
    else
    {
        cout << "String not accepted";
    }

    return 0;
}
