#pragma once
#include <vector>
#include <set>
#include <string>

class Analyzer
{
    public:
        virtual ~Analyzer() {}
        Analyzer();

        void analyze(const std::vector<std::string>& tokens, size_t lineNum);
        virtual void analyzeEnd();

    private:
        void analyzeToken(const std::string& token, size_t lineNum);

        virtual void checkType(const std::string& token, size_t lineNum);
        virtual void checkKeyWords(const std::string& token, size_t lineNum);
        virtual void checkOperators(const std::string& token, size_t lineNum);
        virtual void checkBrackets(const std::string& token, size_t lineNum);
        virtual void checkVar(const std::string& token, size_t lineNum);

        void checkIfElse(const std::string& token, size_t lineNum);
        void checkMain(const std::string& token, size_t lineNum);
        void checkRound(const std::string& token, size_t lineNum);
        void checkSquare(const std::string& token, size_t lineNum);
        void checkCurly(const std::string& token, size_t lineNum);
        void checkPlus(const std::string& token, size_t lineNum);
        void checkMinus(const std::string& token, size_t lineNum);
        bool isTypeDeclared(const std::string& token, size_t lineNum);
        bool isNameValid(const std::string& token) const;

        void clearPlusMinus() { m_plus = 0; m_minus = 0; }
        void clearCounters();

        std::set<std::string> m_predTypes;
        std::set<std::string> m_keyWords;
        std::set<std::string> m_operators;
        std::set<std::string> m_delimeters;

        static std::string predTypes[];
        static std::string keyWords[];
        static std::string operators[];
        static std::string delimeters[];

        std::set<std::string> m_varTable;

        //counters
        bool m_firstToken;
        bool m_type;
        int m_ifElse;
        int m_plus;
        int m_minus;
        int m_round;     //()
        int m_square;    //[]
        int m_curly;     //{}  

        Analyzer(const Analyzer& a);
        Analyzer& operator=(const Analyzer& a);
};