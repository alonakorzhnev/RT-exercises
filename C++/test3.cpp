#include <iostream>
#include <cstring>

using namespace std;

void string1(char* str)
{
    int j = 0, count = 0;
    int size = strlen(str);

    for(int i = 1; i < size; i++)
    {
        if(str[j] == str[i])
        {
            char tmp = str[i];
            count = 2;
            while(str[++i] != '\0' && str[i] == tmp)
            {
                count++;
            }
            if(count >= 3)
            {
                j += 2;
                str[j] = str[i];
            }else
            {
                j = i;
            }
                       
        }else
        {   
            j = i;      
            
        }  
    }

    str[++j] = '\0';
}

int main()
{
    char str[8] = {'b', 'a', 'a', 'a', 'b', 'a', 'b', '\0'};
    string1(str);
    cout << str << endl;
    return 0;
}