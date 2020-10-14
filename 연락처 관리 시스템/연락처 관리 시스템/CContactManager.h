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
class ContactManager // 해시클래스
{
private:
	CONTACT** ContactList;// CONTACT의 배열
	int Listsize; //ContactList 의 크기
	int hash_func(string Name);
public:
	ContactManager(int N);
	~ContactManager();
	CONTACT* ContactSearch(string Name);//조회
	void Contactadd(string Name);//추가
	void ContactModify(string Name);//수정
	void ContactDelete(string Name);//삭제

};
#endif