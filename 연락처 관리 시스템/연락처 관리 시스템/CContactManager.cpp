#include<iostream>
#include<stdlib.h>
#include<string>
#include "CContactManager.h"

using namespace std;


ContactManager::ContactManager(int N) :Listsize(N)
{
	N = 26;
	ContactList = new CONTACT * [N];
	for (int i = 0; i < Listsize; i++)ContactList[i] = NULL;
	//Listsize=����Ʈ�� ��ϵ� �̸��� ��
}
ContactManager::~ContactManager()
{

}
int ContactManager::hash_func(string _Name)
{
	const char* Name = _Name.c_str();
	int n = 0;
	if (Name[0] >= 'A' && Name[0] <= 'Z')
	{
		n = (int)Name[0] - 'A';//���ڸ� �ƽ�Ű�ڵ�� �ٲ㼭 ���
	}
	else if (Name[0] >= 'a' && Name[0] <= 'z')
	{
		n = (int)Name[0] - 'a';
	}
	else
	{
		n = (int)Name[0];
		n = n % 26;
	}
	

	return n;
}
CONTACT* ContactManager::ContactSearch(string _Name)//��ȸ
{
	const char* Name = _Name.c_str();
	int Contact = 0;
	Contact=hash_func(_Name);
	CONTACT* c = ContactList[Contact];
	if (c == NULL) return NULL;
	else if (c != NULL)
	{
		while (1)
		{
			if (c->Name == _Name) 
				return c;
			c = c->Next;
			if (c == NULL) break;
		}
	}
	return NULL;
}
void ContactManager::Contactadd(string Name)//�߰�
{
	CONTACT* c= first;
	if (first == NULL)
	{

	}
}
void ContactManager::ContactModify(string Name)//����
{

}
void ContactManager::ContactDelete(string Name)//����
{

}