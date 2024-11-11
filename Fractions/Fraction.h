//CMPS 5543 101 Fall 2024
//Michael Ellerkamp and Jorge Santos
//Instructor: Dr. Colmenares
//OOP Assignment 3
//Create a fraction class using oop.
//**************************************************************
// Assignment #1
// Name: Michael Ellerkamp, and Jorge Santos
// Parallel Programming Date: Date of Submission (M/D/Y)
//**************************************************************
/*Header files for the Fraction class.
This program is to create an abstract data type that is robust enough to handle most common operators.
This ADT will also interact with ints and be able to be expressed as a double.
The typing of the member variables are long ints.
The ADT will handle the following operators. Addition, subtraction, division, multiplication.
Power, reciprocation, inequalities.
Cin and Cout will be overloaded.
We will focus on two kinds of errors. Creating a fraction with a denominator of 0 is considered a severe error and ends the program.
A fraction trying to divide by 0 is a lesser error and produces an error statement instead of the normal statement.
This program will loop to allow users more changes to test out the functionality of the program.*/
//*****************************************************************
#pragma once
#ifndef Fraction_H
#define Fraction_H

#include <iostream>
#include <string>
using namespace std;

class Fraction {
private:
    //num is the numerator of the fraction
    long int num;
    //den is the denominator of the fraction.
    long int den;
public:
    Fraction(long int num = 0, long int den = 1);
    Fraction(long int num);
    Fraction(const Fraction& a);
    Fraction operator=(const Fraction& a);
    ~Fraction();
    void setNum(long int a);
    long int getNum() const;
    void setDen(long int a);
    long int getDen() const;
    unsigned long int GCD(unsigned long int a, unsigned long int b);
    void simplify();
    Fraction operator-();
    Fraction reciprocal();
    Fraction exp(int a);
    Fraction exp_recursion(Fraction c, Fraction b, int a);
    operator double() const;
    Fraction operator+(Fraction other);
    Fraction operator+(long int a);
    Fraction operator-(Fraction other);
    Fraction operator-(long int a);
    Fraction operator*(Fraction other);
    Fraction operator*(long int a);
    Fraction operator/(Fraction other);
    Fraction operator/(long int a);

    friend Fraction operator/(long int a, Fraction b);
    friend Fraction operator+(long int a, Fraction b);
    friend Fraction operator-(long int a, Fraction b);
    friend Fraction operator*(long int a, Fraction b);
    friend ostream& operator<<(ostream& os, Fraction a);
    friend istream& operator>>(istream& in, Fraction& fraction);

    bool operator==(Fraction& b) const;
    bool operator!=(Fraction& b) const;
    bool operator>(Fraction& b) const;
    bool operator<(Fraction& b) const;
    bool operator>=(Fraction& b) const;
    bool operator<=(Fraction& b) const;
    bool operator==(long int& b) const;
    bool operator!=(long int& b) const;
    bool operator>(long int& b) const;
    bool operator<(long int& b) const;
    bool operator>=(long int& b) const;
    bool operator<=(long int& b) const;

    //more friend methods, for the equalities of an int and a fraction.
    //proper comments where the code is defined.
    friend bool operator==(long int& b, Fraction& a);
    friend bool operator!=(long int& b, Fraction& a);
    friend bool operator>(long int& b, Fraction& a);
    friend bool operator<(long int& b, Fraction& a);
    friend bool operator>=(long int& b, Fraction& a);
    friend bool operator<=(long int& b, Fraction& a);


};

#endif