#include "parser.h"
#include <iostream>
#include <fstream>

void Parser::parse(const char* fileName)
{
    ifstream file(fileName);
    string line;
    size_t lineNum = 0;

    if(file.is_open())
    {
        while(getline(file, line))
        {
            m_tokenizer.tokenize(line, m_tokens);
            m_analyzer.analyze(m_tokens, lineNum);
            ++lineNum;
        }

        m_analyzer.analyzeEnd();
        file.close();
    }
    else throw string("Unable to open file");
}