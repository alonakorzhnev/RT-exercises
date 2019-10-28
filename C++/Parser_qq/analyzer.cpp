#include "analyzer.h"
#include <iostream>
#include <algorithm>

using namespace std;

string Analyzer::predTypes[] = {"char", "short", "int", "long", "float", "double", "void"};
string Analyzer::keyWords[] = {"if", "else", "while", "class", "private", "public", "protected", "main", "const", "virtual"};
string Analyzer::operators[] = {"++", "--", "==", "->", "=", "+", "-", "*", "&", "<<", ">>"};
string Analyzer::delimeters[] = {"(", ")", "[", "]", "{", "}", ";", "<", ">", "=", "+", "-", "*"};

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

void Analyzer::analyze(const vector<string>& tokens, size_t lineNum)
{
    for(int i = 0; i < tokens.size(); ++i)
    {
        if(tokens[i] != "")
            analyzeToken(tokens[i], lineNum);
    }
}

void Analyzer::analyzeToken(const string& token, size_t lineNum)
{
    if(m_firstToken)
        checkMain(token, lineNum);  
    if(m_predTypes.find(token) != m_predTypes.end())
        checkType(token, lineNum);
    else if(m_keyWords.find(token) != m_keyWords.end())
        checkKeyWords(token, lineNum);
    else if(m_operators.find(token) != m_operators.end())
        checkOperators(token, lineNum);
    else if(m_delimeters.find(token) != m_delimeters.end())
        checkBrackets(token, lineNum);
    else
        checkVar(token, lineNum);
}

bool Analyzer::isTypeDeclared(const string& token, size_t lineNum)
{
    if(m_type)
    {
        cout << "line " << lineNum << "-error, " << token << " illegal variable name" << endl;
        m_type = false;
        return true;
    }
    else return false;
}

void Analyzer::checkType(const string& token, size_t lineNum)
{
    clearPlusMinus();
    if(m_type)
    {
        m_type = false;
        cout << "line " << lineNum << "-error, error multiple type declaration" << endl;            
        return;
    }
    m_type = true;
}

void Analyzer::checkKeyWords(const string& token, size_t lineNum)
{
    if(!isTypeDeclared(token, lineNum) && (token == "if" || token == "else"))
        checkIfElse(token, lineNum);
}

void Analyzer::checkOperators(const string& token, size_t lineNum)
{
    if(!isTypeDeclared(token, lineNum))
    {
        if(token == "+")
            checkPlus(token, lineNum);
        else if(token == "-")
            checkMinus(token, lineNum);
    }
}

void Analyzer::checkBrackets(const string& token, size_t lineNum)
{
    clearPlusMinus();
    if(!isTypeDeclared(token, lineNum))
    {
        if(token == "(" || token == ")")
            checkRound(token, lineNum);
        else if(token == "[" || token == "]")
            checkSquare(token, lineNum);
        else if(token == "{" || token == "}")
            checkCurly(token, lineNum);
    }
}

void Analyzer::checkVar(const string& token, size_t lineNum)
{
    clearPlusMinus();
    if(m_type)
    {
        if(m_varTable.find(token) == m_varTable.end())
        {
            if(isNameValid(token))
                m_varTable.insert(token);
            else
                cout << "line " << lineNum << "-error, " << token << " illegal variable name" << endl;                                          
        }
        else
            cout << "line " << lineNum << "-error, variable " << token << " already declared" << endl; 
        m_type = false;          
    }
    else
        cout << "line " << lineNum << "-error, variable " << token << " is not declared" << endl;   
}

bool Analyzer::isNameValid(const string& token) const
{
    return (isalpha(token[0]) || token[0] == '_') ? true : false;
}

void Analyzer::checkIfElse(const string& token, size_t lineNum)
{
    clearPlusMinus();
    if(token == "if")
        ++m_ifElse;
    else if(token == "else")
    {
        --m_ifElse;
        if(m_ifElse < 0)
        {
            m_ifElse = 0;
            cout << "line " << lineNum << "-error, 'else' without 'if'" << endl;
        }
    }
}

void Analyzer::checkMain(const string& token, size_t lineNum)
{
    if(token != "main")
    {
        m_firstToken = false;
        cout << "line " << lineNum << "-error, no 'main' before" << endl;
    }
}

void Analyzer::checkRound(const string& token, size_t lineNum)
{
    if(token == "(")
        ++m_round;
    else if(token == ")")
    {
        --m_round;        
        if(m_round < 0)
        {
            m_round = 0;
            cout << "line " << lineNum << "-error, is illegal '(' has to be before ')'" << endl;
        }
    }    
}

void Analyzer::checkSquare(const string& token, size_t lineNum)
{    
    if(token == "[")
        ++m_square;
    else if(token == "]")
    {
        --m_square;
        if(m_square < 0)
        {
            m_square = 0;
            cout << "line " << lineNum << "-error, is illegal '[' has to be before ']'" << endl;
        }
    } 
}

void Analyzer::checkCurly(const string& token, size_t lineNum)
{
    if(token == "{")
        ++m_curly;
    else if(token == "}")
    {
        --m_curly;
        if(m_curly < 0)
        {
            m_curly = 0;
            cout << "line " << lineNum << "-error, is illegal '{' has to be before '}'" << endl;     
        }
    } 
}

void Analyzer::checkPlus(const string& token, size_t lineNum)
{
    ++m_plus;
    m_minus = 0;
    if(m_plus == 3)
    {
        m_plus = 0;
        cout << "line " << lineNum << "-error, no operator +++" << endl;
    }
}

void Analyzer::checkMinus(const string& token, size_t lineNum)
{
    ++m_minus;
    m_plus = 0;
    if(m_minus == 3)
    {
        m_minus = 0;
        cout << "line " << lineNum << "-error, no operator ---" << endl;
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
        cout << "error " << m_round << "'(' not closed" << endl; 
    if(m_square != 0)
        cout << "error " << m_square << "'[' not closed" << endl; 
    if(m_curly != 0)
        cout << "error " << m_curly << "'{' not closed" << endl; 

    clearCounters();
    m_varTable.clear();
}