#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
//二进制转换为十六进制函数实现
string BinToHex(string str)
{
	string hex = "";//用来存储最后生成的十六进制数
	int temp = 0;//用来存储每次四位二进制数的十进制值
	while (str.size() % 4 != 0) //因为每四位二进制数就能够成为一个十六进制数，所以将二进制数长度转换为4的倍数
	{
		str = "0" + str;//最高位添0直到长度为4的倍数即可
	}
	for (int i = 0; i < str.size(); i += 4)
	{
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;//判断出4位二进制数的十进制大小为多少
		if (temp < 10) //当得到的值小于10时，可以直接用0-9来代替
		{
			hex += to_string(temp);
		}
		else //当得到的值大于10时，需要进行A-F的转换
		{
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//十六进制转换为二进制函数实现
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

//二进制转换为十进制的函数实现
int BinToDec(string str)
{
	int dec = 0;
	for (int i = 0; i < str.size(); i++)
	{
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//十进制转换为二进制的函数实现
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

//十六进制转换为十进制的函数实现
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

//十进制转换为十六进制的函数实现
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


string LeftShift(string str, int len) //实现循环左移len位功能
{
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}

string XOR(string str1, string str2) //实现异或操作
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

string AND(string str1, string str2) //实现与操作
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

string OR(string str1, string str2) //实现或操作
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

string NOT(string str) //实现非操作
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

char binXor(char str1, char str2) //实现单比特的异或操作
{
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) //实现单比特的与操作
{
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) //mod 2^32运算的函数实现
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

string P1(string str) //实现置换功能P1（X）
{
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) //实现置换功能P0（X）
{
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) //返回Tj常量值的函数实现
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

string FF(string str1, string str2, string str3, int j) //实现布尔函数FF功能
{
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) //实现布尔函数GG功能
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

