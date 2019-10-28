#pragma once
#include <queue>
#include <string>

class Tokenizer
{
    public:
        ~Tokenizer() {}
        Tokenizer() {}

        void tokenize(const std::string& line, std::queue<std::string>& tokens) const;

        static std::string& getDelimeters() { return m_delimeters; }
        static void setDelimeters(const std::string& del) { m_delimeters = del; } 

    private:
        Tokenizer(const Tokenizer& t);
        Tokenizer& operator=(const Tokenizer& t);

        static std::string      m_delimeters;
};