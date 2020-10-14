#pragma once
#ifndef _TEXTSEARCHING_H
#define _TEXTSEARCHING_H
#include <iostream>
#include<vector>
using namespace std;
class PatternMatch //추상클래스
{
public:
	virtual	int patternmatch(const char* pText, const char* pPtrn) = 0;//순수 가상함수
	virtual CString getType()=0;// 순수가상함수
};
class BF :public PatternMatch
{
public:
	
	int patternmatch(const char* pText, const char* pPtrn)
	{
		int lenText = (int)strlen(pText);
		int lenPtrn = (int)strlen(pPtrn);

		int i = 0; // pText
		int j = 0; // pPtrn
		while (1)
		{
			if ((lenText - lenPtrn) < i)	break;

			int idx = i;
			while(pText[idx] == pPtrn[j])
			{
				idx++;
				j++;

				if (j == lenPtrn)
					return i;
			}
			j = 0;
			i++;
		}

		return -1;
	}
	CString getType() { return CString("BF"); }
};
class BM : public PatternMatch
{
private:
	std::vector<int> buildLastFunction(const char* pPtrn)
	{
		int lenPtrn = (int)strlen(pPtrn);

		const int N_ASCll = 128;/// 아스키 코드의 갯수
		std::vector<int> last(N_ASCll);
		for (int i = 0; i < N_ASCll; i++)/// 아스키 코드의 배열의 값을 -1 로 초기화 하는것
			last[i] = -1;
		for (int i = 0; i < lenPtrn; i++)
			last[pPtrn[i]] = i;
	//  패턴=aba 일때 pPtrn[0]=a a의 아스키코드 값은 97 pPtrn[1]=b b의 아스키코드 값은 98 last[97]=0 last[98]=1 last[97]= 2<< 첫번째로 들어갔던 값을 덮어씌운다(오버라이딩)
	//하는 이유는 -1일때는 패턴에 포함되지 않아 건너띄기 위해서이고, 패턴에 포함된 char는 -1이외의 인트값을 가져 패턴에 포함되는지 안되는지 확인하기 위함이다.

		return last;
	}
public:
	int patternmatch(const char* pText, const char* pPtrn)
	{
		int lenText = (int)strlen(pText);
		int lenPtrn = (int)strlen(pPtrn);

		std::vector<int>last = buildLastFunction(pPtrn);
		int i = lenPtrn - 1;
		if (lenText - 1 < i)
			return -1;

		int j = lenPtrn - 1;
		do
		{ 
			if (pPtrn[j] == pText[i])
				if (j == 0)return i;
				else
				{
					i--; j--;
				}
			else
			{
				i = i + lenPtrn - min(j, 1 + last[pText[i]]);
				j = lenPtrn - 1;
			}
		} while (i <= lenText - 1);
		return -1;

	}
	CString getType() { return CString("BM"); }
};
#endif