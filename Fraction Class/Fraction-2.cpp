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
/*This program is to create an abstract data type that is robust enough to handle most common operators.
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
using namespace std;

class Fraction{
private:
	long int num;
	long int den;
public:
	// function Name::Function()
	// Parameters: 
	/**/
	// function Name::Fraction()
	// Parameters: long int num = 0, long int den = 1. Two long ints with default values. To cover the numerator and denominator of our fraction.
	/* This is our default Fraction constructor. Default values are num = 0, and den = 1 thus creating a 0/1 fraction.
	This also checks if the denominator is negative, if so it multiples num and den by -1 to flip their signs.
	Thus only the numerator can be negative and represent the sign of the entire fraction.*/
	Fraction(long int num = 0, long int den = 1):num(num), den(den){
		if (den < 0)
		{
			//changing a negative den to positive, by doing so we change the num's sign.
			this->den = den * -1;
			this->num = num * -1;
		}

	}
	// function Name::Fraction()
	// Parameters: long int, the numerator is the concern here.
	/*This is a constructor that expects a singular long int.
	this long int will be used for the numerator and the denominator is hard set to be 1.
	This constructor is thus useful for when we are given a single long int and the logic is that long int is the numerator.*/
	Fraction(long int num) :num(num), den(1) {
	}
	Fraction(const Fraction& a)
	{
		this->setNum(a.getNum());
		this->setDen(a.getDen());
	}	
	// function Name::operator=
	// Parameters: Fraction, the fraction we want to copy.
	/*This is a copy assignment operator.
	We are copying the values from a fraction (a) and storing the values in the Fraction that called this method.*/
	Fraction operator=(const Fraction& a)
	{
		if (this != &a) { // self-assignment check
			this->setNum(a.getNum());
			this->setDen(a.getDen());
		}
		return *this;
	}
	// function Name::~Fraction()
	// Parameters: none
	/*Default constructor. No dynamic allocation to worry about deleting so this is empty.*/
	~Fraction() {
	}
	// function Name::setNum()
	// Parameters: long int a.
	/*mutator function, sets the member variable num to the value of a.*/
	void setNum(long int a)
	{
			num = a;
	}
	// function Name::getNum()
	// Parameters: none
	/*accessor function,returns a long int that is the value of the member variable num.*/
	long int getNum() const
	{
		return num;
	}
	// function Name::setDen()
	// Parameters: long int a.
	/*mutator function, sets the value of the member varible den to a.
	It has been determined that the numerator will hold the sign value for the fraction,
	thus this check if the denominator is negative, if so it flips the sign for the den and num.*/
	void setDen(long int a)
	{
		if(a < 0)
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
	// function Name::getDen()
	// Parameters: 
	/*accessor function, returns a long int that is the value of the member variable den.*/
	long int getDen() const
	{
		return den;
	}
	// function Name::GCD()
	// Parameters: long int a and long int b. a will initially be the numerator of the fraction and b the denominator.
	/*This is a recursive function provided by Dr. Colmenares.
	It will keep going into it b is 0 in which case a will be the greatest common divisor between the numerator and denominator.*/
	unsigned long int GCD(unsigned long int a, unsigned long int b) {
		return (b == 0) ? a : GCD(b, a % b);
	}
	// function Name::simplify()
	// Parameters: none
	/*this is to be called when we want to simplify our fractions.
	It is done by calling the recursive function GCD and dividing both the numerator and denominator by the GCD value.*/
	void simplify()
	{
		long int gcd = GCD(abs(num), den);
		this->setNum(num / gcd);
		this->setDen(den / gcd);
	}
	// function Name::operator-()
	// Parameters: none
	/*The negation operator, we merely a fraction that is the same as the original fraction except the numerator's sign is switched.*/
	Fraction operator-()
	{
		//return a new fraction with the numerator having the opposite sign.
		Fraction temp;
		temp.setNum(-(this->getNum()));
		temp.setDen(this->getDen());
		temp.simplify();
		return temp;
	}
	// function Name::reciprocal()
	// Parameters: none.
	/*This creates a new Fraction that flips the placement of the numerator and denominator of our fraction.*/
	Fraction reciprocal()
	{
		Fraction temp;
		temp.setNum(this->getDen());
		temp.setDen(this->getNum());
		temp.simplify();
		return temp;
	}
	// function Name::exp()
	// Parameters: an integer to represent the power we are raising our fraction to.
	/*This returns a fraction that is the result of raising the fraction that called this by that number.
	All powers are integers only.
	Negative powers are not implemented
	Power to 0 outputs 1 in fraction terms 1/1.
	postive values call our recursive function exp_recursion to resolve. 
	*/
	Fraction exp(int a) 
	{
		Fraction temp;
		//I assume some kind of recusive function.
		if (a > 0)
		{
			temp = exp_recursion(*this, *this, a);
			temp.simplify();
			return temp;
		}
		else if(a == 0)
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
	// function Name::exp_recursion()
	// Parameters: our intial fraction is c, our running total is fraction b, the power is int a.
	/*This is a recursive method that is tail recursive.
	It'll continue running putting the value to be returned in variable b until the power reaches 1.*/	
	Fraction exp_recursion(Fraction c, Fraction b, int a)
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
	// function Name::double()
	// Parameters: none
	/*returns a double value that is the numerator divided by the denominator.*/
	operator double() const{
		return double(num)/double(den);
	}
	// function Name::operator+()
	// Parameters: Fraction other
	/*Operator overload for addition of fraction + fraction.
	Returns a fraction which shortcuts the math of finding a common deminator and then adding the values of the numerators.*/
	Fraction operator+(Fraction other)
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
	// function Name::operator+()
	// Parameters: long int a
	/*operator overload for addition for a Fraction + long int.
	Returns a fraction that adds to the numerator the value of (the long int * the denominator of the fraction)*/
	Fraction operator+(long int a)
	{
		Fraction temp;
		temp.setNum(this->num + (a * this->getDen()));
		temp.setDen(this->den);
		//simplify temp here.
		temp.simplify();
		return temp;
	}
	// function Name::operator-()
	// Parameters: fraction other
	/*operator overload for subtraction between a fraction and another.
	Returns a fraction that shortcuts the common denominator math and then subtracts the two numerators.*/
	Fraction operator-(Fraction other)
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
	// function Name::operator-()
	// Parameters: long int a
	/*Operator overload for subration between a fraction and a long int.
	returns a fraction that subtracts (long int * the denmoninator) to the numerator of the fraction.*/
	Fraction operator-(long int a)
	{
		Fraction temp;
		temp.setNum(this->num - (a * this->getDen()));
		temp.setDen(this->den);
		//simplify temp here.
		temp.simplify();
		return temp;
	}
	// function Name::operator*()
	// Parameters: Fraction other
	/*operator overload of the multiplication operator between two fractions.
	returns a fraction that multiplies each member variable by the same member variable of the other fraction.*/
	Fraction operator*(Fraction other)
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
	Fraction operator*(long int a)
	{
		Fraction temp;
		temp.setNum(this->getNum() * a);
		temp.setDen(this->getDen());
		temp.simplify();
		return temp;
	}
	// function Name::operator/()
	// Parameters: fraction other
	/*operator overload for the division operator between two fractions.
	returns a fraction that multiplies the num of one fraction by the den of the other fraction, and den of one fraction by the num of the other.*/
	Fraction operator/(Fraction other)
	{
		Fraction temp;
		temp.setNum(this->getNum() * other.getDen());
		temp.setDen(this->getDen() * other.getNum());
		temp.simplify();
		return temp;
	}
	// function Name::operator/()
	// Parameters: long int a
	/*operator overload of division between two fractions.
	returns a fraction that multiplies the long int by the denominator of the fraction.*/
	Fraction operator/(long int a)
	{
		Fraction temp;
		temp.setNum(this->num);
		temp.setDen(this->den * a);
		temp.simplify();
		return temp;
	}
	//these friend methods are all operator overloads.
	//more details will be provided where the definitions exists later in the file.
	friend Fraction operator/(long int a, Fraction b);
	friend Fraction operator+(long int a, Fraction b);
	friend Fraction operator-(long int a, Fraction b);
	friend Fraction operator*(long int a, Fraction b);
	friend ostream& operator<<(ostream& os, Fraction a);
	friend istream& operator>>(istream& in, Fraction& fraction);
	// function Name::operator==()
	// Parameters: fraction b
	/*operator overload of the equality operator between two fractions.
	returns a boolean value, true if both of the member variables of both fractions are equal to their peer in the other fraction.*/
	bool operator==(Fraction& b) const {
		return this->num == b.getNum() && this->den == b.getDen();
	}

	// function Name::operator!=()
	// Parameters: fraction b
	/*operator overload of the inequality oeprator between two fractions.
	returns a boolean value, true if either of the the member variables of both fractions are not equal to their peer in the other fraction.*/
	bool operator!=(Fraction& b) const {
		return !(*this == b);
	}
	// function Name::operator>()
	// Parameters: fraction b
	/*operator overload of the greater than operator between two fractions.
	returns a boolean value, true if fraction a is larger than fraction b.
	this is checked by shortcutting the math for a common denimator between the two fractions and then comparing the numerators.*/
	bool operator>(Fraction& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.
		return ((this->num * b.getDen()) > (b.getNum() * this->den));
	}
	// function Name::operator<()
	// Parameters: fraction b
	/*operator overload of the less than operator between two fractions.
	returns a boolean value, true if fraction a is less than fraction b.
	this is checked by shortcutting the math of the common denominator between the two fractions and then comparing the numerators.*/
	bool operator<(Fraction& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.
		return ((this->num * b.getDen()) < (b.getNum() * this->den));
	}
	// function Name::operator>=()
	// Parameters: fraction b
	/*operator overload of the greater than or equal to operator between two fractions.
	returns a boolean value, true if fraction a is greater than or equal to fraction b.
	this is achieved by calling on the == and > operators and either one returns true.*/
	bool operator>=(Fraction& b) const {
		return ((*this > b) || (*this == b));
	}
	// function Name::operator<=()
	// Parameters: fraction b
	/*operator overload of the less than or equal to operator between two fractions.
	returns a boolean value, true if fraction a is less than or equal to fraction b.
	this is achieved by call on the == and < operators and either one returns true.*/
	bool operator<=(Fraction& b) const {
		return ((*this < b) || (*this == b));
	}
	// function Name::operator==()
	// Parameters: long int b
	/*operator overload of the equality operator between a fraction and a long int.
	returns a bool value, true if fraction a is equal to long int b.
	this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
	bool operator==(long int& b) const {
		return this->num == (b * this->den);
	}

	// function Name::operator!=()
	// Parameters: long int b
	/*operator overload of the inequality operator between a fraction and a long int.
	returns a bool value, true if fraction is not equal to long int b.
	this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
	bool operator!=(long int& b) const {
		return !(*this == b);
	}
	// function Name::operator>()
	// Parameters: long int b
	/*operator overload of the greater than oeprator between a fraction and a long int.
	returns a bool value, true if fraction is greater than long int b.
	this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
	bool operator>(long int& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num) > (b * this->den));
	}
	// function Name::<()
	// Parameters: long int b
	/*operator overload of the less than operator between a fraction and a long int.
	returns a bool value, true if fraction is less than long int b.
	this is achieved by multiplying the long int by the denominator of the fraction then comparing it to the numerator.*/
	bool operator<(long int& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num) < (b * this->den));
	}
	// function Name::>=()
	// Parameters: long int b
	/*operator overload of the greater than or equal to operator between a fraction and a long int.
	returns a bool value, true if the fraction is greater than or equal to the long int b.
	this is achieved by calling the == and > operators for fraction and long int, if either returns true.*/
	bool operator>=(long int& b) const {
		return ((*this > b) || (*this == b));
	}
	// function Name::<=()
	// Parameters: long int b
	/*operator overload of the less than or equal to operator between a fraction and a long int.
	returns a bool value, true if the fraction is less than or equal to the long int b.
	this is achieved by calling the == and < operators for fraction and long int, if either returns true.*/
	bool operator<=(long int& b) const {
		return ((*this < b) || (*this == b));
	}
	//more friend methods, for the equalities of an int and a fraction.
	//proper comments where the code is defined.
	friend bool operator==(long int& b, Fraction& a);
	friend bool operator!=(long int& b, Fraction& a);
	friend bool operator>(long int& b, Fraction& a);
	friend bool operator<(long int& b, Fraction& a);
	friend bool operator>=(long int& b, Fraction& a);
	friend bool operator<=(long int& b, Fraction& a);
};

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
		(f1.getNum() != 0) ? cout << "The reciprocal value of " << f1 << " is " << f1.reciprocal() << endl: cout << "Division by zero.\n";
		(f2.getNum() != 0) ? cout << "The reciprocal value of " << f2 << " is " << f2.reciprocal() << endl: cout << "Division by zero.\n";
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
		catch(...)
		{
			choice = 0;
		}
	}

	return 0;
}
