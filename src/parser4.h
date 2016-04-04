#ifndef parser4_hpp
#define parser4_hpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <map>
#include <cstdlib>
#include <ctime>
#include "stack.h"

using namespace std;

class Parser
{
    public:
        Parser();

        double parse(string &wyrazenie);




    private:
        string PI;
        string e;
        bool ifLewyNaw(char c);
        bool ifPrawyNaw(char c);
        bool ifPrior1(char c);
        bool ifPrior2(char c);
        bool ifPrior3(char c);
        bool ifCyfra(char c);
        bool ifOper(char c);
        bool ifSpacja(char c);
        bool ifA(char c);
        bool ifB(char c);
        bool ifC(char c);
        bool ifD(char c);
        bool ifE(char c);
        bool ifEq(char c);
        string a1;
        string b1;
        string c1;
        string d1;
        string e1;



};
#endif
