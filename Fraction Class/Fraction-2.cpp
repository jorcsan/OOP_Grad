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
		if (den == 0)
		{
			cout << "Error: Denominator cannot be 0, denom has been set to 1." << endl;
			this->den = 1;
		}
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
		if (a == 0)
		{
			num = a;
			den = 1;
		}
		else
		{
			num = a;
		}
	}
	long int getNum() const
	{
		return num;
	}
	void setDen(long int a)
	{
		if (a == 0)
		{
			cout << "Denominator cannot be 0, denominator set as 1." << endl;
			den = 1;
		}
		else if(a < 0)
		{
			//turning a negative den positive, doing so we change the sign of the num.
			num = num * -1;
			den = den * -1;
		}
		else
		{
			den = a;
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
		int gcd = GCD(abs(num), den);
		num = num / gcd;
		den = den / gcd;
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
					in.setstate(ios::failbit);  // Denominator can't be zero
					std::cerr << "Error: Denominator cannot be zero." << std::endl;
				}
			}
			else {
				in.setstate(ios::failbit);  // Invalid input for denominator
			}
		}
		else {
			// No '/' character found, so treat it as a single integer
			a.setNum(num);
			a.setDen(1);  // Default the denominator to 1
		}
	}
	else {
		in.setstate(ios::failbit);  // Invalid input for numerator
	}

	return in;
}

int main() {

	Fraction f1(2, 4);
	cout << "test 1" << endl;
	Fraction f2(1, 3);
	cout << "test 2" << endl;
//	Fraction f3 = 5 + f2;
//	cout << "test 3" << endl;
	Fraction f4;
//	cin >> f4;
//	cout << f4 << endl;
//	cout << f1 << endl;
//	cout << f2 << endl;
	cout << f1 << endl;
	cout << f1 / f2 << endl;
	cout << f2.reciprocal() << endl;
	cout << "exponent test " << f1.exp(0) << endl;
//	f3 = f1 * f2;
//	cout << f3 << endl;
//	Fraction f5(1,-1);
//	cout << f5 << endl;
	return 0;
}
