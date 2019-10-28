#include "tokenizer.h"
#include <sstream>
#include <cctype>

using namespace std;

string Tokenizer::m_delimeters = "()[]{};<>=+-*& \n\t\v\f\r";

void Tokenizer::tokenize(const string& line, queue<string>& tokens) const
{
    size_t start = 0;
    size_t found = line.find_first_of(m_delimeters);
    
    while(found != string::npos)
    {
        string token = line.substr(start, found - start);
        start = found + 1;
        tokens.push(token);

        char delim = line[found];
        if(!isspace(line[found]))
        {
            string str = "";
            str += delim;
            tokens.push(str);
        }

        found = line.find_first_of(m_delimeters, start);
    }
}