#include "tokenizer.h"
#include <sstream>
#include <cctype>
#include <iostream>

using namespace std;

string Tokenizer::m_delimeters = "()[]{};<>=+-*& \n\t\v\f\r";

void Tokenizer::tokenize(const string& line, vector<string>& tokens)
{
    size_t start = 0;
    size_t found = line.find_first_of(m_delimeters);
    tokens.clear();
    
    while(found != string::npos)
    {
        string token = line.substr(start, found - start);
        start = found + 1;

        tokens.push_back(token);

        char delim = line[found];
        if(!isspace(line[found]))
        {
            string str = "";
            str += delim;
            tokens.push_back(str);
        }

        found = line.find_first_of(m_delimeters, start);
    }
}