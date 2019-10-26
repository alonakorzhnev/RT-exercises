#pragma once
#include "analyzer.h"
#include "tokenizer.h"
#include <vector>
#include <string>

using namespace std;

class Parser
{
    public:
        ~Parser() {}
        Parser() {}

        void parse(const char* fileName);

    private:
        Tokenizer       m_tokenizer;
        Analyzer        m_analyzer;
        vector<string>  m_tokens;

        Parser(const Parser& p);
        Parser& operator=(const Parser& p);
};
