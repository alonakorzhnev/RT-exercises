#pragma once
#include <queue>
#include <string>

class Tokenizer;
class Analyzer;

class Parser
{
    public:
        ~Parser();
        Parser();

        void parse(const char* fileName);

    private:
        Tokenizer*                  m_tokenizer;
        Analyzer*                   m_analyzer;
        std::queue<std::string>     m_tokens;

        Parser(const Parser& p);
        Parser& operator=(const Parser& p);
};
