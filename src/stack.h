#ifndef stack_hpp
#define stack_hpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <map>
#include <cstdlib>
#include <ctime>
#include "container.h"

using namespace std;

template <class typ>
class Stack : public Container<typ>
{
    public:
        class Elem
        {

        public:
            Elem();
            typ* Wart();
            Elem* Popr();
            void setWart(typ* newWart);
            void setPopr(Elem* newNast);

        private:
            typ *wart;
            Elem *popr;

        };
        Stack();
        ~Stack();
        int ile_elem() const;
        bool empty();
        void push_back(typ element);
        typ pop();
        typ top();

    private:

        Elem *front;


};

template <class typ>
Stack<typ>::Stack()
{


    front=NULL;
    this->rozm = 0;

}

template <class typ>
Stack<typ>::~Stack()
{
    while(front)
    {
        Elem *tmp = front->Popr();
        if(front->Wart())
            delete front->Wart();
        delete front;
        front = tmp;
    }
}

template <class typ>
int Stack<typ>::ile_elem() const
{

    return this->rozm;

}

template <class typ>
Stack<typ>::Elem::Elem()
{

    popr = NULL;
    wart = NULL;

}


template <class typ>
typename Stack<typ>::Elem* Stack<typ>::Elem::Popr()
{

    return popr;

}


template <class typ>
typ* Stack<typ>::Elem::Wart()
{

    return wart;

}

template <class typ>
void Stack<typ>::Elem::setWart(typ* newWart)
{

    wart = newWart;

}


template <class typ>
void Stack<typ>::Elem::setPopr(Stack<typ>::Elem* newPopr)
{

    popr = newPopr;

}

template <class typ>
void Stack<typ>::push_back(typ element)
{

    Stack<typ>::Elem *p = new Stack<typ>::Elem();
    typ *wskt = new typ(element);
    p->setWart(wskt);
    if(front)
        p->setPopr(front);
    front = p;
    this->rozm++;



}

template <class typ>
typ Stack<typ>::pop()
{
    typ ret;
    if(front)
    {
        ret =  *(front->Wart());
        Elem *tmp = front;
        front=front->Popr();


        if(tmp->Wart())
            delete tmp->Wart();
        delete tmp;
        this->rozm--;
        return ret;

    }

    else
        return 0;
}



template <class typ>
typ Stack<typ>::top()
{

    if (front)
        return *(front->Wart());
    else return 0;


}

template <class typ>
bool Stack<typ>::empty()
{

    return (this->rozm == 0 && this->front ==NULL);
}


#endif
