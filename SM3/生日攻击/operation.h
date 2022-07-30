#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
//������ת��Ϊʮ�����ƺ���ʵ��
string BinToHex(string str)
{
	string hex = "";//�����洢������ɵ�ʮ��������
	int temp = 0;//�����洢ÿ����λ����������ʮ����ֵ
	while (str.size() % 4 != 0) //��Ϊÿ��λ�����������ܹ���Ϊһ��ʮ�������������Խ�������������ת��Ϊ4�ı���
	{
		str = "0" + str;//���λ��0ֱ������Ϊ4�ı�������
	}
	for (int i = 0; i < str.size(); i += 4)
	{
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;//�жϳ�4λ����������ʮ���ƴ�СΪ����
		if (temp < 10) //���õ���ֵС��10ʱ������ֱ����0-9������
		{
			hex += to_string(temp);
		}
		else //���õ���ֵ����10ʱ����Ҫ����A-F��ת��
		{
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//ʮ������ת��Ϊ�����ƺ���ʵ��
string HexToBin(string str)
{
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
		{
			bin += table[str[i] - 'A' + 10];
		}
		else
		{
			bin += table[str[i] - '0'];
		}
	}
	return bin;
}

//������ת��Ϊʮ���Ƶĺ���ʵ��
int BinToDec(string str)
{
	int dec = 0;
	for (int i = 0; i < str.size(); i++)
	{
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
string DecToBin(int str)
{
	string bin = "";
	while (str >= 1)
	{
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
int HexToDec(string str)
{
	int dec = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
		{
			dec += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else {
			dec += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return dec;
}

//ʮ����ת��Ϊʮ�����Ƶĺ���ʵ��
string DecToHex(int str)
{
	string hex = "";
	int temp = 0;
	while (str >= 1)
	{
		temp = str % 16;
		if (temp < 10 && temp >= 0)
		{
			hex = to_string(temp) + hex;
		}
		else
		{
			hex += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return hex;
}


string LeftShift(string str, int len) //ʵ��ѭ������lenλ����
{
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}

string XOR(string str1, string str2) //ʵ��������
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++)
	{
		if (res1[i] == res2[i])
		{
			res += "0";
		}
		else
		{
			res += "1";
		}
	}
	return BinToHex(res);
}

string AND(string str1, string str2) //ʵ�������
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++)
	{
		if (res1[i] == '1' && res2[i] == '1')
		{
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

string OR(string str1, string str2) //ʵ�ֻ����
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++)
	{
		if (res1[i] == '0' && res2[i] == '0')
		{
			res += "0";
		}
		else
		{
			res += "1";
		}
	}
	return BinToHex(res);
}

string NOT(string str) //ʵ�ַǲ���
{
	string res1 = HexToBin(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++)
	{
		if (res1[i] == '0')
		{
			res += "1";
		}
		else
		{
			res += "0";
		}
	}
	return BinToHex(res);
}

char binXor(char str1, char str2) //ʵ�ֵ����ص�������
{
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) //ʵ�ֵ����ص������
{
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) //mod 2^32����ĺ���ʵ��
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--)
	{
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1')
		{
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1')
			{
				temp = binAnd('1', temp);
			}
			else
			{
				temp = '0';
			}
		}
	}
	return BinToHex(res);
}

string P1(string str) //ʵ���û�����P1��X��
{
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) //ʵ���û�����P0��X��
{
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) //����Tj����ֵ�ĺ���ʵ��
{
	if (0 <= j && j <= 15)
	{
		return "79CC4519";
	}
	else
	{
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) //ʵ�ֲ�������FF����
{
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) //ʵ�ֲ�������GG����
{
	if (0 <= j && j <= 15)
	{
		return XOR(XOR(str1, str2), str3);
	}
	else
	{
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}

