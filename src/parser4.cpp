#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <map>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "parser4.h"
#include "stack.h"

using namespace std;

Parser::Parser()
{
    PI = "3.14159265";
    e = "2.71828182";
}



double Parser::parse(string &wyrazenie)
{
//-------------------------------------------------------------------------

    int pos;
    bool ifA3 = false;
    bool ifB3 = false;
    bool ifC3 = false;
    bool ifD3 = false;
    bool ifE3 = false;



   if(wyrazenie[0]=='-')
            wyrazenie.insert(0,"0");
    else if(wyrazenie[0] == '.')
        wyrazenie.insert(0,"0");



    for (unsigned int i = 0; i < wyrazenie.length() - 1; ++i)
    {

       if(ifSpacja(wyrazenie[i]))
       {
            wyrazenie.erase(i,1);
            parse(wyrazenie);
       }
       if (ifCyfra(wyrazenie[i]) && ifLewyNaw(wyrazenie[i+1]))
            wyrazenie.insert(i+1, "*");

        else if (ifPrawyNaw(wyrazenie[i]) && (wyrazenie[i+1]=='.' || ifLewyNaw(wyrazenie[i+1])))
            wyrazenie.insert(i+1, "*");




	    else if(ifLewyNaw(wyrazenie[i]) && wyrazenie[i+1] == '-' )
            wyrazenie.insert(i+1,"0");
        else if(!ifCyfra(wyrazenie[i]) && wyrazenie[i+1] == '.' )
            wyrazenie.insert(i+1,"0");
    }


     while((pos=wyrazenie.find("pi")) != -1)
     {
         wyrazenie.replace(pos, 2,PI);
     }
     while((pos=wyrazenie.find("e")) != -1)
     {
         wyrazenie.replace(pos, 2,e);
     }

     if((pos=wyrazenie.find("=")) == 1)
     {

         if((pos=wyrazenie.find("a")) == 0)
         {
            ifA3=true;
            wyrazenie.erase(0,2);
         }
         else if((pos=wyrazenie.find("b")) == 0)
         {
             ifB3=true;
             wyrazenie.erase(0,2);
         }
         else if((pos=wyrazenie.find("c")) == 0)
         {
             ifC3=true;
             wyrazenie.erase(0,2);
         }
         else if((pos=wyrazenie.find("d")) == 0)
         {
             ifD3=true;
             wyrazenie.erase(0,2);
         }
         else if((pos=wyrazenie.find("f")) == 0)
         {
             ifE3=true;
             wyrazenie.erase(0,2);
         }

     }

    else
    {


        while ((pos=wyrazenie.find("a")) != -1)
        {

            wyrazenie.replace(pos, 1,a1);

        }

        while ((pos=wyrazenie.find("b")) != -1)
        {

            wyrazenie.replace(pos, 1,b1);

        }

        while ((pos=wyrazenie.find("c")) != -1)
        {

            wyrazenie.replace(pos, 1,c1);
        }

        while ((pos=wyrazenie.find("d")) != -1)
        {

            wyrazenie.replace(pos, 1,d1);
        }

        while ((pos=wyrazenie.find("f")) != -1)
        {

            wyrazenie.replace(pos, 1,e1);
        }
    }



    Stack<char> S;
    string wynik;
    unsigned int i2 = 0;


    while (i2 < wyrazenie.length())
    {
        char c = wyrazenie[i2++];

//wczytywanie cyfry

	   if (ifCyfra(c))
        {

            string n(1, c);
            while (ifCyfra(c = wyrazenie[i2]) || (c=='.'))
            {
                n += c;
                ++i2;
            }

            wynik += n;
            wynik += ' ';
        }




	    else if (ifOper(c))
        {

            if (ifPrior1(c))
            {
                while (!S.empty() && (ifPrior1(S.top()) || ifPrior2(S.top()) || ifPrior3(S.top())))
                {
                    wynik += S.top();
                    wynik += ' ';
                    S.pop();
                }
            }
            if (ifPrior2(c))
            {
                while (!S.empty() && (ifPrior2(S.top()) || ifPrior3(S.top())))
                {
                    wynik += S.top();
                    wynik += ' ';
                    S.pop();
                }
            }
            if (ifPrior3(c))
            {
                while (!S.empty() && ( ifPrior3(S.top())))
                {
                    wynik += S.top();
                    wynik += ' ';
                    S.pop();
                }
            }

            S.push_back(c);
        }



	    else if (ifSpacja(c))
        {

        }




	    else if (ifLewyNaw(c))
        {

            S.push_back(c);
        }
        else if (ifPrawyNaw(c))
        {

            while (!S.empty() && !ifLewyNaw(S.top()))
            {
                wynik += S.top();
                wynik += ' ';
                S.pop();
            }

            S.pop();

        }




	    else
        {

            cout<<"Niepoprawny znak\n"<<endl;

        }
    }



    while (!S.empty())
    {
        wynik += S.top();
        wynik += ' ';
        S.pop();
    }

//-------------------------------------------------------------------------

    string ONP=wynik;



    Stack <double> S1;
    unsigned i3 = 0;
    char c;
    while (i3 < ONP.length())
    {
        c = ONP[i3++];



        if (ifCyfra(c) || c=='.')
        {
            double v = c - '0';
            while (ifCyfra(c = ONP[i3]))
            {
                v *= 10;
                v += c - '0';
                i3++;
            }



		    if((c=ONP[i3++]) == '.')
            {
                double j=10;
                while (ifCyfra(c = ONP[i3]))
                {
                    v+=(c-'0')/(j);
                    j*=10;
                    i3++;
                }
            }

            S1.push_back(v);
        }



        else if (ifOper(c))
        {
            double a = S1.top(); S1.pop();
            double b = S1.top(); S1.pop();

            switch (c)
            {
            case '+':
                S1.push_back(b + a);
                break;
            case '-':
                S1.push_back(b - a);
                break;
            case '*':
                S1.push_back(b * a);
                break;
            case '/':
                S1.push_back(b / a);
                break;
            case '^':
                S1.push_back(pow(b, a));
                break;
            }
        }




	    else if (ifSpacja(c))
        {

        }




		else
        {
            //throw string("Niepoprawny znak!\n");
            cout<<"Niepoprawny znak\n"<<endl;
            break;
        }
    }

   if(ifA3)
   {

      stringstream ss;

      ss << S1.top();
      a1 = ss.str();

   }
   else if(ifB3)
   {
       stringstream ss;
      ss << S1.top();
      b1 = ss.str();
   }
   else if(ifC3)
   {
      stringstream ss;
      ss << S1.top();
      c1 = ss.str();
   }
   else if(ifD3)
   {
       stringstream ss;
      ss << S1.top();
      d1 = ss.str();
   }
   else if(ifE3)
   {
       stringstream ss;
      ss << S1.top();
      e1 = ss.str();
   }


   return S1.top();

//-------------------------------------------------------------------------
}

bool Parser::ifLewyNaw(char c)
{
    return c == '(';
}

bool Parser::ifPrawyNaw(char c)
{
    return c == ')';
}



bool Parser::ifPrior2(char c)
{
    return c == '*' || c == '/';
}

bool Parser::ifPrior1(char c)
{
    return c == '-' || c == '+';
}

bool Parser::ifPrior3(char c)
{
    return c == '^';
}



bool Parser::ifCyfra(char c)
{
    return (c >= '0' && c <= '9');
}

bool Parser::ifOper(char c)
{
    switch (c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
    }

    return false;
}

bool Parser::ifEq(char c)
{
    return c == '=';
}


bool Parser::ifSpacja(char c)
{
    return c == ' ';
}

bool Parser::ifA(char c)
{
   return c == 'a';
}

bool Parser::ifB(char c)
{
   return c == 'b';
}

bool Parser::ifC(char c)
{
   return c == 'c';
}

bool Parser::ifD(char c)
{
   return c == 'd';
}

bool Parser::ifE(char c)
{
   return c == 'e';
}
