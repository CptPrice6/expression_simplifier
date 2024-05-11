// Made by Domantas Petkevicius, student of Vilniaus Universitetas, Matematikos ir Informatikos fakultetas (MIF), domasp902@gmail.com

#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <iostream>
#include <typeinfo>
#include <exception>

using namespace std;

// This class handles custom and standard exceptions thrown by other classes

class ExceptionHandler
{
public:
    string handleException(exception &err)
    {
        if (typeid(err) == typeid(NotQuoted))
        {
            return err.what();
        }
        else if (typeid(err) == typeid(UnknownSymbols))
        {
            return err.what();
        }
        else if (typeid(err) == typeid(CannotDivideByZero))
        {
            return err.what();
        }
        else if (typeid(err) == typeid(EmptyExpression))
        {
            return err.what();
        }
        else if (typeid(err) == typeid(InvalidExpressionFormating))
        {
            return err.what();
        }
        else if (typeid(err) == typeid(invalid_argument))
        {
            return "There are invalid symbols in the expression";
        }
        else if (typeid(err) == typeid(out_of_range))
        {
            return "Some number is out of range";
        }
        else
        {
            return "Unknown exception occured: " + string(err.what());
        }
    }
};

#endif
