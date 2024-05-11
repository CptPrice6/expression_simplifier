// Made by Domantas Petkevicius, student of Vilniaus Universitetas, Matematikos ir Informatikos fakultetas (MIF), domasp902@gmail.com

#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

using namespace std;

// These classes define custom exceptions

class CannotDivideByZero : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Division by zero is not possible";
    }
};

class UnknownSymbols : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Expression contains unknown symbols";
    }
};

class InvalidExpressionFormating : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Expression format is invalid";
    }
};

class NotQuoted : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Expression is not in quotes";
    }
};
class EmptyExpression : public std::exception
{
public:
    const char *what() const throw()
    {
        return "\"\"";
    }
};
class EmptyLine : public std::exception
{
public:
    const char *what() const throw()
    {
        return "\n";
    }
};

#endif