#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <cmath>
#include <map>
#include <cstdlib>
#include <ctime>
#include <csignal>
#include "parser4.h"
#include "stack.h"

bool run = true;
static void catch_function(int signo)
{
        run=false;
}

int main()
{

    signal(SIGINT, catch_function);
    string wyrazenie;
    double res;


    cout << "Prosty kalkulator" << endl << endl;
    cout << "Dostepne operacje i stale matematyczne:" << endl;
	cout << "+" "    "<<"-" "    "<<"*" "    "<<"/" "    "<<endl;
	cout << "^" "    "<<"pi" "   "<<"e" "    "<<endl<<endl;
	cout << "Dostepne zmienne do zapisu w pamieci:" << endl;
	cout << "a" "    "<<"b" "    "<<"c" "    "<<"d" "    "<<"f" "    "<<endl<<endl;
	Parser parser;
    while(1)
    {
        cout << "Podaj wyrazenie: ";
        getline(cin, wyrazenie);
        if((int)wyrazenie[0]==0)
            return 0;
        res=parser.parse(wyrazenie);
        cout <<"Wynik: "<< res <<endl << endl;
        if (signal(SIGINT, catch_function) == SIG_ERR)
            {
                fputs("Blad przy czyszczeniu pamieci.\n", stderr);
                return EXIT_FAILURE;
            }

    }
    return 0;
}
