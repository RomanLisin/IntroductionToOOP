#include<iostream>
#include<math.h>
using namespace std;


class Point  // Создаем структуру 'Point', которая будет описывать точки на плоскости
{
	double x;
	double y;

public:

	//Point() { x = 0; y = 0; }; // default constructor 

	//Point(double X, double Y)   // constructor 2
	//{
	//	x = X;
	//	y = Y;
	//}

	//Point(double X, double Y) :x(X), y(Y) {}; //constructor with member initialization list functional form

	Point(double X, double Y) :x{ X }, y{ Y } {}; // uniform initializer syntax

	double get_x() const
	{
		return x;
	}
	double get_y() const
	{
		return y;
	}
	void set_x(double x)
	{
		this -> x = x;
	}
	void set_y(double y)
	{
		this -> y = y;
	}
	double distance();
};

double distance(Point, Point);

//#define STRUCT_POINT

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRUCT_POINT
	cout << "Hello OOP" << endl;
	int a;      // Объявление переменной 'a' типа 'int'
	Point A;    // Объявление переменной 'A' типа 'Point'
	// Создание объекта 'A' структуры 'Point'
	// Создание экземпляра структуры 'Point'
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;
	cout << sizeof(Point) << endl;
	cout << sizeof(A) << endl;

	Point* pA = &A;
	cout << (*pA).x << "\t" << (*pA).y << endl;  // одно и то же
	cout << pA->x << "\t" << pA->y << endl;      //  одно и то же  
#endif // STRUCT_POINT

	Point A{3, 4};    //  uniform init  defoult constructor called
	//Point B(8,6);  // functional form initialization defoult constructor NOT called
	Point B{8, 9}; 

	/*A.set_x(2);
	A.set_y(3);
	B.set_x(5);
	B.set_y(8);*/

	std::cout << A.get_x() << "\t" << A.get_y() << endl;
	std::cout << B.get_x() << "\t" << B.get_y() << endl;
	std::cout << "The distance to point B is: " << B.distance() << endl;
	std::cout << "The distance between points X and Y is: " << distance(A,B) << endl;
}

double Point::distance() { return pow(pow(x, 2) + pow(y, 2), 0.5); }

double distance(Point x, Point y)
{
	double deltX = y.get_x() - x.get_x();
	double deltY = y.get_y() - x.get_y();
	return  pow(pow(deltX, 2) + pow(deltY, 2), 0.5);
}