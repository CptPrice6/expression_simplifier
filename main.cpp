// Made by Domantas Petkevicius, student of Vilniaus Universitetas, Matematikos ir Informatikos fakultetas (MIF), domasp902@gmail.com
// This program simplifies an expression, also throws and handles custom exceptions in case of errors.
// Classes are also destroyed using destructors.
// Is split among multiple files and has multiple classes.

// Tested on Windows 11, 64 bits, Visual Studio Code C++ 14 2024-04-05 and 2024-04-13

#include <iostream>
#include <fstream>

#include "expressionsimplifier.h"

using namespace std;

const string OUT_FILE = "out.txt";

int main(int argc, char *argv[])
{
    ExpressionSimplifier *simplifier = new ExpressionSimplifier();
    ExceptionHandler *exceptionHandler = new ExceptionHandler();
    ifstream *infile;
    ofstream *outfile;

    string *fileName = new string(OUT_FILE);
    outfile = new ofstream(fileName->c_str());
    delete fileName;

    if (argc > 1)
    {
        string *inputFileName = new string(argv[1]);
        infile = new ifstream(inputFileName->c_str());
        delete inputFileName;
        if (!infile->is_open())
        {
            cerr << "Error: Unable to open file\n";
            delete simplifier;
            delete exceptionHandler;
            delete outfile;
            delete infile;
            return EXIT_FAILURE;
        }
    }
    else
    {
        cout << "Please enter the input file:";
        string *inputFileName = new string("");
        getline(cin, *inputFileName);
        infile = new ifstream(inputFileName->c_str());
        delete inputFileName;
        if (!infile->is_open())
        {
            cerr << "Error: Unable to open file\n";
            delete simplifier;
            delete exceptionHandler;
            delete outfile;
            delete infile;
            return EXIT_FAILURE;
        }
    }
    string *line = new string();
    while (getline(*infile, *line))
    {
        string *expression = new string(*line);
        if (expression->empty())
        {
            *outfile << endl;
            cout << endl;
            delete expression;
            continue;
        }
        int *result;
        try
        {
            result = simplifier->simplifyExpression(expression);
        }
        catch (exception &err)
        {
            string exceptionText = exceptionHandler->handleException(err);
            *outfile << exceptionText << endl;
            cout << exceptionText << endl;
            delete expression;
            continue;
        }
        cout << *result << endl;
        *outfile << *result << endl;
        delete expression;
        delete result;
    }
    delete line;

    infile->close();
    outfile->close();

    delete simplifier;
    delete exceptionHandler;
    delete outfile;
    delete infile;

    return 0;
}