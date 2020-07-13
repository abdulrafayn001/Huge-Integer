#include "HugeInt.h"
#include<string>
#include<fstream>
using namespace std;
/*------------------------Constructors-----------------------------*/
HugeInt::HugeInt()
{
	Size = 0;
	Vs = nullptr;
}

HugeInt::HugeInt(int x)
{
	if (x != 0)
	{
		if (x < 0)
		{
			Sign = true;
			x = x*-1;
		}
		else
		{
			Sign = false;
		}
		int i = 0, m = x;
		while (m > 0)
		{
			m /= 10;
			i++;
		}
		this->Size = i;
		Vs = new int[Size];
		i = 0;
		int rem = 0;
		while (x > 0)
		{
			rem = x % 10;
			x /= 10;
			Vs[i] = rem;
			i++;
		}
	}
	else
	{
		Sign = false;
		Size = 1;
		Vs = new int[Size];
		Vs[x] = x;
	}
}
HugeInt::HugeInt(ifstream &Rdr)
{
	string s;
	Rdr >> s;
	HNSet(s);
	this->TRIM();

}

HugeInt::HugeInt(HugeInt const &H)
{
	Vs = nullptr;
	Size = H.Size;
	Vs = new int[Size];
	Sign = H.Sign;
	for (int i = 0; i < Size; i++)
	{
		Vs[i] = H.Vs[i];
	}
}

HugeInt& HugeInt::operator=(const char* ptr)
{
	delete[]this->Vs;
	this->Vs = nullptr;
	this->Sign = false;
	Size = 0;
	this->HNSet(ptr);
	return *this;
}
void HugeInt::HNSet(string s)
{
	int di = 0;
	int si = 0;
	bool sfind = false;
	if (s[0] == '+' || s[0] == '-')
	{
		this->Sign = (s[0] == '-');
		si++;
	}
	this->Size = s.length() - si;
	this->Vs = new int[this->Size];
	int x = Size - 1;
	for (; x >= 0; si++)
	{
		Vs[x] = s[si] - '0';
		x--;
	}
	TRIM();
}



/*--------------------------Conditions----------------------------*/
bool HugeInt::EqualsTo(HugeInt const &H)
{
	if (Size == H.Size)
	{
		for (int i = 0; i < Size; i++)
		{
			if (Vs[i] != H.Vs[i])
				return false;
		}
	}
	else
		return false;
	return true;
}

bool HugeInt::GreaterThen(HugeInt const &H)
{
	if (Size > H.Size)
		return true;
	else
	if (Size < H.Size)
		return false;
	else
	{
		for (int i = Size - 1; i >= 0; i--)
		{
			if (Vs[i]>H.Vs[i])
				return true;
			else
			if (Vs[i] < H.Vs[i])
				return false;
		}
	}
	return false;
}

bool HugeInt::LessThen(HugeInt const &H)
{
	if (Size < H.Size)
		return true;
	else
	if (Size > H.Size)
		return false;
	else
	{
		for (int i = Size - 1; i >= 0; i--)
		{
			if (Vs[i]<H.Vs[i])
				return true;
			else
			if (Vs[i] > H.Vs[i])
				return false;
		}
	}
	return false;
}

bool HugeInt::GreaterThenEqualsTo(HugeInt const &H)
{
	if (Size > H.Size)
		return true;
	else
	if (Size < H.Size)
		return false;
	else
	{
		for (int i = Size - 1; i >= 0; i--)
		{
			if (Vs[i]>H.Vs[i])
				return true;
			else
			if (Vs[i] < H.Vs[i])
				return false;
		}
	}
	return true;
}

bool HugeInt::LessThenEqualsTo(HugeInt const &H)
{
	if (Size < H.Size)
		return true;
	else
	if (Size > H.Size)
		return false;
	else
	{
		for (int i = Size - 1; i >= 0; i--)
		{
			if (Vs[i]<H.Vs[i])
				return true;
			else
			if (Vs[i] > H.Vs[i])
				return false;
		}
	}
	return true;
}



int HugeInt::GetSize()const
{
	return Size;
}
int HugeInt::ithDigit(int i)
{
	int temp = 0;
	if (i >= Size)
		return temp;
	else
		return Vs[i];
}

