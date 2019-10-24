#pragma once
#include "analyzer.h"
#include "tokenyzer.h"
#include <vector>
#include <string>

using namespace std;

class Parser
{
    public:
        ~Parser() {}
        Parser() {}

        void parseFile(const string& fileName);
        void printTokens();

    private:
        Tokenyzer       m_tokenizer;
        Analyzer        m_analyzer;
        vector<string>  m_tokens;

        Parser(const Parser& p);
        Parser& operator=(const Parser& p);
};
