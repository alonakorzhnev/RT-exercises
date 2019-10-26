#include "analyzer.h"
#include <iostream>
#include <algorithm>

string predTypes[] = {"char", "short", "int", "long", "float", "double", "void"};
string keyWords[] = {"if", "else", "while", "class", "private", "public", "protected", "main", "const", "virtual"};
string operators[] = {"++", "--", "==", "->", "=", "+", "-", "*", "&", "<<", ">>"};
string delimeters[] = {"(", ")", "[", "]", "{", "}", ";", "<", ">", "=", "+", "-", "*", "&"};

Analyzer::Analyzer() : m_predTypes(predTypes, predTypes + sizeof(predTypes)/sizeof(string)), 
                       m_keyWords(keyWords, keyWords + sizeof(keyWords)/sizeof(string)),
                       m_operators(operators, operators + sizeof(operators)/sizeof(string)),
                       m_delimeters(delimeters, delimeters + sizeof(delimeters)/sizeof(string))
{
    m_firstToken = true;
    m_type = false;
    m_ifElse = 0;
    m_plus = 0;
    m_minus = 0;
    m_round = 0;
    m_square = 0;
    m_curly = 0;
}

void Analyzer::analyze(vector<string>& tokens, size_t lineNum)
{
    for(int i = 0; i < tokens.size(); ++i)
    {
        if(tokens[i] != "")
        {
            analyzeToken(tokens[i], lineNum);
        }
    }
}

void Analyzer::analyzeToken(const string& token, size_t lineNum)
{
    checkMain(token, lineNum);
    checkIfElse(token, lineNum);
    checkMinus(token, lineNum);
    checkPlus(token, lineNum);
    checkRound(token, lineNum);
    checkSquare(token, lineNum);
    checkCurly(token, lineNum);
    checkType(token, lineNum);
    checkVar(token, lineNum);    
}

void Analyzer::checkIfElse(const string& token, size_t lineNum)
{
    if(token == "if")
    {
        ++m_ifElse;
        clearPlusMinus();
    }
    else if(token == "else")
    {
        --m_ifElse;
        clearPlusMinus();
        if(m_ifElse < 0)
        {
            m_ifElse = 0;
            cout << "line " << lineNum << "-error, " << "'else' without 'if'" << endl;
        }
    }
}

void Analyzer::checkMain(const string& token, size_t lineNum)
{
    if(m_firstToken == true && token != "main")
    {
        m_firstToken = false;
        cout << "line " << lineNum << "-error, " << "no 'main before'" << endl;
    }
    else if(m_firstToken == false && token == "main")
    {
        clearPlusMinus();
        cout << "line " << lineNum << "-error, " << "illegal declaration before 'main'" << endl;
    }
}

void Analyzer::checkVar(const string& token, size_t lineNum)
{
    if(find(m_predTypes.begin(), m_predTypes.end(), token) == m_predTypes.end() &&
       find(m_keyWords.begin(), m_keyWords.end(), token) == m_keyWords.end() &&
       find(m_operators.begin(), m_operators.end(), token) == m_operators.end() &&
       find(m_delimeters.begin(), m_delimeters.end(), token) == m_delimeters.end())
    {
        clearPlusMinus();

        if(m_type)
        {
            if(find(m_varTable.begin(), m_varTable.end(), token) == m_varTable.end())
            {
                if(isalpha(token[0]))
                {
                    m_varTable.push_back(token);
                }  
                else
                {
                    cout << "line " << lineNum << "-error, " << "illegal variable name" << endl;
                    return;
                }                                           
            }
            else
            {
                cout << "line " << lineNum << "-error, " << "variable " << token << " already declared" << endl;
                return;
            }  
            m_type = false;          
        }else
        {
            cout << "line " << lineNum << "-error, " << "is not declared" << endl;
        }        
    }
}

void Analyzer::checkRound(const string& token, size_t lineNum)
{
    if(token == "(")
    {
        ++m_round;
        clearPlusMinus();
    }
    else if(token == ")")
    {
        --m_round;
        clearPlusMinus();

        if(m_round < 0)
        {
            m_round = 0;
            cout << "line " << lineNum << "-error, " << "is illegal '(' has to be before ')'" << endl;
        }
    }    
}

void Analyzer::checkSquare(const string& token, size_t lineNum)
{
    if(token == "[")
    {
        ++m_square;
        clearPlusMinus();
    }
    else if(token == "]")
    {
        --m_square;
        clearPlusMinus();

        if(m_square < 0)
        {
            m_square = 0;
            cout << "line " << lineNum << "-error, " << "is illegal '[' has to be before ']'" << endl;
        }
    } 
}

void Analyzer::checkCurly(const string& token, size_t lineNum)
{
    if(token == "{")
    {
        ++m_curly;
        clearPlusMinus();
    }
    else if(token == "}")
    {
        --m_curly;
        clearPlusMinus();

        if(m_curly < 0)
        {
            m_curly = 0;
            cout << "line " << lineNum << "-error, " << "is illegal '{' has to be before '}'" << endl;     
        }
    } 
}

void Analyzer::checkType(const string& token, size_t lineNum)
{
    if(find(m_predTypes.begin(), m_predTypes.end(), token) != m_predTypes.end())
    {
        clearPlusMinus();

        if(m_type)
        {
            m_type = false;
            cout << "line " << lineNum << "-error, " << "error multiple type declaration" << endl;            
            return;
        }

        m_type = true;
    }
}

void Analyzer::checkPlus(const string& token, size_t lineNum)
{
    if(token == "+")
    {
        ++m_plus;
        m_minus = 0;
        if(m_plus == 3)
        {
            m_plus = 0;
            cout << "line " << lineNum << "-error, " << "no operator +++" << endl;
        }
    }
}

void Analyzer::checkMinus(const string& token, size_t lineNum)
{
    if(token == "-")
    {
        ++m_minus;
        m_plus = 0;
        if(m_minus == 3)
        {
            m_minus = 0;
            cout << "line " << lineNum << "-error, " << "no operator ---" << endl;
        }
    }
}

void Analyzer::clearCounters()
{
    m_firstToken = true;
    m_type = false;
    m_ifElse = 0;
    m_plus = 0;
    m_minus = 0;
    m_round = 0;
    m_square = 0;
    m_curly = 0;
}

void Analyzer::analyzeEnd()
{
    if(m_round != 0)
    {
        cout << "error " << m_round << "'(' not closed" << endl; 
    }
    else if(m_square != 0)
    {
        cout << "error " << m_square << "'[' not closed" << endl; 
    }
    else if(m_curly != 0)
    {
        cout << "error " << m_curly << "'{' not closed" << endl; 
    }
}