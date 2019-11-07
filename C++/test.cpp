#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    ifstream myfile;
    myfile.open("111.txt");
    if(myfile.is_open())
    {
        map<string, int> myMap;
        map<string, int>::iterator it;
        string line;

        while(getline(myfile, line))
        {
            stringstream ss(line);
            string word;

            while(getline(ss, word, ' '))
            {
                it = myMap.find(word);
                if(it == myMap.end())
                {
                    myMap[word] = 1;
                }
                else
                {
                    it->second += 1;
                }                
            }
        }
        for(it = myMap.begin(); it != myMap.end(); ++it)
            cout << it->first << " " << it->second << endl;
    }
    myfile.close();
    return 0;
}