// Lychrel196.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int calculatePalindrome(int num);
void printNum(int* num, int intDigits);
void simplify(int *&num, int &intDigits);
bool compareNums(int* left, int leftIntDigits, int* right, int rightIntDigits);
int divide(int *num, int intDigits, int *&outNum, int &outIntDigits);
void multiply(int *num, int intDigits, int*&outNum, int &outIntDigits);
void add(int *num, int intDigits, int *otherNum, int otherIntdigits, int*&outNum, int &outIntDigits);
void reverse(int *num, int intDigits, int*&outNum, int &outIntDigits);

int main()
{
	int* num;
	int numIntDigits;
	int *originalNum;
	int originalNumID;
	int iterations = 0;
	int *pal;
	int palID;
	//num = new int[1];
	//num[0] = 99999999;
	//numIntDigits = 1;
	//add(num, numIntDigits, num, numIntDigits, num, numIntDigits);
	//printNum(num, numIntDigits);
	//cin.get();

	cout << "Enter a number of int digits: ";
	cin >> originalNumID;
	originalNum = new int[originalNumID];
	for (int i = 0; i < originalNumID; i++)
	{
		cout << "Enter a number: ";
		cin >> originalNum[i];
	}
	numIntDigits = originalNumID;
	num = new int[numIntDigits];
	for (int i = 0; i < originalNumID; i++)
		num[i] = originalNum[i];
	reverse(num, numIntDigits, pal, palID);
	while (!compareNums(num, numIntDigits, pal, palID))
	{
		add(num, numIntDigits, pal, palID, num, numIntDigits);
		iterations++;
		reverse(num, numIntDigits, pal, palID);
	}
	printNum(originalNum, originalNumID);
	cout << " ends up in a palindrome (";
	printNum(num, numIntDigits);
	cout << ") after " << iterations << " iterations.";
	cin.get();
	cin.get();
    return 0;
}

void printNum(int* num, int intDigits)
{
	int digit;
	int tmp;
	for (int i = intDigits - 1; i >= 0; i--)
	{
		if (i == intDigits - 1)
			cout << num[i];
		else
		{
			tmp = num[i];
			for (int j = 100000000; j >= 1; j /= 10)
			{
				digit = tmp / j;
				cout << digit;
				tmp -= digit * j;
			}
		}
	}
}

bool compareNums(int* left, int leftIntDigits, int* right, int rightIntDigits)
{
	if (leftIntDigits != rightIntDigits)
		return false;
	for (int i = 0; i < leftIntDigits; i++)
	{
		if (left[i] != right[i])
			return false;
	}
	return true;
}

void simplify(int *&num, int &intDigits)
{
	if (intDigits == 1) return;
	while (num[intDigits - 1] == 0)
	{
		int* newNum = new int[intDigits - 1];
		for (int i = 0; i < intDigits - 1; i++)
			newNum[i] = num[i];
		num = newNum;
		intDigits -= 1;
	}
}

int divide(int *num, int intDigits, int *&outNum, int &outIntDigits)
{
	int *n = new int[intDigits];
	int nID = intDigits;
	for (int i = 0; i < nID; i++)
		n[i] = num[i];

	int digit = 0;
	int curIntDigit;
	int tmp;
	for (int i = nID - 1; i >= 0; i--)
	{
		curIntDigit = n[i];
		curIntDigit /= 10;
		tmp = n[i] - curIntDigit * 10;
		n[i] = curIntDigit + 100000000 * digit;
		digit = tmp;
	}
	simplify(n, nID);
	outNum = n;
	outIntDigits = nID;
	return digit;
}

void multiply (int *num, int intDigits, int*&outNum, int &outIntDigits)
{
	int *n = new int[intDigits];
	int nID = intDigits;
	for (int i = 0; i < nID; i++)
		n[i] = num[i];

	int digit = 0;
	int tmp;
	for (int i = 0; i < nID; i++)
	{
		tmp = n[i] / 100000000;
		n[i] -= tmp * 100000000;
		n[i] *= 10;
		n[i] += digit;
		digit = tmp;
	}
	if (digit != 0)
	{
		int* newNum = new int[nID + 1];
		for (int i = 0; i < nID; i++)
			newNum[i] = n[i];
		newNum[nID] = digit;
		n = newNum;
		nID++;
	}
	outNum = n;
	outIntDigits = nID;
}

void add(int *num, int intDigits, int *otherNum, int otherIntDigits, int*&outNum, int &outIntDigits)
{
	if (intDigits > otherIntDigits)
		outIntDigits = intDigits + 1;
	else
		outIntDigits = otherIntDigits + 1;
	outNum = new int[outIntDigits];
	bool carry = false;
	for (int i = 0; i <= outIntDigits - 2; i++)
	{
		if (i >= intDigits)
			outNum[i] = otherNum[i]; 
		else if (i >= otherIntDigits)
			outNum[i] = num[i];
		else
			outNum[i] = num[i] + otherNum[i];
		if (carry)
			outNum[i]++;
		if (outNum[i] > 999999999)
		{
			carry = true;
			outNum[i] -= 1000000000;
		}
		else
			carry = false;
	}
	if (carry)
		outNum[outIntDigits - 1] = 1;
	else
		outNum[outIntDigits - 1] = 0;
	simplify(outNum, outIntDigits);
}

void reverse(int *num, int intDigits, int*&outNum, int &outIntDigits)
{
	int *tenth;
	int tenthID;
	int digit;

	int *n = new int[intDigits];
	int nID = intDigits;
	for (int i = 0; i < nID; i++)
		n[i] = num[i];

	outNum = new int[1];
	outIntDigits = 1;
	outNum[0] = 0;
	while (nID > 1 || n[0] > 0)
	{
		digit = n[0] - (n[0] / 10) * 10;
		divide(n, nID, tenth, tenthID);
		multiply(outNum, outIntDigits, outNum, outIntDigits);
		add(outNum, outIntDigits, &digit, 1, outNum, outIntDigits);
		n = tenth;
		nID = tenthID;
	}
}

int calculatePalindrome(int num)
{
	int result = 0;
	while (num > 0)
	{
		int tenth = num / 10;
		int digit = num - tenth * 10;
		result *= 10;
		result += digit;
		num = tenth;
	}
	return result;
}