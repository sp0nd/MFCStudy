
// MFC_CcontactDlg.cpp: 구현 파일
//
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "pch.h"
#include "framework.h"
#include "MFC_Ccontact.h"
#include "MFC_CcontactDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCcontactDlg 대화 상자



CMFCCcontactDlg::CMFCCcontactDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CCONTACT_DIALOG, pParent)
	, m_strName(_T("kim taejun"))
	, m_srtBirth(_T("1994.03.31"))
	, m_strEmail(_T("sp0nd@naver.com"))
	, m_strHomeTel(_T("051-305-3378"))
	, m_strMobileTel(_T("010-2128-0303"))
	, m_strOfficeTel(_T("음쓰"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCcontactDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Birth, m_strName);
	DDX_Text(pDX, IDC_Birth, m_srtBirth);
	DDX_Text(pDX, IDC_Email, m_strEmail);
	DDX_Text(pDX, IDC_HomeTel, m_strHomeTel);
	DDX_Text(pDX, IDC_MobileTel, m_strMobileTel);
	DDX_Text(pDX, IDC_Name, m_strName);
	DDX_Text(pDX, IDC_OfficeTel, m_strOfficeTel);
	DDX_Control(pDX, IDC_CContactManager, m_strCContactManager);
}

BEGIN_MESSAGE_MAP(CMFCCcontactDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	
	ON_BN_CLICKED(IDC_INSERT, &CMFCCcontactDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_MODIFY, &CMFCCcontactDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_SEARCH, &CMFCCcontactDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_DELETE, &CMFCCcontactDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDOK, &CMFCCcontactDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCCcontactDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_Name, &CMFCCcontactDlg::OnEnChangeName)
	ON_EN_CHANGE(IDC_Birth, &CMFCCcontactDlg::OnEnChangeBirth)
	ON_EN_CHANGE(IDC_HomeTel, &CMFCCcontactDlg::OnEnChangeHometel)
	ON_EN_CHANGE(IDC_MobileTel, &CMFCCcontactDlg::OnEnChangeMobiletel)
	ON_EN_CHANGE(IDC_OfficeTel, &CMFCCcontactDlg::OnEnChangeOfficetel)
	ON_EN_CHANGE(IDC_Email, &CMFCCcontactDlg::OnEnChangeEmail)
	ON_BN_CLICKED(IDC_add, &CMFCCcontactDlg::OnBnClickedadd)
	ON_LBN_SELCHANGE(IDC_CContactManager, &CMFCCcontactDlg::OnSelchangeCcontactmanager)
END_MESSAGE_MAP()


// CMFCCcontactDlg 메시지 처리기

BOOL CMFCCcontactDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCCcontactDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCCcontactDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCCcontactDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCCcontactDlg::OnBnClickedInsert()// Load 이름 실수로 바뀜
{
		//AfxMessageBox(_T("ㄴ"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	FILE* fp = fopen("contact(1).txt","rt");
	if (!fp)
	{
		AfxMessageBox(_T("Can't open file!"));
		return;
	}
	m_strCContactManager.ResetContent();
	char fpln[128];
	while(fgets(fpln,128,fp)!= NULL)
	{
		m_strCContactManager.AddString(fpln);//
		
	}
	fclose(fp);
	
}


void CMFCCcontactDlg::OnBnClickedModify()
{
		//AfxMessageBox(_T("아뇨"));
	UpdateData(TRUE);
	CString str;
	for (int i = 0; i < m_strCContactManager.GetCount(); i++)
	{
		m_strCContactManager.GetText(i,str);

		CStringArray arr;
		tockenstring(arr, str);

		if (arr.GetAt(0) == m_strName)
		{
			str= m_strName + "," + m_srtBirth + "," + m_strHomeTel + "," + m_strMobileTel + "," + m_strOfficeTel + "," + m_strEmail;
			m_strCContactManager.InsertString(i, str);
			m_strCContactManager.DeleteString(i + 1);
			return;
		}

	}
	AfxMessageBox("연락처 내용이 변경되었습니다.");

}


void CMFCCcontactDlg::OnBnClickedSearch()
{
		//AfxMessageBox(_T("아니요"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCCcontactDlg::OnBnClickedDelete()
{
		//AfxMessageBox(_T("Nop"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int nIndex = m_strCContactManager.GetCurSel();
	if ((nIndex == LB_ERR))
	{
		return;
	}
	else
	m_strCContactManager.DeleteString(nIndex);
}

void CMFCCcontactDlg::OnBnClickedOk()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "contact(1).txt", "wt");
	if (err != 0)
	{
		AfxMessageBox("Fail to open file!");
		return;
	}
	CString str;
	for (int i = 0; i < m_strCContactManager.GetCount(); i++)
	{
		m_strCContactManager.GetText(i, str);
		fprintf(fp, "%s\n", (LPCTSTR)str);
	}
	fclose(fp);
	AfxMessageBox("저장되었습니다.");
}


void CMFCCcontactDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CMFCCcontactDlg::OnEnChangeName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCCcontactDlg::OnEnChangeBirth()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCCcontactDlg::OnEnChangeHometel()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCCcontactDlg::OnEnChangeMobiletel()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCCcontactDlg::OnEnChangeOfficetel()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCCcontactDlg::OnEnChangeEmail()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCCcontactDlg::OnBnClickedadd()// insert 기능
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString Aaaa = m_strName + "," + m_srtBirth + "," + m_strHomeTel + "," + m_strMobileTel + "," + m_strOfficeTel + "," + m_strEmail;
	CString str;
	for (int i = 0; i < m_strCContactManager.GetCount(); i++)
	{
		m_strCContactManager.GetText(i, str);

		CStringArray arr;
		tockenstring(arr, str);
		if (arr.GetAt(0) == m_strName)
		{
			AfxMessageBox("이름이 중복됩니다.");
			return;
		}
	}
	 m_strCContactManager.AddString(Aaaa);
	return;

}
void CMFCCcontactDlg::tockenstring(CStringArray& arr, CString& str)
{
	CString t = "";
	for (int i = 0; i < str.GetLength(); i++)
	{
		char s = str.GetAt(i);
		if (s == ',')
		{
			arr.Add(t);
			t = ""; continue;
		}
		t += s;
	}
	arr.Add(t);
}


void CMFCCcontactDlg::OnSelchangeCcontactmanager()
{
	int nsel = m_strCContactManager.GetCurSel();
	if (nsel == LB_ERR)return;

	CString str;
	m_strCContactManager.GetText(nsel, str);

	CStringArray arr;
	tockenstring(arr, str);
	m_strName = arr.GetAt(0);
	m_srtBirth = arr.GetAt(1);
	m_strHomeTel = arr.GetAt(2);
	m_strMobileTel = arr.GetAt(3);
	m_strOfficeTel = arr.GetAt(4);
	m_strEmail = arr.GetAt(5);

	UpdateData(FALSE);

}
