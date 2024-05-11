// Made by Domantas Petkevicius, student of Vilniaus Universitetas, Matematikos ir Informatikos fakultetas (MIF), domasp902@gmail.com

#ifndef EXPRESSION_SIMPLIFIER_H
#define EXPRESSION_SIMPLIFIER_H

#include <algorithm>

#include "customexceptions.h"
#include "exceptionhandler.h"
#include "operation.h"

// This class simplifies an expression :
// outputs an integer answer if there are no mistakes or invalid formatting
// outputs "" in case of empty expression.
// outputs new line in case of empty line.
// throws custom exceptions in case of invalid format.
// uses dynamic memory for EVERY variable, even for loops.

// It can simplify any expression that contains +, -, /, *, ().
// Brackets are used for priority.
// Unary negation is also understood.
// It uses integer computation, spaces do not change anything!

class ExpressionSimplifier
{
private:
    Operation *operation;

public:
    ExpressionSimplifier()
    {
        operation = nullptr;
    }

    ~ExpressionSimplifier()
    {
        delete operation;
    }

    int *simplifyExpression(string *expression)
    {
        removeSpaces(expression);
        if (*expression == "\"\"")
        {
            throw EmptyExpression();
        }
        if ((*expression)[0] != '"' || (*expression)[expression->length() - 1] != '"')
        {
            throw NotQuoted();
        }
        expression->erase(0, 1);
        expression->erase(expression->length() - 1, 1);
        // this loop searches for parentheses and simplifies all expressions inside them.
        while (true)
        {
            changeSymbols(expression);
            pair<int *, int *> *locations = findParentheses(expression);
            // if parentheses have not been found break the loop
            if (*locations->first == -1 || *locations->second == -1)
            {
                break;
            }
            else
            {
                string *expressionInParentheses = new string(expression->substr(*locations->first + 1, *locations->second - *locations->first - 1));
                string *simplifiedBit = simplifySpecificBit(expressionInParentheses);
                // constructs a simplified expression with answer in place of those parentheses
                *expression = expression->substr(0, *locations->first) + *simplifiedBit + expression->substr(*locations->second + 1);
                delete expressionInParentheses;
                delete simplifiedBit;
                delete locations->first;
                delete locations->second;
                delete locations;
            }
        }
        // simplifies an expression without parentheses
        *expression = *simplifySpecificBit(expression);

        int *result = new int(stoi(*expression));
        delete expression;
        return result;
    }

    string *simplifySpecificBit(string *expression)
    {
        // looks for invalid formatting
        if ((*expression)[0] == '*' || (*expression)[0] == '/' ||
            (*expression)[expression->length() - 1] == '*' ||
            (*expression)[expression->length() - 1] == '/' ||
            (*expression)[expression->length() - 1] == '+' ||
            (*expression)[expression->length() - 1] == '-')
        {
            throw InvalidExpressionFormating();
        }

        while (expression->find('+') != string::npos || expression->find('-') != string::npos || expression->find('*') != string::npos || expression->find('/') != string::npos)
        {
            changeSymbols(expression);
            bool *isFirstNegative = new bool(false);
            // If only one negative number is left, then it returns it as answer.
            // Also checks if the first number is negative
            // To correctly simplify an expression
            if ((*expression)[0] == '-')
            {
                bool *areAllDigits = new bool(true);
                int *i = new int(1);
                for (*i; *i < expression->length(); (*i)++)
                {
                    if (!isdigit((*expression)[*i]))
                    {
                        *areAllDigits = false;
                    }
                }
                if (*areAllDigits)
                {
                    break;
                }
                else
                {
                    *isFirstNegative = true;
                }
                delete i;
                delete areAllDigits;
            }
            // If only one positive number is left, then it returns it as answer.
            else if ((*expression)[0] == '+')
            {
                bool *areAllDigits = new bool(true);
                int *i = new int(1);
                for (*i; *i < expression->length(); (*i)++)
                {
                    if (!isdigit((*expression)[*i]))
                    {
                        *areAllDigits = false;
                    }
                }
                if (*areAllDigits)
                {
                    break;
                }
                delete i;
                delete areAllDigits;
            }

            string *newExpression = new string("");
            int *newI = new int(0);
            int *opCount = new int(0);
            char *c;
            int *i = new int(0);

            for (*i; *i < expression->length(); (*i)++)
            {
                operation = nullptr;
                c = new char((*expression)[*i]);

                if (*i > 0 && (*c == '-' || *c == '+' || *c == '*' || *c == '/'))
                {
                    (*opCount)++;
                }

                if (*c == ' ')
                    continue;
                if (isdigit(*c))
                {
                    *newExpression += *c;
                    (*newI)++;
                    continue;
                }
                pair<int *, int *> *leftAndRightNums;

                // chooses an operation based on symbol
                if (*c == '*')
                {
                    operation = new Multiplication();
                }
                else if (*c == '/')
                {
                    operation = new Division();
                }
                else if (expression->find('*') == string::npos && expression->find('/') == string::npos && *c == '+')
                {
                    operation = new Addition();
                }
                else if (expression->find('*') == string::npos && expression->find('/') == string::npos && *c == '-')
                {
                    operation = new Subtraction();
                }
                // if operation was chosen performs a simplification
                if (operation != nullptr)
                {
                    bool isRightNegative = false;
                    // checks if the right number from the operator is negative
                    if (*c == '*' || *c == '/')
                    {
                        if ((*expression)[(*i) + 1] == '-')
                        {
                            isRightNegative = true;
                            expression->erase((*i) + 1, 1);
                        }
                    }
                    else
                    // skips the first negative sign ( if found )
                    {
                        if (*i == 0)
                        {
                            (*newI)++;
                            *newExpression += *c;
                            continue;
                        }
                    }
                    leftAndRightNums = getLeftAndRightNums(expression, i);
                    int *leftNum = leftAndRightNums->first;
                    int *rightNum = leftAndRightNums->second;
                    int *leftNumLen = new int(*getNumberLength(leftNum));
                    int *rightNumLen = new int(*getNumberLength(rightNum));

                    if (isRightNegative)
                        *rightNum *= (-1);

                    if (*opCount == 1 && *isFirstNegative)
                    {
                        *leftNum *= (-1);
                        (*leftNumLen) += 1;
                    }

                    int *result = operation->operate(*leftNum, *rightNum);
                    // constructs new expression with simplified bit inserted in its place
                    newExpression->erase(*newI - *leftNumLen, *leftNumLen);
                    *newExpression += to_string(*result);
                    *newExpression += expression->substr(*i + *rightNumLen + 1);

                    delete leftNum;
                    delete rightNum;
                    delete leftNumLen;
                    delete rightNumLen;
                    delete result;
                    delete leftAndRightNums->first;
                    delete leftAndRightNums->second;
                    delete leftAndRightNums;
                    delete c;
                    delete i;
                    break;
                }
                if (*c != '+' && *c != '-' && *c != '/' && *c != '*')
                {
                    throw UnknownSymbols();
                }
                else
                {
                    *newExpression += *c;
                    (*newI)++;
                    continue;
                }
                delete c;
            }
            *expression = *newExpression;
            delete newExpression;
            delete newI;
            delete opCount;
        }

        return expression;
    }

