#ifndef _MYHASH_H_
#define _MYHASH_H_
#define AZ 26

#include <string>

using namespace std;

// ���Ͽ� ���Ե� ��� Ŭ����
class NODE
{
public:
    NODE(string _Name, string _HomeTel, string _MobileTel, string _OfficeTel, string _Email, string _Birth)
    {
        Name = _Name;    // ȫ�浿
        Birth = _Birth;
        HomeTel = _HomeTel;
        MobileTel = _MobileTel;
        OfficeTel = _OfficeTel;
        Email = _Email;
        next = NULL;
    }

    string Name;    // ȫ�浿
    string Birth;  
    string HomeTel; 
    string MobileTel;
    string OfficeTel;
    string Email;
    NODE* next;
};

// �ؽ� Ŭ����
class MyHash
{
    NODE** bucketArray; // ���� �迭
    int bucketSize;     // ���� ������
public:
    MyHash(int N=26); // ������ (����Ʈ ���� ������� 26���� ����)
    ~MyHash();

    NODE* searchNode(const char* _key);
    bool insertNode(string _Name, string _HomeTel, string _MobileTel, string _OfficeTel, string _Email, string _Birth);
    void deleteNode(const char* _key);
    void deleteAll();
    void displayNodes();

    NODE** getBucketArray() { return bucketArray; }
    int getBucketSize() { return bucketSize; }

private:
    int hash_func(const char* key);   // �ؽ� �Լ�
    double polynomial(const char* b, int n, int idx, double a);   // ���׽� �ؽ��ڵ�����Լ�
};

#endif