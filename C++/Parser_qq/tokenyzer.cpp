#include "tokenyzer.h"
#include <sstream>
#include <cctype>

void Tokenyzer::tokenyze(const string& line, vector<string>& tokens)
{
    string delimeters("()[]{};<>=+-*& \\n\\t\\v\\f\\r");
    size_t found = line.find_first_of(delimeters);
    istringstream ss(line);
    string token;
    
    while(found != string::npos)
    {
        char delim = line[found];
        getline(ss, token, delim);
        tokens.push_back(token);

        if(!isspace(delim))
        {
            tokens.push_back(delim);
        }

        found = line.find_first_of(delimeters, found + 1);
    }
}