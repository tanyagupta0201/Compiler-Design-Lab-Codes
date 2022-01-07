#include <bits/stdc++.h>
using namespace std;

int main()
{
    char s[50];
    cin >> s;

    int l;
    l = strlen(s);

    if (s[0] == 'a' and s[l - 1] == 'b' and s[l - 2] == 'b' and s[l - 3] == 'a')
    {
        cout << "String accepted";
    }
    else
    {
        cout << "String not accepted";
    }

    return 0;
}
