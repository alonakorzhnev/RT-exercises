#pragma once
#include <vector>
#include <string>

using namespace std;

class Analyzer
{
    public:
        ~Analyzer() {}
        Analyzer();

        void analyze(vector<string>& tokens, size_t lineNum);
        void analyzeEnd();

    private:
        void analyzeToken(const string& token, size_t lineNum);

        void checkIfElse(const string& token, size_t lineNum);
        void checkMain(const string& token, size_t lineNum);
        void checkVar(const string& token, size_t lineNum);
        void checkRound(const string& token, size_t lineNum);
        void checkSquare(const string& token, size_t lineNum);
        void checkCurly(const string& token, size_t lineNum);
        void checkType(const string& token, size_t lineNum);
        void checkPlus(const string& token, size_t lineNum);
        void checkMinus(const string& token, size_t lineNum);

        void clearPlusMinus() { m_plus = 0; m_minus = 0; }
        void clearCounters();

        vector<string> m_predTypes;
        vector<string> m_keyWords;
        vector<string> m_operators;
        vector<string> m_delimeters;

        vector<string> m_varTable;

        //counters
        bool m_firstToken;
        bool m_type;
        size_t m_ifElse;
        size_t m_plus;
        size_t m_minus;
        size_t m_round;     //()
        size_t m_square;    //[]
        size_t m_curly;     //{}  

        Analyzer(const Analyzer& a);
        Analyzer& operator=(const Analyzer& a);
};