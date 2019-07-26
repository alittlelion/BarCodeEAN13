#include "CBarCodeEAN13.h"
#include <stdlib.h>

CBarCodeEAN13::CBarCodeEAN13(std::string str)
{
	m_Text = str;
	m_MidCode = "01010";
	m_AuxiliaryCode = "101";
	m_Encode = "101";

	InitEncode();
}


CBarCodeEAN13::~CBarCodeEAN13()
{
}

void CBarCodeEAN13::InitEncode()
{
	m_EAN13_Code = new vector<element_t*>();
	m_EAN13_Code->push_back(new element_t("0", "AAAAAA", "0001101", "0100111", "1110010"));
	m_EAN13_Code->push_back(new element_t("1", "AAAAAA", "0011001", "0110011", "1100110"));
	m_EAN13_Code->push_back(new element_t("2", "AABABB", "0010011", "0011011", "1101100"));
	m_EAN13_Code->push_back(new element_t("3", "AABBAB", "0111101", "0100001", "1000010"));
	m_EAN13_Code->push_back(new element_t("4", "ABAABB", "0100011", "0011101", "1011100"));
	m_EAN13_Code->push_back(new element_t("5", "ABBAAB", "0110001", "0111001", "1001110"));
	m_EAN13_Code->push_back(new element_t("6", "ABBBAA", "0101111", "0000101", "1010000"));
	m_EAN13_Code->push_back(new element_t("7", "ABABAB", "0111011", "0010001", "1000100"));
	m_EAN13_Code->push_back(new element_t("8", "ABABBA", "0110111", "0001001", "1001000"));
	m_EAN13_Code->push_back(new element_t("9", "ABBABA", "0001011", "0010111", "1110100"));
}

int CBarCodeEAN13::CalculateCheckDigit()
{
	int oddSum = 0;
	int evenSum = 0;
	for (int i = m_Text.length(); i > 0; i--)
	{
		if (i % 2 == 0)
		{
			char ch = m_Text[i - 1];
			int a = (int)(ch);
			a -= 48;
			evenSum += a;
		}
		else if (i % 2 == 1)
		{
			char ch1 = m_Text[i - 1];
			int b = (int)(ch1);
			b -= 48;
			oddSum += b;
		}
	}
	evenSum *= 3;
	int sum = evenSum + oddSum;
	int checkDigit = 10 - (sum % 10);

	return checkDigit;
}

void CBarCodeEAN13::FindCharacterrCode()
{
	if (!isNumber(m_Text) || m_Text.length() < 13 )
	{
		printf("String Error");
		return;
	}
	//查找起始字符使用的编码
	string s(1, m_Text[0]);
	string StartEncode = FindStartEncode(s);
	int length = (int)m_Text.length();
	int startLength = (int)StartEncode.length();
	for (int i = 1; i < length ; i++)
	{
		string str(1, m_Text[i]);
		if (i <= startLength)  //i <= 6
		{
			if (StartEncode[i - 1] == 'A')
			{
				m_Encode += FindDataEncode(str, ENCODEA);
			}
			else if (StartEncode[i - 1] == 'B')
			{
				m_Encode += FindDataEncode(str, ENCODEB);
			}
		}
		else   // i = (7-12)
		{
			if (i == 7)
			{
				m_Encode += m_MidCode;
			}
			m_Encode += FindDataEncode(str, ENCODEC);
		}
	}

}

string CBarCodeEAN13::FindStartEncode(string &s)
{
	for (int i = 0; i < m_EAN13_Code->size(); i++)
	{
		if (m_EAN13_Code->at(i)->Value == s)
		{
			string encode = m_EAN13_Code->at(i)->LeftCode;
			return encode;
		}
	}
	return string();
}

string CBarCodeEAN13::FindDataEncode(string &s, EAN_TYPE type)
{
	string encode;
	for (int i = 0; i < m_EAN13_Code->size(); i++)
	{
		if (m_EAN13_Code->at(i)->Value == s)
		{
			switch (type)
			{
			case ENCODEA:
				encode = m_EAN13_Code->at(i)->LeftACode;
				return encode;
			case ENCODEB:
				encode = m_EAN13_Code->at(i)->LeftBCode;
				return encode;
			case ENCODEC:
				encode = m_EAN13_Code->at(i)->RightCode;
				return encode;
			default:
				break;
			}
		}
	}
	return string();
}

bool CBarCodeEAN13::isNumber(const string &s)
{
	return !s.empty() && s.find_first_not_of("-.0123456789") == string::npos;
}

string CBarCodeEAN13::GetEncode()
{
	int checkDigit = CalculateCheckDigit();
	 string s =to_string(checkDigit);
	 m_Text.append(s);


	FindCharacterrCode();
	m_Encode.append(m_AuxiliaryCode);
	return m_Encode;
}
