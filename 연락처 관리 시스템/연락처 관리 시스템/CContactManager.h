#ifndef _CCONTACTMANAGER_H
#define _CCONTACTMANAGER_H

#include <string>
using namespace std;


class CONTACT
{
public:
	CONTACT(string Name, string Birth, string HomeTel, string MobileTel, string OfficeTel, string Email)
		:Name(Name), Birth(Birth), HomeTel(HomeTel), MobileTel(MobileTel), OfficeTel(OfficeTel), Email(Email), Next(NULL) {};
	string Name;
	string Birth;//year,month,days
	string HomeTel,MobileTel,OfficeTel;
	string Email;
	CONTACT* Next;

};
class ContactManager // �ؽ�Ŭ����
{
private:
	CONTACT** ContactList;// CONTACT�� �迭
	int Listsize; //ContactList �� ũ��
	int hash_func(string Name);
public:
	ContactManager(int N);
	~ContactManager();
	CONTACT* ContactSearch(string Name);//��ȸ
	void Contactadd(string Name);//�߰�
	void ContactModify(string Name);//����
	void ContactDelete(string Name);//����

};
#endif