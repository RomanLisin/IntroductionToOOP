#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <cstring>
using namespace std;

int sizeChStr(const char* str);
void strCopy(char* to, const char* from);
void concatenateStrings(char* to, const char* from);

class String {
private:
	char* arrStr;
	int lenStr;

public:
	char* get_arrStr()const
	{
		return arrStr;
	}

	// default constructor
	String() : lenStr(80) {
		arrStr = new char[lenStr];
		for (int i = 0; i < lenStr; i++) {
			arrStr[i] = (i == lenStr - 1 ? '\0' :' '); // Initialize with spaces
		}
	}
	// constructor 
	String(const char* str) {
		lenStr = sizeChStr(str) + 1;
		arrStr = new char[lenStr];
		strCopy(arrStr, str);
	}
	// copy constructor
	String(const String& str) {
		lenStr = str.lenStr;
		arrStr = new char[lenStr];
		strCopy(arrStr, str.arrStr);
	}
	// assignment operator
	String& operator=(const String& str) {
		if (this != &str) {
			delete[] arrStr;
			lenStr = str.lenStr;
			arrStr = new char[lenStr];
			strCopy(arrStr, str.arrStr);
		}
		return *this;
	}
	// destructor
	~String() {
		delete[] arrStr;
	}
	// concatenation operator
	String operator+(const String& str) const {
		String result;
		result.lenStr = lenStr + str.lenStr ; // don't -1 to remove '\0' because we need insert ' '
		result.arrStr = new char[result.lenStr];
		strCopy(result.arrStr, arrStr);
	https://cplusplus.com/reference/cstring/strcat/?kw=strcat
		//strcat(result.arrStr, str.arrStr);
		concatenateStrings(result.arrStr, str.arrStr);
		return result;
	}
	// get length of string
	int sizeStr() const {
		return lenStr - 1; // -1 to exclude '\0'
	}
};
	// Output operator
	std::ostream& operator<<(std::ostream& os, const String& str) {
		os << str.get_arrStr();
		return os;
	}


void main() {
	setlocale(LC_ALL, "");

	String Str; // Default constructor creates an empty string of 80 characters
	String str1 = "Hello"; // copy constructor
	String str2 = "World"; // copy constructor
	String str3 = str1 + str2;
	cout << str3 << endl;

}

int sizeChStr(const char* str)
{
	int i = 0;
	while (str[++i]);
	return i;
}

void strCopy(char* to, const char* from)
{
	int i = 0;
	while (from[i]) {		//!= '\0') {
		to[i] = from[i];
		i++;
	}
	to[i] = '\0'; // null-terminate the to string
}

void concatenateStrings(char* to, const char* from) 
{
	int toLen = 0;
	while (to[toLen]) toLen++;  // != '\0') {toLen++; }
	int fromLen = 0;
	while (from[fromLen]) fromLen++;  // != '\0') {fromLen++; }
	to[toLen] = ' ';
	toLen++;
	for (int i = 0; i < fromLen; i++) {
		to[toLen + i] = from[i];
	}
	to[toLen + fromLen] = '\0'; // null-terminate the resulting string
}
