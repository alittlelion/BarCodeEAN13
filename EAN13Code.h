/*
Function: EAN-13Code
Timer: 2019-07-24
Editor: Mr.Wu
*/
#include <string>
#include <vector>
using namespace std;

enum EAN_TYPE
{
	ENCODEA,
	ENCODEB,
	ENCODEC
};

struct element_t
{
	string LeftCode;
	string LeftACode;
	string LeftBCode;
	string RightCode;
	string Value;

	element_t(string value, string leftcode, string leftA, string leftB, string right)
		: Value(value), LeftCode(leftcode), LeftACode(leftA), LeftBCode(leftB), RightCode(right)
	{	}
};


class CBarCodeEAN13
{
public:
	CBarCodeEAN13(string str);
	~CBarCodeEAN13();

	int CalculateCheckDigit();

	string GetEncode();
private:
	void InitEncode();
	
	void FindCharacterrCode();

	bool isNumber(const string &s);

	string FindStartEncode(string &s);

	string FindDataEncode(string &s, EAN_TYPE type);
private:
	string m_Text;
	vector<element_t*>  *m_EAN13_Code;
	string m_MidCode;                //middle code
	string m_AuxiliaryCode;
	string m_Encode;
};
