#include<iostream>
#include"HugeInt.h"
#include<fstream>
#include<string>
using namespace std;

int main()
{
	HugeInt **HNs;
	int HNsize;
	ifstream Rdr("HNs.txt");
	Rdr >> HNsize;
	HNs = new HugeInt*[HNsize];
	for (int vi = 0; vi < HNsize; vi++)
	{
		HNs[vi] = new HugeInt(Rdr);
	}
	for (int vi = 0; vi < HNsize; vi++)
	{
		cout << *HNs[vi];
	}

	cout << endl;
	HugeInt temp;
	cout << "ADDITION" << endl;
	temp = (*HNs[0]) + (*HNs[1]);
	
	cout << temp;
	cout << "SUBTRACTION" << endl;
	HugeInt tem;
	tem = (*HNs[0]) - (*HNs[1]);
	cout << tem;

	cout << "Division" << endl;
	HugeInt te;
	te = (*HNs[0]) / (*HNs[1]);
	cout << te;

	cout << "Multiply" << endl;
	HugeInt t;
	t = (*HNs[0]) * (*HNs[1]);
	cout << t;


	if (*HNs[0] > *HNs[1])
	{
		cout << "Greater" << endl;
	}
	else
	if (*HNs[0] < *HNs[1])
	{
		cout << "LESS" << endl;
	}
	else
	if (*HNs[0] == *HNs[1])
	{
		cout << "Equal" << endl;
	}
	if (*HNs[0] >= *HNs[1])
		cout << "Greater then or equals to" << endl;

	if (*HNs[0] <= *HNs[1])
		cout << "Less then or equals to" << endl;

	
	return 0;
}