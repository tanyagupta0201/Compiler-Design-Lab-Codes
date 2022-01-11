// Implement DFA for L = { (01)^i (1)^2j where i >= 1 an j >= 1}

#include <bits/stdc++.h>
using namespace std;

int main()
{
    char s[50];
    cin >> s;

    int c = 0, l;
    l = strlen(s);

    if (s[0] == '0' and s[1] == '1')
    {
        for (int i = 1; i < l; i++)
        {
            if (s[i] == '0')
            {
                c = 0;
            }
            else
            {
                c++;
            }
        }

        if (c % 2 == 1)
        {

            cout << "accepted";
        }
        else
        {
            cout << "not accepted";
        }
    }

    else
    {
        cout << " not accepted";
    }

    return 0;
}
