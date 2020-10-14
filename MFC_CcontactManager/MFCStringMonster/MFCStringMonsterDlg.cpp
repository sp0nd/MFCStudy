
// MFCStringMonsterDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCStringMonster.h"
#include "MFCStringMonsterDlg.h"
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


// CMFCStringMonsterDlg 대화 상자



CMFCStringMonsterDlg::CMFCStringMonsterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTRINGMONSTER_DIALOG, pParent)
	, m_strFilename(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pTree = new TrieTree;
}
CMFCStringMonsterDlg::~CMFCStringMonsterDlg()
{
	delete m_pTree;
}

void CMFCStringMonsterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TextList, m_ctrlTL);
	DDX_Control(pDX, IDC_TextarrayList, m_ctrlTAL);
	DDX_Control(pDX, IDC_SearcharrayList, m_ctrlSAL);
	DDX_Text(pDX, IDC_Filename, m_strFilename); 
}

BEGIN_MESSAGE_MAP(CMFCStringMonsterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, &CMFCStringMonsterDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_SEARCH, &CMFCStringMonsterDlg::OnBnClickedSearch)
	ON_EN_CHANGE(IDC_Filename, &CMFCStringMonsterDlg::OnEnChangeFilename)
END_MESSAGE_MAP()


// CMFCStringMonsterDlg 메시지 처리기

BOOL CMFCStringMonsterDlg::OnInitDialog()
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

void CMFCStringMonsterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCStringMonsterDlg::OnPaint()
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
HCURSOR CMFCStringMonsterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCStringMonsterDlg::OnBnClickedLoad()
{
	TCHAR szFilters[] = _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");//|data files(*.dat)|*.dat|

	CFileDialog fdlg(TRUE,_T("*.txt"),NULL,OFN_HIDEREADONLY,szFilters);

	if(fdlg.DoModal()!=IDOK)return;

	m_strFilename = fdlg.GetPathName();

	CStdioFile file;
	if (!file.Open(m_strFilename, CFile::modeRead))
	{
		AfxMessageBox(_T("Fail to Opne!"));
		return;
	}

	// 리스트박스 스트링 초기화
	m_ctrlTL.ResetContent();
	//트라이 초기화
	m_pTree->reset();

	int row = 0;  //문자열 row 값
	CString str, tstr;
	while (file.ReadString(str))// 한줄 읽기
	{
		str.MakeUpper();// 대문자로 변환
		tstr.Format(_T("[%d]%s"),row,(LPCTSTR)str);
		m_ctrlTL.AddString(tstr);//리스트 박스에 추가
	}
	//trie에 삽입할 단어로 분리
	vector<CString> arr;
	vector<int> idxs;
	int cnt = tockenstring(arr, idxs, str);

	//분리된 단어를 트리에 insert
	if (0 < cnt)
	{
		for (int i = 0; i < cnt; i++)
		{
			tstr.Format(_T("[%d][%d],%s"), row, idxs[i], (LPCTSTR)arr[i]);

			// 이미 존재하는 단어이지 점검
			TrieTree* ret = m_pTree->find(arr[i]);

			if (ret)
			{
				ret->insert(ret, row, idxs[i]);
			}
			else
			{
				m_pTree->insert(arr[i], row, idxs[i]);
			}
			m_ctrlTAL.AddString(tstr);
		}
	}
	row++;
}
int CMFCStringMonsterDlg::tockenstring(vector<CString>& arr, vector<int>& idxs, CString& str)
{
	CString t = "";
	int size = str.GetLength();
	int cnt = -1;
	for (int i = 0; i < size; i++)
	{
		char ch = str.GetAt(i);
		if (ch < 'A' || ch>'Z')
		{
			if (t.GetLength() > 0)
			{
				arr.push_back(t);
				idxs.push_back(t);
				t = "";
				cnt = -1;
			}
		}
		t += ch;
		if (cnt < 0)
			cnt = i;
	}
	if (t.GetLength() > 0)
	{
		arr.push_back(t);
		idxs.push_back(t);
		t = "";
		cnt = -1;
	}

}

void CMFCStringMonsterDlg::OnBnClickedSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCStringMonsterDlg::OnEnChangeFilename()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
