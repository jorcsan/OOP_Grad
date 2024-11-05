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
	int num;
	int den;
public:
	//default constructor.
	Fraction(int num = 0, int den = 1):num(num), den(den){
		if (den == 0)
		{
			cout << "Error: Denominator cannot be 0, denom has been set to 1." << endl;
			den = 1;
		}

	}
	//a solo int becomes int over 1.
	Fraction(int num) :num(num), den(1) {
	}
	//deconstructor in case we decide to use it.
	~Fraction() {
	}
	void setNum(int a)
	{
		num = a;
	}
	int getNum()
	{
		return num;
	}
	void setDen(int a)
	{
		if (den == 0)
		{
			cout << "Denominator cannot be 0, denominator set as 1." << endl;
			den = 1;
		}
		else
		{
			den = a;
		}
	}
	int getDen()
	{
		return den;
	}
	unsigned long GCD(unsigned long a, unsigned long b)
	{
	return a%b ? GCD(b, a%b) : b;
	}
	void simplify()
	{
		int gcd = GCD(num, den);
		num = num / gcd;
		den = den / gcd;
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
	Fraction operator+(int a)
	{
		Fraction temp;
		temp.setNum(this->num + (a * this->getDen()));
		temp.setDen(this->den);
		//simplify temp here.
		temp.simplify();
		return temp;
	}
	friend Fraction operator+(int a, Fraction b);
	friend ostream& operator<<(ostream& os, Fraction a);
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
		return ((*this > b) or (*this == b));
	}
	bool operator<=(Fraction& b) const {
		return ((*this < b) or (*this == b));
	}
	//now to deal with our scalar, int. Starting with Fraction comparison int.
	//then later as friend methods: int comparison Fraction.
	bool operator==(int& b) const {
		return this->num == (b * this->den);
	}

	// Inequality operator
	bool operator!=(int& b) const {
		return !(*this == b);
	}
	bool operator>(int& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num) > (b * this->den));
	}
	bool operator<(int& b) const {
		//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
		//den. Once they have the same den then the nums can be compared directly.

		return ((this->num) < (b * this->den));
	}
	bool operator>=(int& b) const {
		return ((*this > b) or (*this == b));
	}
	bool operator<=(int& b) const {
		return ((*this < b) or (*this == b));
	}
	//these are the friends for int comparison fraction.
	friend bool operator==(int& b, Fraction& a);
	friend bool operator!=(int& b, Fraction& a);
	friend bool operator>(int& b, Fraction& a);
	friend bool operator<(int& b, Fraction& a);
	friend bool operator>=(int& b, Fraction& a);
	friend bool operator<=(int& b, Fraction& a);
};

bool operator==(int& b, Fraction& a) {
	return a.getNum() == (b * a.getDen());
}

// Inequality operator
bool operator!=(int& b, Fraction& a) {
	return !(a == b);
}
bool operator>(int& b, Fraction& a) {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((b * a.getDen()) > (a.getNum()));
}
bool operator<(int& b, Fraction& a) {
	//multiply each num by the opposite den, this is the relevant part of making two fractions have the same
	//den. Once they have the same den then the nums can be compared directly.

	return ((b * a.getDen()) < (a.getNum()));
}
bool operator>=(int& b, Fraction& a) {
	return ((b > a) or (b == a));
}
bool operator<=(int& b, Fraction& a) {
	return ((b < a) or (b == a));
}


Fraction operator+(int a, Fraction b)
{
	Fraction temp;
	temp.setNum(b.getNum() + (a * b.getDen()));
	temp.setDen(b.getDen());
	//simplify temp here
	temp.simplify();
	return temp;
}
ostream& operator<<(ostream& os, Fraction a)
{
	if (a.getDen() == 1) {
		os << a.getNum();
	}
	else {
		os << a.getNum() << '/' << a.getDen();
	}
	return os;
}
int main() {

	Fraction f1(1, 2);
	Fraction f2(1, 3);
	Fraction f3 = f1 + f2;
	return 0;
}
