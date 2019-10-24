#pragma once
#include <vector>
#include <string>

using namespace std;

class Tokenyzer
{
    public:
        ~Tokenyzer() {}
        Tokenyzer() {}

        void tokenyze(const string& line, vector<string>& tokens);

    private:
        Tokenyzer(const Tokenyzer& t);
        Tokenyzer& operator=(const Tokenyzer& t);
};