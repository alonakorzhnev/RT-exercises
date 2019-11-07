#include <iostream>
#include <string>

using namespace std;

char* matrix(char* sumCol, char* sumRow, int N)
{
    char* result = new char[N*2 + 1];

    for(int i = 0; i < N; i++)
    {
        if(sumCol[i] == 2)
        {
            result[i] = '1';
            --sumRow[0];
            result[i + N] = '1';
            --sumRow[1];
        }
        else if(sumCol[i] == 0)
        {
            result[i] = '0';
            result[i + N] = '0';           
        }
    }

    for(int i = 0; i < N; i++)
    {
        if(sumCol[i] == 1)
        {
            if(sumRow[0] > 0)
            {
                result[i] = '1';
                --sumRow[0];
                result[i + N] = '0';               
            }
            else if(sumRow[1] > 0)
            {
                result[i] = '0';
                result[i + N] = '1';
                --sumRow[1];                
            }
            else
            {
                cout << "Error" << endl;
                delete[] result;
                return 0;
            }            
        }      
    }
    result[2*N] = '\0';
    return result;
}

int main()
{
    char sumCol[5] = {2, 0, 1, 1, 2};
    char sumRow[2] = {3, 3};

    char* result = matrix(sumCol, sumRow, 5);
    cout << result << endl;

    return 0;
}