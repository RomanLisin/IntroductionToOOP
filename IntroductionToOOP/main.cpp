#include<iostream>
using namespace std;


class Point  // Создаем структуру 'Point', которая будет описывать точки на плоскости
{
	double x;
	double y;
public:
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
};

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

	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;


}