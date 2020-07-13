#pragma once
#include<iostream>
using namespace std;
class HugeInt
{
	int *Vs;
	int Size;
	bool Sign;
	
	int Greater(int x, int y)const;
	int FindZeros();
	int STRLEN(char *x)const;
	HugeInt Add(HugeInt &H);
	HugeInt Subtract(HugeInt &H);
	bool LessThen(HugeInt const &H);
	void BalancingZeros(HugeInt &H);
	int intSize(int);
	void TRIM();
public:
	
	/*-----------------------Constructors-------------------------*/
	HugeInt();
	HugeInt(int);
	HugeInt(ifstream &Rdr);
	HugeInt(HugeInt const &H);
	HugeInt(char *&V);
	void HugeInt::HNSet(string s);
	HugeInt& operator=(const char* ptr);
	HugeInt operator=(const HugeInt &H2);


	/*-----------------------Conditions-----------------------------*/
	bool EqualsTo(HugeInt const &H);
	bool GreaterThen(HugeInt const &H);
	
	bool GreaterThenEqualsTo(HugeInt const &H);
	bool LessThenEqualsTo(HugeInt const &H);

	/*-----------------------Operator overload-------------------------------------*/
	HugeInt operator+(HugeInt &H);
	HugeInt operator+=(HugeInt &H);
	HugeInt operator-(HugeInt &H);
	HugeInt operator-=(HugeInt &H);
	HugeInt& operator++();
	HugeInt& operator++(int);
	HugeInt& operator--();
	HugeInt& operator--(int);
	bool operator<(HugeInt const &H);
	bool operator>(HugeInt const &H);
	bool operator==(HugeInt const &H);
	bool operator!=(HugeInt const &H);
	bool operator<=(HugeInt const &H);
	bool operator>=(HugeInt const &H);
	HugeInt operator*(HugeInt &H);
	HugeInt operator/(HugeInt &H);

	HugeInt& Multiplication(HugeInt const &H);
	friend ostream& operator<<(ostream & MyCout, const HugeInt &HN);
	void Swap(HugeInt &H1, HugeInt &H2);
	int operator[](int)const;
	int& operator[](int);
	int GetSize()const;
	int ithDigit(int i);
	
	~HugeInt();
};
