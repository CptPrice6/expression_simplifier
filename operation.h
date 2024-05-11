// Made by Domantas Petkevicius, student of Vilniaus Universitetas, Matematikos ir Informatikos fakultetas (MIF), domasp902@gmail.com

#ifndef OPERATION_H
#define OPERATION_H

// The Operation class is an abstract base class with a pure virtual function operate().
// It takes two integers and returns an integer pointer as a result. It also has a virtual destructor.
// Derived classes Addition, Subtraction, Multiplication and Division implement operate() function to perform their respective arithmetic operations.
class Operation
{
public:
    virtual int *operate(int a, int b) = 0;
    virtual ~Operation() {}
};

class Addition : public Operation
{
public:
    int *operate(int a, int b) override
    {
        int *result = new int(a + b);
        return result;
    }
};

class Subtraction : public Operation
{
public:
    int *operate(int a, int b) override
    {
        int *result = new int(a - b);
        return result;
    }
};

class Multiplication : public Operation
{
public:
    int *operate(int a, int b) override
    {
        int *result = new int(a * b);
        return result;
    }
};

class Division : public Operation
{
public:
    int *operate(int a, int b) override
    {
        if (b == 0)
        {
            throw new CannotDivideByZero();
        }
        int *result = new int(a / b);
        return result;
    }
};

#endif