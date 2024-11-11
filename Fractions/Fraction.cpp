//CMPS 5543 101 Fall 2024
//Michael Ellerkamp and Jorge Santos
// Instructor: Dr. Colmenares
//OOP Assignment 3
//Create a fraction class using oop.
//**************************************************************
// Assignment #1
// Name: Michael Ellerkamp, and Jorge Santos
// Parallel Programming Date: Date of Submission (M/D/Y)
//***************************************************************
/*Implementation file of the Fraction Class.
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

#include <iostream>
#include <string>
#include "Fraction.h"
using namespace std;

// Fraction::Function()
// Parameters: 
/**/
// Fraction::Fraction()
// Parameters: long int num = 0, long int den = 1. Two long ints with default values. To cover the numerator and denominator of our fraction.
/* This is our default Fraction constructor. Default values are num = 0, and den = 1 thus creating a 0/1 fraction.
This also checks if the denominator is negative, if so it multiples num and den by -1 to flip their signs.
Thus only the numerator can be negative and represent the sign of the entire fraction.*/
Fraction::Fraction(long int num, long int den) :num(num), den(den) {
	if (den < 0)
	{
		//changing a negative den to positive, by doing so we change the num's sign.
		this->den = den * -1;
		this->num = num * -1;
	}

}
// Fraction::Fraction()
// Parameters: long int, the numerator is the concern here.
/*This is a constructor that expects a singular long int.
this long int will be used for the numerator and the denominator is hard set to be 1.
This constructor is thus useful for when we are given a single long int and the logic is that long int is the numerator.*/
Fraction::Fraction(long int num) :num(num), den(1) {
}
Fraction::Fraction(const Fraction& a)
{
	this->setNum(a.getNum());
	this->setDen(a.getDen());
}
// Fraction::operator=
// Parameters: Fraction, the fraction we want to copy.
/*This is a copy assignment operator.
We are copying the values from a fraction (a) and storing the values in the Fraction that called this method.*/
Fraction Fraction::operator=(const Fraction& a)
{
	if (this != &a) { // self-assignment check
		this->setNum(a.getNum());
		this->setDen(a.getDen());
	}
	return *this;
}
// Fraction::~Fraction()
// Parameters: none
/*Default constructor. No dynamic allocation to worry about deleting so this is empty.*/
Fraction::~Fraction() {
}
// Fraction::setNum()
// Parameters: long int a.
/*mutator function, sets the member variable num to the value of a.*/
void Fraction::setNum(long int a)
{
	num = a;
}
// Fraction::getNum()
// Parameters: none
/*accessor function,returns a long int that is the value of the member variable num.*/
long int Fraction::getNum() const
{
	return num;
}
// Fraction::setDen()
// Parameters: long int a.
/*mutator function, sets the value of the member varible den to a.
It has been determined that the numerator will hold the sign value for the fraction,
thus this check if the denominator is negative, if so it flips the sign for the den and num.*/
void Fraction::setDen(long int a)
{
	if (a < 0)
	{
		//turning a negative den positive, doing so we change the sign of the num.
		this->num = num * -1;
		this->den = den * -1;
	}
	else
	{
		this->den = a;
	}
}
// Fraction::getDen()
// Parameters: 
/*accessor function, returns a long int that is the value of the member variable den.*/
long int Fraction::getDen() const
{
	return den;
}
// Fraction::GCD()
// Parameters: long int a and long int b. a will initially be the numerator of the fraction and b the denominator.
/*This is a recursive function provided by Dr. Colmenares.
It will keep going into it b is 0 in which case a will be the greatest common divisor between the numerator and denominator.*/
unsigned long int Fraction::GCD(unsigned long int a, unsigned long int b) {
	return (b == 0) ? a : GCD(b, a % b);
}
// Fraction::simplify()
// Parameters: none
/*this is to be called when we want to simplify our fractions.
It is done by calling the recursive function GCD and dividing both the numerator and denominator by the GCD value.*/
void Fraction::simplify()
{
	long int gcd = GCD(abs(num), den);
	this->setNum(num / gcd);
	this->setDen(den / gcd);
}
// Fraction::operator-()
// Parameters: none
/*The negation operator, we merely a fraction that is the same as the original fraction except the numerator's sign is switched.*/
Fraction Fraction::operator-()
{
	//return a new fraction with the numerator having the opposite sign.
	Fraction temp;
	temp.setNum(-(this->getNum()));
	temp.setDen(this->getDen());
	temp.simplify();
	return temp;
}
// Fraction::reciprocal()
// Parameters: none.
/*This creates a new Fraction that flips the placement of the numerator and denominator of our fraction.*/
Fraction Fraction::reciprocal()
{
	Fraction temp;
	temp.setNum(this->getDen());
	temp.setDen(this->getNum());
	temp.simplify();
	return temp;
}
// Fraction::exp()
// Parameters: an integer to represent the power we are raising our fraction to.
/*This returns a fraction that is the result of raising the fraction that called this by that number.
All powers are integers only.
Negative powers are not implemented
Power to 0 outputs 1 in fraction terms 1/1.
postive values call our recursive function exp_recursion to resolve.
*/
Fraction Fraction::exp(int a)
{
	Fraction temp;
	//I assume some kind of recusive function.
	if (a > 0)
	{
		temp = exp_recursion(*this, *this, a);
		temp.simplify();
		return temp;
	}
	else if (a == 0)
	{
		temp.setNum(1);
		temp.setDen(1);
		return temp;
	}
	else
	{
		cout << "Warning: negative powers have not been implemented, returning 1" << endl;
		temp.setNum(1);
		temp.setDen(1);
		return temp;
	}
}
// Fraction::exp_recursion()
// Parameters: our intial fraction is c, our running total is fraction b, the power is int a.
/*This is a recursive method that is tail recursive.
It'll continue running putting the value to be returned in variable b until the power reaches 1.*/
Fraction Fraction::exp_recursion(Fraction c, Fraction b, int a)
{
	if (a == 1)
	{
		return b;
	}
	else
	{
		//uncomment this out when done operator overload multiplication is ready.
		return exp_recursion(c, b * c, a - 1);
	}
}
// Fraction::double()
// Parameters: none
/*returns a double value that is the numerator divided by the denominator.*/
Fraction::operator double() const {
	return double(num) / double(den);
}
// Fraction::operator+()
// Parameters: Fraction other
/*Operator overload for addition of fraction + fraction.
Returns a fraction which shortcuts the math of finding a common deminator and then adding the values of the numerators.*/
Fraction Fraction::operator+(Fraction other)
{
	//multiply the denoms together to create a common denominator.
	//multiply each num by the opposite denom, then add them together.
	//then simplify.
	Fraction temp;
	temp.setNum((this->num * other.getDen()) + (other.getNum() * this->getDen()));
	temp.setDen(this->den * other.getDen());
	//Call simplify on temp here.
	temp.simplify();
	return temp;
}
// Fraction::operator+()
// Parameters: long int a
/*operator overload for addition for a Fraction + long int.
Returns a fraction that adds to the numerator the value of (the long int * the denominator of the fraction)*/
Fraction Fraction::operator+(long int a)
{
	Fraction temp;
	temp.setNum(this->num + (a * this->getDen()));
	temp.setDen(this->den);
	//simplify temp here.
	temp.simplify();
	return temp;
}
// Fraction::operator-()
// Parameters: fraction other
/*operator overload for subtraction between a fraction and another.
Returns a fraction that shortcuts the common denominator math and then subtracts the two numerators.*/
Fraction Fraction::operator-(Fraction other)
{
	//multiply the denoms together to create a common denominator.
	//multiply each num by the opposite denom, then add them together.
	//then simplify.
	Fraction temp;
	temp.setNum((this->num * other.getDen()) - (other.getNum() * this->getDen()));
	temp.setDen(this->den * other.getDen());
	//Call simplify on temp here.
	temp.simplify();
	return temp;
}
// Fraction::operator-()
// Parameters: long int a
/*Operator overload for subration between a fraction and a long int.
returns a fraction that subtracts (long int * the denmoninator) to the numerator of the fraction.*/
Fraction Fraction::operator-(long int a)
{
	Fraction temp;
	temp.setNum(this->num - (a * this->getDen()));
	temp.setDen(this->den);
	//simplify temp here.
	temp.simplify();
	return temp;
}
// Fraction::operator*()
// Parameters: Fraction other
/*operator overload of the multiplication operator between two fractions.
returns a fraction that multiplies each member variable by the same member variable of the other fraction.*/
Fraction Fraction::operator*(Fraction other)
{
	Fraction temp;
	temp.setNum(this->getNum() * other.getNum());
	temp.setDen(this->getDen() * other.getDen());
	temp.simplify();
	return temp;
}
// function Name:operator*()
// Parameters: long int a
/*operator overload of multiplication between a fraction and a long int.
returns a fraction that multiplies the numerator by the value of the long int.*/
Fraction Fraction::operator*(long int a)
{
	Fraction temp;
	temp.setNum(this->getNum() * a);
	temp.setDen(this->getDen());
	temp.simplify();
	return temp;
}
// Fraction::operator/()
// Parameters: fraction other
/*operator overload for the division operator between two fractions.
returns a fraction that multiplies the num of one fraction by the den of the other fraction, and den of one fraction by the num of the other.*/
Fraction Fraction::operator/(Fraction other)
{
	Fraction temp;
	temp.setNum(this->getNum() * other.getDen());
	temp.setDen(this->getDen() * other.getNum());
	temp.simplify();
	return temp;
}
// Fraction::operator/()
// Parameters: long int a
/*operator overload of division between two fractions.
returns a fraction that multiplies the long int by the denominator of the fraction.*/
Fraction Fraction::operator/(long int a)
{
	Fraction temp;
	temp.setNum(this->num);
	temp.setDen(this->den * a);
	temp.simplify();
	return temp;
}
// Fraction::operator==()
// Parameters: fraction b
/*operator overload of the equality operator between two fractions.
returns a boolean value, true if both of the member variables of both fractions are equal to their peer in the other fraction.*/
bool Fraction::operator==(Fraction& b) const {
	return this->num == b.getNum() && this->den == b.getDen();
}

