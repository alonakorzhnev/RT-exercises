#include "parser.h"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    Parser parser;
    
    for(int i = 1; i < argc; ++i)
    {
        try
        {
            parser.parse(argv[i]);
        }
        catch(std::string& e)
        {
            std::cout << e << std::endl;
        }
    }

    return 0;
}