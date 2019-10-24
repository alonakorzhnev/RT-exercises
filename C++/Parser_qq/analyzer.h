#pragma once
#include <vector>
#include <string>

using namespace std;

class Analyzer
{
    public:
        ~Analyzer();
        Analyzer();

        void analyze(vector<string>& tokens, size_t lineNum);
        void analyzeToken(const string& token);

        void checkIfElse(const string& token);
        void checkMain(const string& token);
        void checkVarName(const string& token);
        void checkBrackets(const string& token);
        void checkType(const string& token);
        void checkPlus(const string& token);
        void checkMinus(const string& token);

        void clearCounters();
        void analyzeEnd();

    private:
        vector<string> m_predTypes;
        vector<string> m_keyWords;
        vector<string> m_operators;
        vector<char> m_delimeters;

        vector<string> m_varTable;

        //counters
        bool m_type;
        size_t m_if;
        size_t m_plus;
        size_t m_minus;
        size_t m_round;     //()
        size_t m_square;    //[]
        size_t m_curly;     //{}  

        Analyzer(const Analyzer& a);
        Analyzer& operator=(const Analyzer& a);
};