//Fraction
#include<iostream>
using namespace std;

class Fraction
{
	int integer; //целое
	int numerator; // числитель
	int denominator; //знаменатель

public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//   Constructors:
	Fraction()
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		cout << "DefaultConstruction:\t" << this << endl;

	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1ArgConstructor:\t" << this << endl;

	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numeratror , int denominator )
	{
		set_integer(integer);
		set_numerator(numeratror);
		set_denominator(denominator);
		cout << "Counstructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	// Overloading operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator++()
	{
		this->integer++;
		this->numerator++;
		this->denominator++;
		return *this;
	}

	//				Methods:
	
//Print fraction
void print()const
{
	if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";

		}
		else if (integer == 0)cout << 0;
	cout << endl;
}



// find the  greatest common divisor   (НОД)
int mostMaxCommDivisor(int a, int b)
{
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

//convert to proper fraction                  // 2(2/4)
void convPropFract()
{
	if (numerator > denominator) {
		set_integer(integer + numerator / denominator);
		set_numerator(numerator % denominator);
	}
}

//checks whether two fractions have common denominators; if not, 
// then brings these fractions to a common denominator
void commDenominator(Fraction& other)
{
	if (this->denominator != other.denominator)
	{
		this->set_numerator(this->numerator * other.denominator);
		other.set_numerator(this->denominator * other.numerator);
		this->set_denominator(this->denominator * other.denominator);
		other.set_denominator(this->denominator);
	}
}
int numA_commDenominator(const Fraction& other)const
{
	return this->integer* this->denominator + this->numerator * other.denominator;
}

// simplify the fraction                      // 2(1/4)
void simplFract()                                       
{
	int gcdNumDenom = mostMaxCommDivisor(numerator, denominator);           // simplify the fraction
	if (gcdNumDenom != 1)
	{
		set_numerator(numerator / gcdNumDenom);
		set_denominator(denominator / gcdNumDenom);
	}
}

Fraction operator++(int)
{
	Fraction old = *this;
	integer++;
	return old;
} 

Fraction& operator--()
{
	integer--;
	return *this;
}

Fraction operator--(int)
{
	Fraction old = *this;
	integer--;
	return old;
}
Fraction& operator()(int integ, int numer, int denom)
{
	set_integer(integ);
	set_numerator(numer);
	set_denominator(denom);
	return *this;
}
};

//convert to improper (non-proper) fraction   // 6/4
Fraction& convImpropFract(const Fraction& A)
{
	Fraction Tmp;
	Tmp.set_numerator(A.get_denominator() * A.get_integer() +A.get_numerator());
	Tmp.set_denominator(A.get_denominator());
	Tmp.set_integer(0);
	return Tmp;
}

//     Arithmetic operators:

//
Fraction operator+(const Fraction& A, const Fraction& B)
{
	Fraction Tmp, Tmp2;
	convImpropFract(A);
	convImpropFract(B);
	Tmp.commDenominator(Tmp2);
	Tmp.set_numerator(Tmp.get_numerator() + Tmp2.get_numerator());
	Tmp.convPropFract();
	Tmp.simplFract();
	return Tmp;
}

Fraction operator-(const Fraction& A, const Fraction& B)
{
	Fraction Tmp;
	int dnm_1 = A.get_denominator();
	int dnm_2 = B.get_denominator();
	int num_1 = A.get_numerator();
	int num_2 = B.get_numerator();
	int int_1 = A.get_integer();
	int int_2 = B.get_integer();

	if (dnm_1== dnm_2)  // if denominators equal
	{
		Tmp.set_integer(int_1 - int_2);
		Tmp.set_numerator(num_1 - num_2);
		Tmp.set_denominator(dnm_1);
	}
	else if (Tmp.mostMaxCommDivisor(dnm_1, dnm_2) != 1)    // if denominators have common divisor
	{
		Tmp.set_integer(int_1 - int_2);
		Tmp.set_numerator(num_1 * (dnm_2 / Tmp.mostMaxCommDivisor(dnm_1, dnm_2)) - num_2 * (dnm_1 / Tmp.mostMaxCommDivisor(dnm_1, dnm_2)));
		Tmp.set_denominator(dnm_1 > dnm_2 ? dnm_1 : dnm_2);
	}
	else              // if denominators don't have common divisor
	{
		Tmp.set_integer(int_1 - int_2);
		Tmp.set_numerator(num_1 * dnm_2 - num_2 * dnm_1);
		Tmp.set_denominator(dnm_1 * dnm_2);
	}
	if (Tmp.get_numerator() > Tmp.get_denominator())         //  extract integer
	{
		Tmp.set_integer(Tmp.get_integer() - Tmp.get_numerator() / Tmp.get_denominator());
		Tmp.set_numerator(Tmp.get_numerator() % Tmp.get_denominator());
	}
	Tmp.simplFract();
	
	return Tmp;

}

