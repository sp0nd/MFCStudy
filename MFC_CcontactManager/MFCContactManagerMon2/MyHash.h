#ifndef _MYHASH_H_
#define _MYHASH_H_
#define AZ 26

#include <string>

using namespace std;

// 버켓에 삽입될 노드 클래스
class NODE
{
public:
    NODE(string _Name, string _HomeTel, string _MobileTel, string _OfficeTel, string _Email, string _Birth)
    {
        Name = _Name;    // 홍길동
        Birth = _Birth;
        HomeTel = _HomeTel;
        MobileTel = _MobileTel;
        OfficeTel = _OfficeTel;
        Email = _Email;
        next = NULL;
    }

    string Name;    // 홍길동
    string Birth;  
    string HomeTel; 
    string MobileTel;
    string OfficeTel;
    string Email;
    NODE* next;
};

// 해시 클래스
class MyHash
{
    NODE** bucketArray; // 버켓 배열
    int bucketSize;     // 버켓 사이즈
public:
    MyHash(int N=26); // 생성자 (디폴트 버켓 사이즈는 26으로 설정)
    ~MyHash();

    NODE* searchNode(const char* _key);
    bool insertNode(string _Name, string _HomeTel, string _MobileTel, string _OfficeTel, string _Email, string _Birth);
    void deleteNode(const char* _key);
    void deleteAll();
    void displayNodes();

    NODE** getBucketArray() { return bucketArray; }
    int getBucketSize() { return bucketSize; }

private:
    int hash_func(const char* key);   // 해시 함수
    double polynomial(const char* b, int n, int idx, double a);   // 다항식 해시코드생성함수
};

#endif