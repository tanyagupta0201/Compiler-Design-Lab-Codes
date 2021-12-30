#include <stdio.h>
#include <ctype.h>

void Find_First(char[], char);
void Array_Manipulation(char[], char);

int limit;
char production[25][25];

int main()
{
    char option;
    char ch;
    char array[25];
    int count;

    printf("\nEnter Total Number of Productions:\t");
    scanf("%d", &limit);

    for (count = 0; count < limit; count++)
    {
        printf("\nValue of Production Number [%d]:\t", count + 1);
        scanf("%s", production[count]);
    }
    do
    {
        printf("\nEnter a Value to Find First:\t");
        scanf(" %c", &ch);

        Find_First(array, ch);

        printf("\nFirst Value of %c:\t{ ", ch);
        for (count = 0; array[count] != '\0'; count++)
        {
            printf(" %c ", array[count]);
        }
        printf("}\n");

        printf("To Continue, Press Y:\t");
        scanf(" %c", &option);
    } while (option == 'y' || option == 'Y');

    return 0;
}

void Find_First(char *array, char ch)
{
    int count, j, k;
    char temporary_result[20];
    int x;
    temporary_result[0] = '\0';
    array[0] = '\0';

    if (!(isupper(ch)))
    {
        Array_Manipulation(array, ch);
        return;
    }

    for (count = 0; count < limit; count++)
    {
        if (production[count][0] == ch)
        {
            if (production[count][2] == '$')
            {
                Array_Manipulation(array, '$');
            }
            else
            {
                j = 2;
                while (production[count][j] != '\0')
                {
                    x = 0;
                    Find_First(temporary_result, production[count][j]);

                    for (k = 0; temporary_result[k] != '\0'; k++)
                    {
                        Array_Manipulation(array, temporary_result[k]);
                    }

                    for (k = 0; temporary_result[k] != '\0'; k++)
                    {
                        if (temporary_result[k] == '$')
                        {
                            x = 1;
                            break;
                        }
                    }

                    if (!x)
                    {
                        break;
                    }
                    j++;
                }
            }
        }
    }
    return;
}

void Array_Manipulation(char array[], char value)
{
    int temp;
    for (temp = 0; array[temp] != '\0'; temp++)
    {
        if (array[temp] == value)
        {
            return;
        }
    }
    array[temp] = value;
    array[temp + 1] = '\0';
}