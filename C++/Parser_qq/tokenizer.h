#pragma once
#include <vector>
#include <string>

using namespace std;

class Tokenizer
{
    public:
        ~Tokenizer() {}
        Tokenizer() {}

        void tokenize(const string& line, vector<string>& tokens);

    private:
        Tokenizer(const Tokenizer& t);
        Tokenizer& operator=(const Tokenizer& t);
};