Fraction operator*(const Fraction& A,const Fraction& B)
{
	 Fraction Tmp;
	 Tmp.set_numerator(convImpropFract(A).get_numerator() * convImpropFract(B).get_numerator());
	 Tmp.set_denominator(convImpropFract(A).get_denominator() * convImpropFract(B).get_denominator());
	 Tmp.convPropFract();
	 Tmp.simplFract();
	 return Tmp;
}

Fraction operator/(const Fraction& A, const Fraction& B)
{
	Fraction Tmp;
	 Tmp.set_numerator(convImpropFract(A).get_numerator() * convImpropFract(B).get_denominator());
	 Tmp.set_denominator(convImpropFract(A).get_denominator() * convImpropFract(B).get_numerator());
	 Tmp.convPropFract();
	 Tmp.simplFract();
	 return Tmp;
}

void operator+=(Fraction& A, const Fraction& B)
{
	A=A+B;
}
void operator-=(Fraction& A, const Fraction& B)
{
	A = A - B;
}
void operator*=(Fraction& A, const Fraction& B)
{
	A = A * B;
}
void operator/=(Fraction& A, const Fraction& B)
{
	A = A / B;
}

bool operator==(const Fraction& A, const Fraction& B)
{
	return A.numA_commDenominator(B) == B.numA_commDenominator(A);
}

bool operator!=(const Fraction& A, const Fraction& B)
{
	return A.numA_commDenominator(B) != B.numA_commDenominator(A);	
}

bool operator>(const Fraction& A, const Fraction& B)
{
	return A.numA_commDenominator(B) > B.numA_commDenominator(A);	
}

bool operator<(const Fraction & A, const Fraction & B)
{
	return A.numA_commDenominator(B) < B.numA_commDenominator(A);
}

bool operator>=(const Fraction& A, const Fraction& B)
{
	return A.numA_commDenominator(B) >= B.numA_commDenominator(A);
}

bool operator<=(const Fraction& A, const Fraction& B)
{
	return A.numA_commDenominator(B) <= B.numA_commDenominator(A);
}

std::ostream& operator<<(std::ostream& os, const Fraction& A)
{
	return os << "Integer:\t" << A.get_integer() << endl 
		<< "Numerator:\t"<< A.get_numerator() << endl
		<<"Denominator:\t" << A.get_denominator()<< endl;
}

std::istream& operator>>(std::istream& is, Fraction& A)
{
	int integ,numer, denom;
	is >> integ>> numer >> denom;
	A(integ, numer, denom);
	/*A.set_integer(inter);
	A.set_numerator(numer);
	A.set_denominator(denom);*/
	return is;
}


void main()
{
	setlocale(LC_ALL, "");

	//Fraction A; // Default constructor
	//cout << " A = ";
	//A.print();

	//Fraction B = 5; // Single-argument constructor
	//cout << " B = ";
	//B.print();

	//Fraction C(0,1, 2);
	//cout << " C = ";
	//C.print();

	//Fraction D(2, 1, 4);
	//cout << " D = ";
	//D.print();

	//Fraction E = D; // Copy constructor
	//cout << " E = D = ";
	//E.print();

	//Fraction F;
	//cout << " F = E = ";
	//F = E;			// Copy assignment
	//F.print();

	// cout << " C = ";
	// C.print();
	// cout << " D = ";
	// D.print();
	// F = C+D;
	// cout << " F = ";
	// F.print();		
	// F = C-D;
	// cout << " F = C - D = ";
	// F.print();		
	// cout << " F = C * D = ";
	// F = C*D;
	// F.print();		
	// cout << " F = C / D = ";
	// F = C / D;
	// F.print();	

	// cout << (C > D ? "false" : "true") << endl;

	// cout << "Input Fract: "; cin >> F;
	// cout << F << endl;
	// F.print();


	
	  

}