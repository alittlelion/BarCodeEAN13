#include <iostream>
#include "CBarCodeEAN13.h"
#include <string>
using namespace std;

int main()
{	
	CBarCodeEAN13 EAN13("690123456723");
	int checkDigit = EAN13.CalculateCheckDigit();
	string s = EAN13.GetEncode();

	cout <<checkDigit <<"\n"<< s << endl;
	
	system("pause");
	return 0;
}
