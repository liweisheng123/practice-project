#include <iostream>
#include <string>
#include <cmath>
#include"operation.h"
using namespace std;
//Message padding
string padding(string str)
{
	string res = "";
	for (int i = 0; i < str.size(); i++)//����ת������Ϊ16����
	{
		res += DecToHex((int)str[i]);
	}
	int res_length = res.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	res += "8";//��ԭʼ���ݺ���䡰1��
	while (res.size() % 128 != 112)
	{
		res += "0";//��ԭʼ���ݺ������䡰0��
	}
	string res_len = DecToHex(res_length);//���ݳ���תΪ�����ƣ���Ҫ�����64bit
	while (res_len.size() != 16)
	{
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

//Message extension
string extension(string str)
{
	string res = str;//ֱ�Ӹ�ֵǰ16����չ��W
	//���չ�������17λ����68λ��Wֵ
	for (int i = 16; i < 68; i++)
	{
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	//���չ������64λW'ֵ
	for (int i = 0; i < 64; i++)
	{
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	return res;
}

//Message compression
string compress(string str1, string str2)
{
	string V = str2;
	//��ʼ��8���ּĴ���(ABCDEFGH=V)
	string A = V.substr(0, 8), B = V.substr(8, 8),
		C = V.substr(16, 8), D = V.substr(24, 8),
		E = V.substr(32, 8), F = V.substr(40, 8),
		G = V.substr(48, 8), H = V.substr(56, 8);
	//��ʼ���ĸ��м����
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	//���ݼ������ֵ
	for (int i = 0; i < 64; i++)
	{
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(i), (i % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, i), D), SS2), str1.substr((i + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, i), H), SS1), str1.substr(i * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
	}
	string res = (A + B + C + D + E + F + G + H);//ƴ��
	return res;
}

//Iterative compression
string iteration(string str, string IV)
{
	int n = str.size() / 128;//���飬ÿ��512bit
	string V = IV;
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < n; i++)
	{
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}

int main()
{
	string IV = "1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF";
	string str = "lws202000460106";
	cout << "Msg: " + str << endl;
	string paddingValue = padding(str);
	string result = iteration(paddingValue, IV);
	cout << "Hashed_Msg��" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << result.substr(i * 8, 8) << "  ";
	}
	cout << endl;
	return 0;
}