HugeInt HugeInt::Add(HugeInt &H)
{
	this->BalancingZeros(H);
	HugeInt res;
	res.Size = Size + 1;
	res.Vs = new int[this->Size + 1];
	int Carry = 0;
	for (int i = 0; i < res.Size - 1; i++)
	{
		res.Vs[i] = (this->Vs[i] + H.Vs[i] + Carry) % 10;
		Carry = (this->Vs[i] + H.Vs[i] + Carry) / 10;
	}
	res.Vs[res.Size - 1] = Carry;
	res.TRIM();
	return res;

}
HugeInt HugeInt::Subtract(HugeInt &H)
{
	bool isSwap = false;
	if (this->LessThen(H))
	{
		Swap(*this, H);
		isSwap = true;
	}
	this->BalancingZeros(H);
	HugeInt res = *this;
	for (int i = 0; i < res.Size; i++)
	{
		if (res[i] < H[i])
		{
			res[i] += 10;
			--res[i + 1];
		}
		res[i] -= H[i];
	}

	res.TRIM();
	if (isSwap)
	{
		Swap(*this, H);
	}
	return res;
}

HugeInt HugeInt::operator+(HugeInt &H)
{
	if (this->Sign == H.Sign)
	{
		HugeInt res = this->Add(H);
		res.Sign = Sign;
		return res;
	}
	else
	{
		HugeInt res = this->Subtract(H);
		return res;
	}
}

HugeInt HugeInt::operator+=(HugeInt &H)
{
	*this = *this + H;
	return *this;
}

HugeInt& HugeInt::operator++()
{
	HugeInt i(1);
	HugeInt temp = *this;
	temp = temp + i;
	return temp;
}
HugeInt& HugeInt::operator++(int)
{
	HugeInt i(1);
	*this = *this + i;
	return *this;
}

HugeInt HugeInt::operator-(HugeInt  &H)
{
	HugeInt res;

	if (this->Sign == false && H.Sign == true)
	{
		res = this->Add(H);
		res.Sign = false;
		return res;
	}
	else
	if (this->Sign == true && H.Sign == false)
	{
		res = this->Add(H);
		res.Sign = true;
	}
	else
	if (this->Sign == false && H.Sign == false)
	{
		res = this->Subtract(H);
		if (this->LessThen(H))
		{
			res.Sign = true;
		}
		else
		{
			res.Sign = false;
		}
	}
	else
	{
		res = this->Subtract(H);
		if (this->LessThen(H))
		{
			res.Sign = false;
		}
		else
		{
			res.Sign = true;
		}
	}
	return res;
}
HugeInt HugeInt::operator-=(HugeInt &H)
{
	*this = *this - H;
	return *this;
}
HugeInt& HugeInt::operator--()
{
	if (Size != 0)
	{
		HugeInt i(1);
		HugeInt temp = *this;
		temp = temp - i;
		return temp;
	}
	return *this;
}
HugeInt& HugeInt::operator--(int)
{
	if (Size != 0)
	{
		HugeInt i(1);
		*this = *this - i;
	}
	return *this;
}
HugeInt HugeInt::operator*(HugeInt &H)
{
	bool isSwap = false;
	if (this->GreaterThen(H))
	{
		Swap(*this, H);
		isSwap = true;
	}
	HugeInt T(0), Zero(0),TH;
	TH = H;
	HugeInt res(0), Count(0);
	while (TH != Zero)
	{
		res = *this, Count = "1";
		while ((Count+Count) <= TH)
		{
			res += res;
			Count += Count;
		}
		T += res;
		res = "0";
		TH -= Count;
	}
	if (isSwap)
	{
		Swap(*this, H);
	}
	return T;
}

HugeInt HugeInt::operator/(HugeInt &H)
{
	bool isChangethis = false, isChangeH = false;
	if (this->Sign == true)
	{
		Sign = false;
		isChangethis = true;
	}
	if (H.Sign == true)
	{
		H.Sign = false;
		isChangeH = true;
	}
	HugeInt res(0);
	HugeInt i(0);
	HugeInt x(1);
	while (res.LessThen(*this))
	{
		if ((res + H) >= *this)
			break;
		res = res + H;
		i = i + x;
	}

	if (isChangeH)
	{
		H.Sign = true;
	}
	if (isChangethis)
	{
		this->Sign = true;
	}
	if (H.Sign != Sign)
		i.Sign = true;
	else
		i.Sign = Sign;
	return i;
}

bool HugeInt::operator<(HugeInt const &H)
{
	if (Sign == false && H.Sign == true)
	{
		return false;
	}
	else
	if (Sign == true && H.Sign == false)
	{
		return true;
	}
	else
	if ((Sign == true && H.Sign == true) && (this->LessThen(H) == true))
	{
		return false;
	}
	else
	if ((Sign == true && H.Sign == true) && (this->LessThen(H) == false))
	{
		return true;
	}
	else
	{
		return (this->LessThen(H));
	}
}

