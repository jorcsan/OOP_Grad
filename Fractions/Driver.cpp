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
/*Driver program for the project.
Implementation file of the Fraction Class.
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
#include "Fraction.h""
using namespace std;


// function Name::operator==()
// Parameters: long int b, fraction a
/*operator overload of the equality oeprator between a long int and a fraction.
this returns a bool value, true if long int a = fraction b.
this is achieved by multiplying the long int by the denominator of the fraction then comparing to the numerator.*/
bool operator==(long int& b, Fraction& a) {
	return a.getNum() == (b * a.getDen());
}
// function Name::operator!=()
// Parameters: long int b, fraction a
/*operator overlaod of the inequality operator between a long int and a fraction.
this returns a bool value, true if long int a != fraction b.
this is achieved by multiplying the long int by the denominator of the fraction then comparing to the numerator.*/
bool operator!=(long int& b, Fraction& a) {
	return !(a == b);
}
// function Name::operator>()
// Parameters: long int b, fraction a
/*operator overload of the greater than operator between a long int and a fraction
this returns a bool value, true if long int a is greater than fraction b.
this is acehieved by multiplying the long int by the denominator of the fraction then comparing the two.*/
bool operator>(long int& b, Fraction& a) {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((b * a.getDen()) > (a.getNum()));
}
// function Name::operator<()
// Parameters: long int b, fraction a.
/*operator overload of the less than operator btween a long int and a fraction.
this returns a bool value, true if long int a is less than fraction b.
this is achieved by multiplying the long int by the denominator of the fraction then comapring the two.*/
bool operator<(long int& b, Fraction& a) {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((b * a.getDen()) < (a.getNum()));
}
// function Name::operator>=()
// Parameters: long int b, fraction a
/*opreator overload of the greater than or equal to operator between a long int and a fraction.
this returns a bool value, true if long int a is greater than or equal to fraction b.
this is achieved by calling the == and > operators for a long int and a fraction, if either returns true.*/
bool operator>=(long int& b, Fraction& a) {
	return ((b > a) || (b == a));
}
// function Name::operator<=()
// Parameters: long int b, fraction a
/*opreator overload of the less than or equal to operator between a long int and a fraction.
this returns a bool value, true if long int a is less than or equal to fraction b.
this is achieved by calling the == and < operators for a long int and a fraction, if either returns true.*/
bool operator<=(long int& b, Fraction& a) {
	return ((b < a) || (b == a));
}
// function Name::operator+()
// Parameters: long int a, faction b
/*operator overload of the addition operator between a long int and a fraction.
this returns a fraction that adds (the long int a * the denominator) to the numerator of the fraction.*/
Fraction operator+(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum(b.getNum() + (a * b.getDen()));
	temp.setDen(b.getDen());
	temp.simplify();
	return temp;
}
// function Name::operator-()
// Parameters: long int a, fraction b.
/*operator overload of the addition oeprator between a long int and a fraction.
this returns a fraction that subtracts from (the long int a * the denominator) by the numerator of the fraction.*/
Fraction operator-(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum((a * b.getDen()) - b.getNum());
	temp.setDen(b.getDen());
	temp.simplify();
	return temp;
}
// function Name::operator*()
// Parameters: long int a, fraction b.
/*operator overload of the multiplication operator between a long int and a fraction.
this returns a fraction that multiplies the numerator by (the long int * the denominator of the fraction)*/
Fraction operator*(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum(b.num * a);
	temp.setDen(b.den);
	temp.simplify();
	return temp;
}
// function Name::operator/()
// Parameters: long int a, fraction b.
/*operator overload of the division operator between a long int a, and fraction b.
this returns a fraction that multiplies the long int by the denominator and sets the b numerator to be the new denominator.*/
Fraction operator/(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum(a * b.getDen());
	temp.setDen(b.getNum());
	temp.simplify();
	return temp;
}
// function Name::operator<<()
// Parameters: ostream, fraction a
/*operator overload of the cout operator for a fraction.
this add our desired statements to the ostream.
if our denominator is 1, then we output only the numerator of our fraction.
if our denonminator is not 1, we output the numerator a slash and then our denominator.*/
ostream& operator<<(ostream& os, Fraction a)
{
	a.simplify();
	if (a.getDen() == 1) {
		os << a.getNum();
	}
	else {
		os << a.getNum() << '/' << a.getDen();
	}
	return os;
}
// function Name::operator>>()
// Parameters: istream in and fraction a.
/*overload of the cin operator for fractions.
this takes in data from the istream and uses it to create a fraction.
if the intanked data is a single long int then we set the value of the new fraction numerator to it and the denom to 1.
if we have a long int, a slash, and then another long int, we set the first long int to the numerator and the second to the denominator.
if a 0 is ever given to the denominator we exit the program with a strong error message.
any other inputs are bad inputs and produce a small error and a fraction that is 0.*/
istream& operator>>(istream& in, Fraction& a) {
	long int num;
	char slash;
	try {
		if (in >> num) {  // Try reading the numerator first
			if (in.peek() == '/') {  // Check if the next character is '/' in >> std::ws && 
				in >> slash;  // Read the '/' character
				long int denom;
				if (in >> denom) {  // Now read the denominator
					if (denom != 0) {  // Validate that the denominator is not zero
						a.setNum(num);
						a.setDen(denom);
						a.simplify();
					}
					else {
						cout << "Fraction Error 2: Illegal rational number.";
						exit(0);  // Denominator can't be zero
					}
				}
				else {
					throw(404);  // Invalid input for denominator
				}
			}
			else {
				// No '/' character found, so treat it as a single integer
				a.setNum(num);
				a.setDen(1);  // Default the denominator to 1
			}
		}
		else {
			throw(404);
		}

		return in;
	}
	catch (...)
	{
		cin.clear();
		cin.ignore();
		cout << "Error: not a number.\nFraction value will be set to 0.\n";
		a.setNum(0);
		a.setDen(1);
		return in;
	}
}

