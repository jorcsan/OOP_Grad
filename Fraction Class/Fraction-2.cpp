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
	unsignedd long GCD(unsigned long a, unsigned long b)
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
};
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
		os << a.getDen();
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
