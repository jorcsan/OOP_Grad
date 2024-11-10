//CMPS 5543 101 Fall 2024
//Michael Ellerkamp and Jorge Santos
// Instructor: Dr. Colmenares
//OOP Assignment 3
//Create a fraction class using oop.
#include <iostream>
#include <string>
using namespace std;

class Fraction{
private:
	long int num;
	long int den;
public:
	//default constructor.
	Fraction(long int num = 0, long int den = 1):num(num), den(den){
		if (den < 0)
		{
			//changing a negative den to positive, by doing so we change the num's sign.
			this->den = den * -1;
			this->num = num * -1;
		}

	}
	//a solo int becomes int over 1.
	Fraction(long int num) :num(num), den(1) {
	}
	Fraction(const Fraction& a)
	{
		this->setNum(a.getNum());
		this->setDen(a.getDen());
	}
	Fraction operator=(const Fraction& a)
	{
		if (this != &a) { // self-assignment check
			this->setNum(a.getNum());
			this->setDen(a.getDen());
		}
		return *this;
	}
	//deconstructor in case we decide to use it.
	~Fraction() {
	}
	void setNum(long int a)
	{
			num = a;
	}
	long int getNum() const
	{
		return num;
	}
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
	long int getDen() const
	{
		return den;
	}
	unsigned long int GCD(unsigned long int a, unsigned long int b) {
		return (b == 0) ? a : GCD(b, a % b);
	}
	void simplify()
	{
		long int gcd = GCD(abs(num), den);
		this->setNum(num / gcd);
		this->setDen(den / gcd);
	}
	//Fraction negation
	Fraction operator-()
	{
		//return a new fraction with the numerator having the opposite sign.
		Fraction temp;
		temp.setNum(-(this->getNum()));
		temp.setDen(this->getDen());
		temp.simplify();
		return temp;
	}
	Fraction reciprocal()
	{
		Fraction temp;
		temp.setNum(this->getDen());
		temp.setDen(this->getNum());
		temp.simplify();
		return temp;
	}
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
	
	//Fraction c will be the intial fraction, Fraction b will be what we return and starts as a copy of Fraction c.
	//a is how many times we recur.
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
	operator double() const{
		return double(num)/double(den);
	}
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
	//adding Fraction + a scalar
	Fraction operator+(long int a)
	{
		Fraction temp;
		temp.setNum(this->num + (a * this->getDen()));
		temp.setDen(this->den);
		//simplify temp here.
		temp.simplify();
		return temp;
	}
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

	Fraction operator-(long int a)
	{
		Fraction temp;
		temp.setNum(this->num - (a * this->getDen()));
		temp.setDen(this->den);
		//simplify temp here.
		temp.simplify();
		return temp;
	}

	Fraction operator*(Fraction other)
	{
		Fraction temp;
		temp.setNum(this->getNum() * other.getNum());
		temp.setDen(this->getDen() * other.getDen());
		temp.simplify();
//		cout << "\n\n" << temp.getNum() << " " << temp.getDen() <<  "\n\n";
		return temp;
	}
	Fraction operator*(long int a)
	{
		Fraction temp;
		temp.setNum(this->getNum() * a);
		temp.setDen(this->getDen());
		temp.simplify();
		return temp;
	}
	Fraction operator/(Fraction other)
	{
		Fraction temp;
		temp.setNum(this->num * other.den);
		temp.setDen(this->den * other.num);
		temp.simplify();
		return temp;
	}
	Fraction operator/(long int a)
	{
		Fraction temp;
		temp.setNum(this->num);
		temp.setDen(this->den * a);
		temp.simplify();
		return temp;
	}
	friend Fraction operator/(long int a, Fraction b);
	friend Fraction operator+(long int a, Fraction b);
	friend Fraction operator-(long int a, Fraction b);
	friend Fraction operator*(long int a, Fraction b);
	friend ostream& operator<<(ostream& os, Fraction a);
	friend istream& operator>>(istream& in, Fraction& fraction);
	bool operator==(Fraction& b) const {
		return this->num == b.getNum() && this->den == b.getDen();
	}