bool HugeInt::operator>(HugeInt const &H)
{
	if (Sign == true && H.Sign == false)
	{
		return false;
	}
	else
	if (Sign == false && H.Sign == true)
	{
		return true;
	}
	else
	if ((Sign == true && H.Sign == true) && (this->GreaterThen(H)) == true)
	{
		return false;
	}
	else
	if ((Sign == true && H.Sign == true) && (this->GreaterThen(H)) == false)
	{
		return true;
	}
	else
	{
		return (this->GreaterThen(H));
	}
}

bool HugeInt::operator==(HugeInt const &H)
{
	if ((Sign == H.Sign) && (this->EqualsTo(H)) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HugeInt::operator<=(HugeInt const &H)
{
	if (*this < H || *this == H)
	{
		return true;
	}
	else
		return false;
}

bool HugeInt::operator>=(HugeInt const &H)
{
	if (*this > H || *this == H)
	{
		return true;
	}
	else
		return false;
}

bool HugeInt::operator!=(HugeInt const &H)
{
	if ((*this == H) == false)
		return true;
	else
		return false;
}


HugeInt HugeInt::operator=(const HugeInt &H2)
{
	delete[]Vs;
	this->Vs = nullptr;
	this->Sign = H2.Sign;
	this->Size = H2.Size;
	this->Vs = new int[this->Size];
	for (int i = 0; i < this->Size; i++)
	{
		this->Vs[i] = H2[i];
	}
	return *this;

}
int HugeInt::STRLEN(char *x)const
{
	int i = 0;
	while (x[i] != '\0')
	{
		i++;
	}
	return i;
}

istream& operator>>(istream & MyCin, HugeInt &HN)
{
	string s;
	cin >> s;
	HN.HNSet(s);
	return MyCin;
}
ostream& operator<<(ostream & MyCout, const HugeInt &HN)
{
	if (HN.Size == 1 && HN[HN.Size - 1] == 0)
	{
		return cout << HN[HN.Size - 1] << endl;
	}
	if (HN.Sign == true)
		cout << "-";

	for (int i = HN.Size - 1; i >= 0; i--)
	{
		cout << HN[i];
	}
	cout << endl;
	return cout;
}



/*-------------------------------------------*/

int HugeInt::Greater(int x, int y)const
{
	if (x > y)
		return x;
	else
	if (x < y)
		return y;
	return y;
}

int HugeInt::operator[](int i)const
{
	if (i >= Size)
	{
		return 0;
	}
	else
	{
		return Vs[i];
	}
}
int& HugeInt::operator[](int i)
{
	return Vs[i]; 
}
void HugeInt::Swap(HugeInt &H1, HugeInt &H2)
{
	HugeInt T = H1;
	H1 = H2;
	H2 = T;
}
int HugeInt::FindZeros()
{
	bool flag = true;
	int count = 0;
	int i = Size - 1;
	while (Vs[i] == 0 && i >= 0)
	{
		i--;
		count++;
	}
	if (Size - count == 0)
		return count - 1;
	else
		return count;
}
void HugeInt::TRIM()
{
	int Zeros = FindZeros();
	if (Zeros != 0)
	{
		int *ptr = new int[Size - Zeros];
		for (int i = Size - Zeros - 1; i >= 0; i--)
		{
			ptr[i] = Vs[i];
		}
		if (Vs)
			delete[]Vs;
		Vs = nullptr;
		Vs = ptr;
		Size = Size - Zeros;
	}
}
int HugeInt::intSize(int x)
{
	int i = 0;
	while (x > 0)
	{
		x /= 10;
		i++;
	}
	return x;
}
void HugeInt::BalancingZeros(HugeInt &H)
{
	if (Size > H.Size)
	{
		int *ptr = new int[Size];
		int j = 0;
		for (; j < H.Size; j++)
		{
			ptr[j] = H.Vs[j];
		}
		for (; j < Size; j++)
		{
			ptr[j] = 0;
		}
		delete H.Vs;
		H.Vs = ptr;
		H.Size = Size;
	}
	else
	if (Size <H.Size)
	{
		int *ptr = new int[H.Size]{0};
		int j = 0;
		for (; j < Size; j++)
		{
			ptr[j] = Vs[j];
		}
		for (; j < H.Size; j++)
		{
			ptr[j] = 0;
		}
		delete Vs;
		Vs = ptr;
		Size = H.Size;
	}
}

HugeInt::~HugeInt()
{
	delete[]Vs;
	Vs = nullptr;
}

