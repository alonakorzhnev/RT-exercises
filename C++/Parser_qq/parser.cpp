#include "parser.h"
#include <iostream>
#include <fstream>

void Parser::parseFile(const string& fileName)
{
    ifstream file(fileName);
    string line;
    size_t lineNum = 0;

    if(file.is_open())
    {
        while(getline(file, line))
        {
            m_tokenizer.tokenyze(line, m_tokens);
            m_analyzer.analyze(m_tokens, ++lineNum);
        }
        file.close();
    }
    else throw string("Unable to open file");
}

void Parser::printTokens()
{
    
}