	// Inequality operator
	bool operator!=(Fraction& b) const {
		return !(*this == b);
	}
	bool operator>(Fraction& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num * b.getDen()) > (b.getNum() * this->den));
	}
	bool operator<(Fraction& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num * b.getDen()) < (b.getNum() * this->den));
	}
	bool operator>=(Fraction& b) const {
		return ((*this > b) || (*this == b));
	}
	bool operator<=(Fraction& b) const {
		return ((*this < b) || (*this == b));
	}
	//now to deal with our scalar, int. Starting with Fraction comparison int.
	//then later as friend methods: int comparison Fraction.
	bool operator==(long int& b) const {
		return this->num == (b * this->den);
	}

	// Inequality operator
	bool operator!=(long int& b) const {
		return !(*this == b);
	}
	bool operator>(long int& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num) > (b * this->den));
	}
	bool operator<(long int& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num) < (b * this->den));
	}
	bool operator>=(long int& b) const {
		return ((*this > b) || (*this == b));
	}
	bool operator<=(long int& b) const {
		return ((*this < b) || (*this == b));
	}
	//these are the friends for int comparison fraction.
	friend bool operator==(long int& b, Fraction& a);
	friend bool operator!=(long int& b, Fraction& a);
	friend bool operator>(long int& b, Fraction& a);
	friend bool operator<(long int& b, Fraction& a);
	friend bool operator>=(long int& b, Fraction& a);
	friend bool operator<=(long int& b, Fraction& a);
};

bool operator==(long int& b, Fraction& a) {
	return a.getNum() == (b * a.getDen());
}

// Inequality operator
bool operator!=(long int& b, Fraction& a) {
	return !(a == b);
}
bool operator>(long int& b, Fraction& a) {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((b * a.getDen()) > (a.getNum()));
}
bool operator<(long int& b, Fraction& a) {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((b * a.getDen()) < (a.getNum()));
}
bool operator>=(long int& b, Fraction& a) {
	return ((b > a) || (b == a));
}
bool operator<=(long int& b, Fraction& a) {
	return ((b < a) || (b == a));
}


Fraction operator+(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum(b.getNum() + (a * b.getDen()));
	temp.setDen(b.getDen());
	temp.simplify();
	return temp;
}
Fraction operator-(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum((a * b.getDen()) - b.getNum());
	temp.setDen(b.getDen());
	temp.simplify();
	return temp;
}
Fraction operator*(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum(b.num * a);
	temp.setDen(b.den);
	temp.simplify();
	return temp;
}
Fraction operator/(long int a, Fraction b)
{
	Fraction temp;
	temp.setNum(b.num);
	temp.setDen(b.den * a);
	temp.simplify();
	return temp;
}
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
istream& operator>>(istream& in, Fraction& a) {
	int num;
	char slash;
	try {
		if (in >> num) {  // Try reading the numerator first
			if (in.peek() == '/') {  // Check if the next character is '/' in >> std::ws && 
				in >> slash;  // Read the '/' character
				int denom;
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
		(f2.getNum() == 0) ? cout << f1 << " (/) " << f2 << " = " << f1 / f2 << endl : cout << "Division by zero.\n";
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Negating both fractions:\n";
		cout << "The negated value of " << f1 << " is " << -f1 << endl;
		cout << "The negated value of " << f2 << " is " << -f2 << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		cout << "Calculating the reciprocal of both fractions:\n";
		(f1.getNum() == 0) ? cout << "The reciprocal value of " << f1 << " is " << f1.reciprocal() << endl: cout << "Division by zero.\n";
		(f2.getNum() == 0) ? cout << "The reciprocal value of " << f2 << " is " << f2.reciprocal() << endl: cout << "Division by zero.\n";
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
			choice == 0;
		}
	}

	return 0;
}
