#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include <iostream>
//#include <cstring>
using namespace std;
//#define CONSTRUCTOR_CHECK;

//int sizeChStr(const char* str);
//void strCopy(char* to, const char* from);
void concatenateStrings(char* to, const char* from);

class String {
private:

	int lenStr;    // рзмер строки в Байтах
	char* arrStr;  // адрес строки в динамической памяти

public:

	int get_lenStr()const
	{
		return lenStr;
	}

	const char* get_arrStr()const
	{
		return arrStr;
	}
	char* get_arrStr()
	{
		return arrStr;
	}
	//  constructors:

	explicit String(int size = 80)
	{
		this->lenStr = size;
		this->arrStr = new char[size] {};  //   чтобы создаваемая строка не была заплнена мусором после оператора скобочки ставим фигурные скобки, в этом случае строка заполняется нулями, но при выводе они не отображаются
		cout << "DefaultConstractor:\t" << this << endl;
	}

	//String() : lenStr(80) {
	//	arrStr = new char[lenStr];
	//	for (int i = 0; i < lenStr; i++) {
	//		arrStr[i] = (i == lenStr - 1 ? '\0' :' '); // Initialize with spaces
	//	}
	//}
	// constructor 
	String(const char* str) {

		this->lenStr = strlen(str) + 1;  // strlen -  считает размер строки в символах
		this->arrStr = new char[lenStr] {};
		for (int i = 0; i < str[i]; i++)this->arrStr[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;

		/*lenStr = sizeChStr(str) + 1;
		arrStr = new char[lenStr];
		strCopy(arrStr, str);*/
	}

	//copy constructor  -  всегда принимает константную ссылку на объект
// The rule of three   -  если в классе есть динамическая память, то в классе должны быть конструктор копирования, оператор присваивания и деструктор
// The rule of zero    -  если динамическая память отсутствует , CopyConstructor, CopyAssignment, Destructor - не нужны

	String(const String& other)
	{
		this->lenStr = other.lenStr;
		// Deep copy - побитовое копирование:
		// 1) выделяем новую память:
		this->arrStr = new char[lenStr] {};    //  то бишь два объекта не используют одну и ту же память
		// 2) Копируем содержимое этой памяти из другого объекта:
		for (int i = 0; other.arrStr[i]; i++)this->arrStr[i] = other.arrStr[i]; // вместо other.arrStr[i] - (до null-terminator) можно поставить и будет вернее  i < lenStr;
		cout << "CopyConstructor:\t" << this << endl;

		//strcpy(arrStr, other.arrStr);
	}

	String(String&& other)
	{
		// Shallow copy:
		this->lenStr = other.lenStr;
		this->arrStr = other.arrStr; // shalow copy
		// MoveConstructor должен работать так, как НЕ должен работать CopyConstructor
		// После копирования удаляемый объект обязательно нужно обнулить:
		other.arrStr = nullptr;
		other.lenStr = 0;
		cout << "MoveConstructor:\t\t" << this << endl;
	}

	// destructor
	~String() {
		delete[] arrStr;
		cout << "Destructor:\t\t" << this << endl;
	}

				// Operators
	// assignment operator    -   также как и конструктор копирования принимает константную ссылку на объект
	String& operator=(const String& other)   
	{
		if (this == &other)return *this;
		delete[] this->arrStr;
		this->lenStr = other.lenStr;
		this->arrStr = new char[lenStr] {}; // если не ставить фигурные скобки , то вывод неправильный, т.е. сразу не инициализируетс, поэтому заполнение происходить относительно мусора, поэтому в итоге получаем неправильный вывод- мусор
		for (int i = 0; other.arrStr[i]; i++)this->arrStr[i] = other.arrStr[i];  // вместо other.arrStr[i] - (до null-terminator) можно поставить и будет вернее  i < lenStr;
		cout << "CopyAssignment:\t\t" << this << endl;
		//strcpy(arrStr, str.arrStr);
		//strCopy(arrStr, str.arrStr);
		
	}
	String& operator=(String&& other)
	{
		if (this == &other) return *this;
		delete[] this->arrStr;
		this->lenStr = other.lenStr;
		this->arrStr = other.arrStr;
		other.arrStr = nullptr;
		other.lenStr = 0;
		cout << "MoveAssignment:\t\t" << this << endl;
		return *this;
	}

	char operator[](int i)const    // когда возвращаем по значению, на месте вызова создаётся безымянный объект
	{								// а временные безымянные объекты всегда являются константными, т.е. перед char const не нужно,
		return arrStr[i];			// потому что он итак константный
	}
	char& operator[](int i)			// чтобы изменить возвращаемый временный безымянный объект, его нужно передать по ссылке
	{
		return arrStr[i];
	}

			//  Methods:
	void print()const
	{
		cout << "Size:\t" << lenStr << endl;
		cout << "arrStr:\t" << arrStr << endl;
	}
	// concatenation operator
	//String operator+(const String& str) const {
	//	String result;
	//	result.lenStr = lenStr + str.lenStr-1; //  -1 to remove '\0' because we need insert ' '
	//	result.arrStr = new char[result.lenStr];
	//	strcpy(result.arrStr, str.arrStr);
	//	//strCopy(result.arrStr, arrStr);
	//https://cplusplus.com/reference/cstring/strcat/?kw=strcat
	//	//strcat(result.arrStr, str.arrStr);
	//	concatenateStrings(result.arrStr, str.arrStr);
	//	return result;
	//}
	// get length of string
	//int sizeStr() const {
	//	return lenStr-1; // -1 to exclude '\0'
	//}
};
	// Output operator
	std::ostream& operator<<(std::ostream& os, const String& str) 
	{ 
		return os << str.get_arrStr();
	}