    // changes -- to +, -+ and +- to - ,++ to +
    void changeSymbols(string *expression)
    {
        string *newExpression = new string("");
        if ((*expression)[0] == '+' && isdigit((*expression)[1]))
        {
            expression->erase(0, 1);
        }
        char *c;
        int *i = new int(0);
        for (*i; *i < expression->length(); (*i)++)
        {
            c = new char((*expression)[*i]);

            if (*c == '-' && (*expression)[(*i) + 1] == '-')
            {
                *newExpression += '+';
                (*i)++;
                continue;
            }
            else if (*c == '-' && (*expression)[(*i) + 1] == '+')
            {
                *newExpression += '-';
                (*i)++;
                continue;
            }
            else if (*c == '+' && (*expression)[(*i) + 1] == '-')
            {
                *newExpression += '-';
                (*i)++;
                continue;
            }
            else if (*c == '+' && (*expression)[(*i) + 1] == '+')
            {
                *newExpression += '+';
                (*i)++;
                continue;
            }
            else
            {
                *newExpression += *c;
                continue;
            }
            delete c;
        }
        delete i;
        *expression = *newExpression;
        delete newExpression;
    }
    // finds parentheses and returns their locations
    // if parentheses have not been found locations are set to -1
    // returns most nested parentheses locations for correct simplification
    pair<int *, int *> *findParentheses(string *expression)
    {
        int *firstIndex = new int(-1);
        int *secondIndex = new int(-1);
        bool *openingFound = new bool(false);
        char *c;
        int *i = new int(0);

        for (*i; *i < expression->length(); (*i)++)
        {
            c = new char((*expression)[*i]);
            if (*c == '(')
            {
                *openingFound = true;
                *firstIndex = *i;
                continue;
            }
            else if (*c == ')' && !*openingFound)
            {
                delete firstIndex;
                delete secondIndex;
                delete openingFound;
                throw InvalidExpressionFormating();
            }
            else if (*c == ')' && *openingFound)
            {
                *secondIndex = *i;
                break;
            }
            delete c;
        }
        if (*openingFound == true && *secondIndex == -1)
        {
            delete firstIndex;
            delete secondIndex;
            delete openingFound;
            throw InvalidExpressionFormating();
        }

        delete openingFound;
        delete i;
        pair<int *, int *> *locations = new pair<int *, int *>(firstIndex, secondIndex);
        return locations;
    }

    int *getNumberLength(int *number)
    {
        int *length = new int(0);

        int *tempNumber = new int(*number);

        if (*tempNumber == 0)
        {
            return new int(1);
        }
        while (*tempNumber != 0)
        {
            (*length)++;
            *tempNumber /= 10;
        }
        delete tempNumber;

        return length;
    }
    // returns a pair of two numbers to the left and right from the operator sign
    // this allows to simplify expressions with longer numbers
    pair<int *, int *> *getLeftAndRightNums(string *expression, int *i)
    {
        string *leftNumStr = new string("");
        int *start = new int(0);
        for (*start = (*i) - 1; *start >= 0; (*start)--)
        {
            if (isdigit((*expression)[*start]))
            {
                *leftNumStr += (*expression)[*start];
            }
            else
            {
                break;
            }
        }
        reverse(leftNumStr->begin(), leftNumStr->end());
        int *leftNum = new int(stoi(*leftNumStr));
        delete leftNumStr;

        string *rightNumStr = new string("");
        for (*start = (*i) + 1; *start < expression->length(); (*start)++)
        {
            if (isdigit((*expression)[*start]))
            {
                *rightNumStr += (*expression)[*start];
            }
            else
            {
                break;
            }
        }
        delete start;
        int *rightNum = new int(stoi(*rightNumStr));
        delete rightNumStr;
        pair<int *, int *> *nums = new pair<int *, int *>(leftNum, rightNum);
        return nums;
    }
    // removes spaces from expression
    void removeSpaces(string *expression)
    {
        string *newExpression = new string("");
        int *i = new int(0);
        char *c;
        for (*i; *i < expression->length(); (*i)++)
        {
            c = new char((*expression)[*i]);
            if (*c != ' ')
            {
                *newExpression += *c;
            }
            delete c;
        }
        delete i;
        *expression = *newExpression;
        delete newExpression;
    }
};
#endif
