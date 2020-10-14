#pragma once
#ifndef _TEXTSEARCHING_H
#define _TEXTSEARCHING_H
#include <iostream>
#include<vector>
using namespace std;
class PatternMatch //�߻�Ŭ����
{
public:
	virtual	int patternmatch(const char* pText, const char* pPtrn) = 0;//���� �����Լ�
	virtual CString getType()=0;// ���������Լ�
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

		const int N_ASCll = 128;/// �ƽ�Ű �ڵ��� ����
		std::vector<int> last(N_ASCll);
		for (int i = 0; i < N_ASCll; i++)/// �ƽ�Ű �ڵ��� �迭�� ���� -1 �� �ʱ�ȭ �ϴ°�
			last[i] = -1;
		for (int i = 0; i < lenPtrn; i++)
			last[pPtrn[i]] = i;
	//  ����=aba �϶� pPtrn[0]=a a�� �ƽ�Ű�ڵ� ���� 97 pPtrn[1]=b b�� �ƽ�Ű�ڵ� ���� 98 last[97]=0 last[98]=1 last[97]= 2<< ù��°�� ���� ���� ������(�������̵�)
	//�ϴ� ������ -1�϶��� ���Ͽ� ���Ե��� �ʾ� �ǳʶ�� ���ؼ��̰�, ���Ͽ� ���Ե� char�� -1�̿��� ��Ʈ���� ���� ���Ͽ� ���ԵǴ��� �ȵǴ��� Ȯ���ϱ� �����̴�.

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