	String operator+(const String& left, const String& right)
	{
		//Hello + world = HelloWorld;
		//String cat = left.get_lenStr() + right.get_lenStr();  // explicit constructor не возможно вызвать вот так, 
		String cat(left.get_lenStr() + right.get_lenStr()-1);     //  но его всегда можно вызвать вот так
		for (int i = 0; i < left.get_lenStr(); i++)
			cat[i] = left[i];
		//cat.get_arrStr()[i] = left.get_arrStr()[i];
		for (int i = 0; i < right.get_lenStr(); i++)
			cat[i + left.get_lenStr()-1] = right[i];
		//cat.get_arrStr()[i + left.get_lenStr()-1] = right.get_arrStr()[i];
		return cat;
	}

	void main() {
		setlocale(LC_ALL, "");


#ifdef CONSTRUCTOR_CHECK

		String Str; // Default constructor creates an empty string of 80 characters
		String str1 = "Hello"; // copy constructor
		String str2 = "World"; // copy constructor
		String str3 = str1 + str2;
		cout << str3 << endl;



		String str;          // Default constructor
		str.print();

		String str1 = "Hello";   // Single-argument constructor
		//str1.print();
		cout << str1 << endl;

		String str2 = str1;            // Copy constructor
		cout << str2 << endl;

		String str3;					// Default constructor
		str3 = str2;					// Copy assingment
		cout << str3 << endl;


#endif // CONSTRUCTOR_CHECK
	
		String str1 = "Hello";
		String str2 = "World";
		std::cout << str1 << endl;
		std::cout << str2 << endl;

		String str3;
		str3 = str1 + str2;
		std::cout << str3 << endl;
	}

/*
-------------------------------
C++11:	The rule of three => The rule of five:
MoveConstructor;
MoveAssignment;
Shallow copy - поверхностное копирование
r-value reference на объект нашего класса
-------------------------------
*/


//int sizeChStr(const char* str)
//{
//	int i = 0;
//	while (str[++i]);
//	return i;
//}

//void strCopy(char* to, const char* from)
//{
//	int i = 0;
//	while (from[i]) {		//!= '\0') {
//		to[i] = from[i];
//		i++;
//	}
//	to[i] = '\0'; // null-terminate the to string
//}

void concatenateStrings(char* to, const char* from) 
{
	int toLen = 0;
	while (to[toLen]) toLen++;  // != '\0') {toLen++; }
	int fromLen = 0;
	while (from[fromLen]) fromLen++;  // != '\0') {fromLen++; }
	/*to[toLen] = ' ';
	toLen++;*/
	for (int i = 0; i < fromLen; i++) {
		to[toLen + i] = from[i];
	}
	to[toLen + fromLen] = '\0'; // null-terminate the resulting string
}
