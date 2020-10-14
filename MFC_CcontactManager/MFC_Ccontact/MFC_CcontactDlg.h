
// MFC_CcontactDlg.h: 헤더 파일
//

#pragma once


// CMFCCcontactDlg 대화 상자
class CMFCCcontactDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCCcontactDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CCONTACT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	CString m_srtBirth;
	CString m_strEmail;
	CString m_strHomeTel;
	CString m_strMobileTel;
	CString m_strName;
	CString m_strOfficeTel;
	void tockenstring(CStringArray& arr, CString& str);
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeName();
	afx_msg void OnEnChangeBirth();
	afx_msg void OnEnChangeHometel();
	afx_msg void OnEnChangeMobiletel();
	afx_msg void OnEnChangeOfficetel();
	afx_msg void OnEnChangeEmail();
	CListBox m_strCContactManager;
	afx_msg void OnBnClickedadd();
	afx_msg void OnSelchangeCcontactmanager();
};