// Fraction::operator!=()
// Parameters: fraction b
/*operator overload of the inequality oeprator between two fractions.
returns a boolean value, true if either of the the member variables of both fractions are not equal to their peer in the other fraction.*/
bool Fraction::operator!=(Fraction& b) const {
	return !(*this == b);
}
// Fraction::operator>()
// Parameters: fraction b
/*operator overload of the greater than operator between two fractions.
returns a boolean value, true if fraction a is larger than fraction b.
this is checked by shortcutting the math for a common denimator between the two fractions and then comparing the numerators.*/
bool Fraction::operator>(Fraction& b) const {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.
	return ((this->num * b.getDen()) > (b.getNum() * this->den));
}
// Fraction::operator<()
// Parameters: fraction b
/*operator overload of the less than operator between two fractions.
returns a boolean value, true if fraction a is less than fraction b.
this is checked by shortcutting the math of the common denominator between the two fractions and then comparing the numerators.*/
bool Fraction::operator<(Fraction& b) const {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.
	return ((this->num * b.getDen()) < (b.getNum() * this->den));
}
// Fraction::operator>=()
// Parameters: fraction b
/*operator overload of the greater than or equal to operator between two fractions.
returns a boolean value, true if fraction a is greater than or equal to fraction b.
this is achieved by calling on the == and > operators and either one returns true.*/
bool Fraction::operator>=(Fraction& b) const {
	return ((*this > b) || (*this == b));
}
// Fraction::operator<=()
// Parameters: fraction b
/*operator overload of the less than or equal to operator between two fractions.
returns a boolean value, true if fraction a is less than or equal to fraction b.
this is achieved by call on the == and < operators and either one returns true.*/
bool Fraction::operator<=(Fraction& b) const {
	return ((*this < b) || (*this == b));
}
// Fraction::operator==()
// Parameters: long int b
/*operator overload of the equality operator between a fraction and a long int.
returns a bool value, true if fraction a is equal to long int b.
this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
bool Fraction::operator==(long int& b) const {
	return this->num == (b * this->den);
}

// Fraction::operator!=()
// Parameters: long int b
/*operator overload of the inequality operator between a fraction and a long int.
returns a bool value, true if fraction is not equal to long int b.
this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
bool Fraction::operator!=(long int& b) const {
	return !(*this == b);
}
// Fraction::operator>()
// Parameters: long int b
/*operator overload of the greater than oeprator between a fraction and a long int.
returns a bool value, true if fraction is greater than long int b.
this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
bool Fraction::operator>(long int& b) const {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((this->num) > (b * this->den));
}
// Fraction::operator<()
// Parameters: long int b
/*operator overload of the less than operator between a fraction and a long int.
returns a bool value, true if fraction is less than long int b.
this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
bool Fraction::operator<(long int& b) const {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((this->num) < (b * this->den));
}
// Fraction::operator>=()
// Parameters: long int b
/*operator overload of the greater than or equal to operator between a fraction and a long int.
returns a bool value, true if the fraction is greater than or equal to the long int b.
this is achieved by calling the == and > operators for fraction and long int, if either returns true.*/
bool Fraction::operator>=(long int& b) const {
	return ((*this > b) || (*this == b));
}
// Fraction::operator<=()
// Parameters: long int b
/*operator overload of the less than or equal to operator between a fraction and a long int.
returns a bool value, true if the fraction is less than or equal to the long int b.
this is achieved by calling the == and < operators for fraction and long int, if either returns true.*/
bool Fraction::operator<=(long int& b) const {
	return ((*this < b) || (*this == b));
}