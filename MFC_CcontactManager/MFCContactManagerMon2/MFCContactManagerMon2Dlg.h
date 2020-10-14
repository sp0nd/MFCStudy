
// MFCContactManagerMon2Dlg.h: 헤더 파일
//

#pragma once

#include <string>
#include <vector>
#include "MyHash.h"

using namespace std;
// CMFCContactManagerMon2Dlg 대화 상자
class CMFCContactManagerMon2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCContactManagerMon2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CMFCContactManagerMon2Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCONTACTMANAGERMON2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	MyHash* hash;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnSelchangeMonsterview();
	//int hash_func(string _Name);
	void tockenstring(vector<string>& arr, CString& str);
	void displayhashtoList();
	CString m_strName;
	CString m_strBirth;
	CString m_strEmail;
	CString m_HomeTel;
	CString m_MobileTel;
	CString m_OfficeTel;
	CListBox m_ctrlList;
};