int main() {

	Fraction f1, f2;
	int power;
	int choice = 1;
	while (choice != 0)
	{
		cout << "Please enter you fractions as 'A/B' without quotes then --> Enter.\n";
		cout << "All fractions will automatically be simplified.\n";
		cout << "Example: Numerator/Denominator: 1/2\n";
		cout << "Numerator/Denominator: ";
		cin >> f1;
		cout << "\nNumerator/Denominator: ";
		cin >> f2;

		cout << "\n----------------------------------------------------------------------------------------\n";
		cout << "Converting both fractions into double:\n";
		cout << f1 << " Converted to double  is: " << double(f1) << endl;
		cout << f2 << " Converted to double  is: " << double(f2) << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Adding both fractions:\n";
		cout << f1 << " (+) " << f2 << " = " << f1 + f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Subtracting both fractions:\n";
		cout << f1 << " (-) " << f2 << " = " << f1 - f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Multiplying both fractions:\n";
		cout << f1 << " (*) " << f2 << " = " << f1 * f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Dividing both fractions:\n";
		(f2.getNum() != 0) ? cout << f1 << " (/) " << f2 << " = " << f1 / f2 << endl : cout << "Division by zero.\n";
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Negating both fractions:\n";
		cout << "The negated value of " << f1 << " is " << -f1 << endl;
		cout << "The negated value of " << f2 << " is " << -f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Calculating the reciprocal of both fractions:\n";
		(f1.getNum() != 0) ? cout << "The reciprocal value of " << f1 << " is " << f1.reciprocal() << endl : cout << "Division by zero.\n";
		(f2.getNum() != 0) ? cout << "The reciprocal value of " << f2 << " is " << f2.reciprocal() << endl : cout << "Division by zero.\n";
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Checking if fractions are equal:\n";
		(f1 == f2) ? cout << "Fractions are equal" : cout << "Fractions are not equal" << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Checking if fractions are different:\n";
		(f1 != f2) ? cout << "Fractions are different\n" : cout << "Fractions are not different\n";
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Checking if fraction (A) is less than fraction (b):\n";
		cout << f1 << " is ";
		(f1 < f2) ? cout << "" : cout << "not ";
		cout << "less than " << f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Checking if fraction (A) is less than or equal to fraction (b):\n";
		cout << f1 << " is ";
		(f1 <= f2) ? cout << "" : cout << "not ";
		cout << "less than or equal to " << f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Checking if fraction (A) is greater than fraction (b):\n";
		cout << f1 << " is ";
		(f1 > f2) ? cout << "" : cout << "not ";
		cout << "greater than " << f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Checking if fraction (A) is greater than or equal to fraction (b):\n";
		cout << f1 << " is ";
		(f1 >= f2) ? cout << "" : cout << "not ";
		cout << "greater than or equal to " << f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Assigning new values to the fractions.\n";
		cout << "Please assign a new value for Fraction A:\n";
		//copying the original values of f1 and f2 to use for output soon.
		Fraction f3(f1), f4(f2);
		cout << "Numerator/Denominator: ";
		cin >> f1;
		cout << "\nPlease assign a new value for Fraction B:\n";
		cout << "Numerator/Denominator: ";
		cin >> f2;
		cout << "\nPrevious value for (a) was: " << f3 << "--> New value for (a) is: " << f1 << endl;
		cout << "\nPrevious value for (b) was: " << f4 << "--> New value for (a) is: " << f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Fractions to the power of i:\nPlease enter the power value of i:\n";
		cin >> power;
		cout << f1 << " to the power of " << power << " is " << f1.exp(power) << endl;
		cout << f2 << " to the power of " << power << " is " << f2.exp(power) << endl;
		cout << "========================================================================================\n";
		cout << "Would you like to start over? Yes --> any input other than 0; No --> 0\n";
		cin >> choice;
		try {
			(choice == 0) ? choice = 0 : choice = 1;
		}
		catch (...)
		{
			choice = 0;
		}
	}

	return 0;
}
