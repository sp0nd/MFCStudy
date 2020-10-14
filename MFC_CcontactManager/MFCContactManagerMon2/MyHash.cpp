#include "pch.h"
#include <iostream>
#include "MyHash.h"

using namespace std;

// ������, N : ���ϻ�����
MyHash::MyHash(int N) : bucketSize(N)
{
    // ���� �迭 �ʱ�ȭ
    bucketArray = new NODE * [N];
    for (int i = 0; i < N; i++)   bucketArray[i] = NULL;
}
// �Ҹ���
MyHash::~MyHash()
{
	deleteAll();

    delete [] bucketArray;
}
// b    : Ű�� ���ڿ� �迭�� ������ ����
// n    : Ű�迭�� ����
// idx  : ���� �ε���
// a    : �ؽû��
double MyHash::polynomial(const char* b, int n, int idx, double a)
{
    if (n <= idx+1) return 0.0;
    return (polynomial(b, n, idx+1, a) + (a * b[idx] + b[idx+1]));
}

// Hash �Լ�
int MyHash::hash_func(const char* Name)
{
    // ��� 1 : ������ ����
    //return (_key % bucketSize);

    // ��� 2 : ���׽�(�ؽ��ڵ�) --> ������(����)
    //int n = sizeof(_key);
    //char* b = (char*)malloc(n);
    //memcpy(b, &_key, n);
    //double a = 0.5;

    ////int hcode = (int)polynomial(b, n, 0, a);
    ////free(b);

    //int hcode = (int)polynomial(_key, strlen(_key), 0, a);

    //return (hcode % bucketSize);
    //const char* Name = _Name.c_str();
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

// ���ο� ��� ����
bool MyHash::insertNode(string _Name, string _Birth, string _HomeTel, string _MobileTel, string _OfficeTel, string _Email)
{
    NODE* t = new NODE(_Name, _Birth, _HomeTel, _MobileTel, _OfficeTel, _Email);

    int bucket = hash_func(_Name.c_str());

    if (bucketArray[bucket] == NULL)
        bucketArray[bucket] = t;
    else
    {
        NODE* _t = bucketArray[bucket];
        while (1)
        {
            if (_t->next == NULL) break;
            _t = _t->next;
        }
        _t->next = t;
    }

    return true;
}
// Ű�� �̿��ؼ� ��� ã��
NODE* MyHash::searchNode(const char* _key)
{
    int bucket = hash_func(_key);
    NODE* t = bucketArray[bucket];

    if (t == NULL)  return NULL;

    while (1)
    {
        if (t->Name == _key) return t;
        t = t->next;
        if (t == NULL) break;
    }

    return NULL;
}
// Ű�� �̿��ؼ� ��� �����ϱ�
void MyHash::deleteNode(const char* _key)
{
    int bucket = hash_func(_key);
    NODE* t = bucketArray[bucket];
    NODE* prev = NULL;

    if (t == NULL)  return;

    while (1)
    {
        if (t->Name == _key)
        {
            // ������ ù��° ��尡 ���� ����̸�
            if (prev == NULL)
                bucketArray[bucket] = t->next;
            else
                prev->next = t->next;
            delete t;
            return;
        }
        prev = t;
        t = prev->next;
        if (t == NULL) break;
    }
}
void MyHash::deleteAll()
{
    cout << "deleteAll()" << endl;

    NODE *t, *_t;
    for (int i = 0; i < bucketSize; i++)
    {
        t = bucketArray[i];

        if (t == NULL)  continue;

        while (1)
        {
            _t = t;
            t = t->next;

            delete _t;

            if (t == NULL) break;
        }
        bucketArray[i] = NULL;//�ʱ�ȭ�� ���� ������ bucketarray�� ������ ���� ��������� �޸𸮰� �����ؼ� �����Ͱ� ����Ű�� ������ ã�ư����� ��� ������ ���.
    }
}
void MyHash::displayNodes()
{
    //int count = 0;
    //NODE* t;
    //for (int i = 0; i < bucketSize; i++)
    //{
    //    t = bucketArray[i];

    //    cout << "bucket : " << i;

    //    if (t == NULL)
    //    {
    //        cout << "\tNone" << endl;
    //        continue;
    //    }
    //    cout << "\t";
    //    while (1)
    //    {
    //        count++;
    //        cout << "[" << t->key << "," << t->name << "]";
    //        t = t->next;
    //        if (t == NULL) break;
    //    }
    //    cout << endl;
    //}
    //cout << "==============================================" << endl;
    //cout << "Total Count : " << count << endl;
    //cout << "==============================================" << endl;
}
