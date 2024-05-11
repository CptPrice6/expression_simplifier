# Made by Domantas Petkevicius, student of Vilniaus Universitetas, Matematikos ir Informatikos fakultetas (MIF), domasp902@gmail.com

# To avoid unnecessary compilations of other .cpp files, all classes are in .h files and are included in main.cpp for simplicity!

# Please provide in.txt as command line argument, as it is SAFER, than inputting through console!

# in.txt has already all cases to show that program can handle every case :

## "((5+2)))" --> there is extra closing parenthesis

## "(((5+2))" --> there is extra opening parenthesis

## "(5asdasf + 3) \* 2 - 4" --> has unknown symbols

## """" --> invalid formatting

## "" --> empty expression

## --> empty line

## other lines are complex expressions to test the robustness of the program

## I tested many different complex expressions and program tends to simplify them all correctly!

# COMPLETED REQUIREMENTS :

## All requirements have been met :

### Input can be provided with command line arguments and with input

### All results are sent to stdout and out.txt which is constant

### For each valid expression --> single number is written

### For empty line --> empty line is written

### For each empty expression ("") --> "" is written

### For different invalid expressions CUSTOM exceptions are thrown, handled and a CUSTOM error message is displayed

### EVERY variable is artificially dynamically allocated and deleted afterwards

### EVERY class has destructor and is destroyed

### The program is based on classes and OOP principles

### The program is split among different files

### All classes have documentation and all complex parts are commented!
