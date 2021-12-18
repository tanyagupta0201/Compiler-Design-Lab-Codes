// C++ Program to Implement Operator Precedence Parser - Bottom-Up Parsing

#include <iostream>
#include <string>
#include <deque>
using namespace std;

int n, n1, n2;

int getPosition(string arr[], string q, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (q == arr[i])
            return i;
    }
    return -1;
}

int main()
{
    string prods[10], leads[10], trails[10], nonterms[10], terms[10];
    char op_table[20][20] = {};

    cout << "Enter the number of productions : ";
    cin >> n;
    cin.ignore();

    cout << "Enter the productions" << endl;
    for (int i = 0; i < n; i++)
    {
        getline(cin, prods[i]);
    }

    cout << "Enter the number of Terminals : ";
    cin >> n2;
    cin.ignore();

    cout << "Enter the Terminals" << endl;
    for (int i = 0; i < n2; i++)
    {
        cin >> terms[i];
    }

    terms[n2] = "$";
    n2++;

    cout << "Enter the number of Non-Terminals : ";
    cin >> n1;
    cin.ignore();

    for (int i = 0; i < n1; i++)
    {
        cout << "Enter Non-Terminal : ";
        getline(cin, nonterms[i]);

        cout << "Enter Leads of " << nonterms[i] << " : ";
        getline(cin, leads[i]);

        cout << "Enter Trails of " << nonterms[i] << " : ";
        getline(cin, trails[i]);
    }

    cout << "Enter the Rules (exit to stop)" << endl;
    string rule = "";
    while (rule != "exit")
    {
        getline(cin, rule);

        if (rule[0] == '1')
        {
            int row = getPosition(terms, rule.substr(2, 1), n2);
            int column = getPosition(terms, rule.substr(4, 1), n2);
            op_table[row][column] = '=';
        }
        if (rule[0] == '2')
        {
            int ntp = getPosition(nonterms, rule.substr(4, 1), n1);
            int row = getPosition(terms, rule.substr(2, 1), n2);
            for (int j = 0; j < leads[ntp].size(); j++)
            {
                int col = getPosition(terms, leads[ntp].substr(j, 1), n2);
                op_table[row][col] = '<';
            }
        }
        if (rule[0] == '3')
        {
            int col = getPosition(terms, rule.substr(4, 1), n2);
            int ntp = getPosition(nonterms, rule.substr(2, 1), n1);
            for (int j = 0; j < trails[ntp].size(); j++)
            {
                int row = getPosition(terms, trails[ntp].substr(j, 1), n2);
                op_table[row][col] = '>';
            }
        }
    }

    for (int j = 0; j < leads[0].size(); j++)
    {
        int col = getPosition(terms, leads[0].substr(j, 1), n2);
        op_table[n2 - 1][col] = '<';
    }

    for (int j = 0; j < trails[0].size(); j++)
    {
        int row = getPosition(terms, trails[0].substr(j, 1), n2);
        op_table[row][n2 - 1] = '>';
    }
    cout << endl;
    cout << "Grammar" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << prods[i] << endl;
    }

    // Display Table
    for (int j = 0; j < n2; j++)
        cout << "\t" << terms[j];
    cout << endl;

    for (int i = 0; i < n2; i++)
    {
        cout << terms[i] << "\t";
        for (int j = 0; j < n2; j++)
        {
            cout << op_table[i][j] << "\t";
        }
        cout << endl;
    }

    // Parsing String
    char c;
    do
    {
        string ip;
        deque<string> op_stack;
        op_stack.push_back("$");
        cout << "Enter the string to be parsed : ";
        getline(cin, ip);
        ip.push_back('$');
        cout << "Stack\ti/p Buffer\tRelation\tAction" << endl;

        while (true)
        {
            for (int i = 0; i < op_stack.size(); i++)
                cout << op_stack[i];
            cout << "\t";
            cout << ip << "\t";
            int row = getPosition(terms, op_stack.back(), n2);
            int column = getPosition(terms, ip.substr(0, 1), n2);
            if (op_table[row][column] == '<')
            {
                op_stack.push_back("<");
                op_stack.push_back(ip.substr(0, 1));
                ip = ip.substr(1);
                cout << "\t"
                     << "<\t\tPush";
            }
            else if (op_table[row][column] == '=')
            {
                op_stack.push_back("=");
                op_stack.push_back(ip.substr(0, 1));
                ip = ip.substr(1);
                cout << "\t"
                     << "=\t\tPush";
            }
            else if (op_table[row][column] == '>')
            {
                string last;
                do
                {
                    op_stack.pop_back();
                    last = op_stack.back();
                    op_stack.pop_back();
                } while (last != "<");
                cout << "\t"
                     << ">\t\tPop";
            }
            else
            {
                if (ip[0] == '$' && op_stack.back() == "$")
                {
                    cout << "\t\t\tAccept\nString Parsed." << endl;
                    break;
                }
                else
                {
                    cout << endl
                         << "String cannot be Parsed." << endl;
                    break;
                }
            }
            cout << endl;
        }
        cout << "Continue?(Y/N) ";
        cin >> c;
        cin.ignore();
    } while (c == 'y' || c == 'Y');
    return 0;
}

/*

OUTPUT:
Enter the number of productions : 4
Enter the productions
S->aAcBe
A->Ab
A->b
B->d
Enter the number of Terminals : 5
Enter the Terminals
a
b
c
d
e
Enter the number of Non-Terminals : 3
Enter Non-Terminal : S
Enter Leads of S : a
Enter Trails of S : e
Enter Non-Terminal : A
Enter Leads of A : bd
Enter Trails of A : bd
Enter Non-Terminal : B
Enter Leads of B : d
Enter Trails of B : d
Enter the Rules (exit to stop)
1 a c
1 c e
2 a A
2 c B
3 A c
3 B e
3 A b
exit


Grammar
S->aAcBe
A->Ab
A->b
B->d
        a       b       c       d       e       $
a               <       =       <
b               >       >
c                                 <       =
d               >       >                >
e                                                 >
$       <

Enter the string to be parsed : abcde
Stack    i/p Buffer       Relation        Action
$          abcde$            <            Push
$<a        bcde$             <            Push
$<a<b      cde$              >            Pop
$<a        cde$              =            Push
$<a=c      de$               <            Push
$<a=c<d    e$                >            Pop
$<a=c      e$                =            Push
$<a=c=e    $                 >            Pop
$          $                              Accept

String Parsed.
Continue?(Y/N) Y

Enter the string to be parsed : abde
Stack      i/p Buffer      Relation        Action
$            abde$           <             Push
$<a          bde$            <             Push
$<a<b        de$
String cannot be parsed.

Continue?(Y/N) N

*/