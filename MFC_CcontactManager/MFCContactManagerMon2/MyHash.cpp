#include "pch.h"
#include <iostream>
#include "MyHash.h"

using namespace std;

// 생성자, N : 버켓사이즈
MyHash::MyHash(int N) : bucketSize(N)
{
    // 버켓 배열 초기화
    bucketArray = new NODE * [N];
    for (int i = 0; i < N; i++)   bucketArray[i] = NULL;
}
// 소멸자
MyHash::~MyHash()
{
	deleteAll();

    delete [] bucketArray;
}
// b    : 키를 문자열 배열로 변경한 변수
// n    : 키배열의 길이
// idx  : 현재 인덱스
// a    : 해시상수
double MyHash::polynomial(const char* b, int n, int idx, double a)
{
    if (n <= idx+1) return 0.0;
    return (polynomial(b, n, idx+1, a) + (a * b[idx] + b[idx+1]));
}

// Hash 함수
int MyHash::hash_func(const char* Name)
{
    // 방법 1 : 나머지 연산
    //return (_key % bucketSize);

    // 방법 2 : 다항식(해시코드) --> 나머지(압축)
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
        n = (int)Name[0] - 'A';//문자를 아스키코드로 바꿔서 계산
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

// 새로운 노드 삽입
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
// 키를 이용해서 노드 찾기
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
// 키를 이용해서 노드 삭제하기
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
            // 버켓의 첫번째 노드가 삭제 대상이면
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
        bucketArray[i] = NULL;//초기화를 하지 않으면 bucketarray에 가비지 값이 들어있으면 메모리가 부족해서 포인터가 가리키는 곳으로 찾아갈수가 없어서 에러가 뜬다.
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
