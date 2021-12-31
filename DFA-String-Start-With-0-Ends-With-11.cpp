#include <bits/stdc++.h>
using namespace std;

int main()
{
    char s[50];
    cin >> s;

    int l;
    l = strlen(s);

    if (s[0] == '0' and s[l - 1] == '1' and s[l - 2] == '1')
    {
        cout << "String accepted";
    }
    else
    {
        cout << "String not accepted";
    }

    return 0;
}
