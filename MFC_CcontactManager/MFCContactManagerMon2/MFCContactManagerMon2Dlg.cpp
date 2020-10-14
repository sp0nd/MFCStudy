
// MFCContactManagerMon2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCContactManagerMon2.h"
#include "MFCContactManagerMon2Dlg.h"
#include "afxdialogex.h"
#include "MyHash.h"
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


// CMFCContactManagerMon2Dlg 대화 상자



CMFCContactManagerMon2Dlg::CMFCContactManagerMon2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCONTACTMANAGERMON2_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strBirth(_T(""))
	, m_strEmail(_T(""))
	, m_HomeTel(_T(""))
	, m_MobileTel(_T(""))
	, m_OfficeTel(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	hash = new MyHash;
}

CMFCContactManagerMon2Dlg::~CMFCContactManagerMon2Dlg()
{
	delete hash;
}

void CMFCContactManagerMon2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Name, m_strName);
	DDX_Text(pDX, IDC_Birth, m_strBirth);
	DDX_Text(pDX, IDC_Email, m_strEmail);
	DDX_Text(pDX, IDC_HomeTel, m_HomeTel);
	DDX_Text(pDX, IDC_MobileTel, m_MobileTel);
	DDX_Text(pDX, IDC_OfficeTel, m_OfficeTel);
	DDX_Control(pDX, IDC_MONSTERVIEW, m_ctrlList);
}

BEGIN_MESSAGE_MAP(CMFCContactManagerMon2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, &CMFCContactManagerMon2Dlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_INSERT, &CMFCContactManagerMon2Dlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_MODIFY, &CMFCContactManagerMon2Dlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_DELETE, &CMFCContactManagerMon2Dlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_SAVE, &CMFCContactManagerMon2Dlg::OnBnClickedSave)
	ON_BN_CLICKED(IDCANCEL, &CMFCContactManagerMon2Dlg::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_MONSTERVIEW, &CMFCContactManagerMon2Dlg::OnLbnSelchangeMonsterview)
END_MESSAGE_MAP()


// CMFCContactManagerMon2Dlg 메시지 처리기

BOOL CMFCContactManagerMon2Dlg::OnInitDialog()
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

void CMFCContactManagerMon2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCContactManagerMon2Dlg::OnPaint()
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
HCURSOR CMFCContactManagerMon2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


///////////////////////////////// 버튼 시작////////////////////////////////////////

void CMFCContactManagerMon2Dlg::OnBnClickedLoad()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "contact.txt", "rt");
	if (fp == 0)
	{
		AfxMessageBox(_T("Can't open file!"));
		return;
	}

	/*if (hash)	delete hash;
	hash = new MyHash;*/
	hash->deleteAll();// 리스트를 리셋을 해도 해시에 값이 남아있기 때문에 해시에 남아있는 값이 계속 로드되서 같은 값이 계속 추가 안되게 해시도 지웠다가 다시 생성한다.

	m_ctrlList.ResetContent();
	char fpln[128];
	while (fgets(fpln, 128, fp) != NULL)
	{
		if (fpln[strlen(fpln) - 1] == '\n')
			fpln[strlen(fpln) - 1] = '\0';

		if (strlen(fpln) != 0)
		{
			CString str(fpln);
			vector<string> arr;
			tockenstring(arr, str);

			hash->insertNode(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
		}
	}
	fclose(fp);
	displayhashtoList();
}


void CMFCContactManagerMon2Dlg::OnBnClickedInsert()
{
	UpdateData(TRUE);
	
	if (hash->searchNode(m_strName))
	{
		AfxMessageBox(_T("데이터가 중복됩니다."));
		return;
	}
	string Name(m_strName), Birth(m_strBirth), Hometel(m_HomeTel), Mobiletel(m_MobileTel), Officetel(m_OfficeTel), Email(m_strEmail);
	hash->insertNode(Name,Birth,Hometel,Mobiletel,Officetel,Email);

	displayhashtoList();
}


void CMFCContactManagerMon2Dlg::OnBnClickedModify()
{
		
	
	if (hash->searchNode(m_strName))
	{
		//(LPSTR)(LPCTSTR)m_strName = string Name(m_strName)
		string Name(m_strName), Birth(m_strBirth), Hometel(m_HomeTel), Mobiletel(m_MobileTel), Officetel(m_OfficeTel), Email(m_strEmail);
		hash->insertNode(Name, Birth, Hometel, Mobiletel, Officetel, Email);
		hash->deleteNode(m_strName);
		displayhashtoList();
		return;
	}
//	for (int i = 0; i < m_ctrlList.GetCount(); i++)
//	{
//		m_ctrlList.GetText(i, str);
//
//		vector<string> arr;
//		tockenstring(arr, str);
//
//		string tstr = m_strName;
////		string tstr(m_strName);
//
//		if (arr.at(0) == tstr)//arr.at(0)==m_strName 은 타입이 안맞아서 타입캐스팅을 해줘야함 ->  1번 string tstr = m_strName;
//																					      //      2번 string tstr(m_strName);
//		{
//			str= m_strName + "," + m_strBirth + "," + m_HomeTel + "," + m_MobileTel + "," + m_OfficeTel + "," + m_strEmail;
//			m_ctrlList.InsertString(i, str);
//			m_ctrlList.DeleteString(i + 1);
//			displayhashtoList();
//			return;
//		}
//	}
	AfxMessageBox("연락처 내용이 변경되었습니다.");
}


void CMFCContactManagerMon2Dlg::OnBnClickedDelete()
{
	hash->deleteNode(m_strName);
	displayhashtoList();
}


void CMFCContactManagerMon2Dlg::OnBnClickedSave()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "contact.txt", "wt");
	if (err != 0)
	{
		AfxMessageBox("Fail to open file !");
		return;
	}
	CString str;
	for (int i = 0; i < m_ctrlList.GetCount(); i++)
	{
		m_ctrlList.GetText(i, str);
		fprintf(fp, "%s\n", (LPCTSTR)str);
	}
	fclose(fp);
	AfxMessageBox("저장되었습니다.");
}


void CMFCContactManagerMon2Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
/////////////////////////////////// 버튼 끝/////////////////////////////////////////
/////////////////////////////////// 리스트 시작///////////////////////////////////////

void CMFCContactManagerMon2Dlg::OnLbnSelchangeMonsterview()
{
	int nsel = m_ctrlList.GetCurSel();
	if (nsel == LB_ERR)return;

	CString str;
	m_ctrlList.GetText(nsel, str);
	vector<string> arr;
	tockenstring(arr, str);



	//char* aaa = "asdf";
	//CString ts = aaa;CString은 리턴타입으로 'char*' 타입을 받을수 있다.
	//const char* ddd = arr[0].c_str();// 2. char* ddd=(char*)arr[0].c_str();
	//CString tt = ddd;
	//c_str()함수가 리턴하는것이 const char*로 반환한다




	m_strName = arr[0].c_str();
	m_strBirth = arr[1].c_str();
	m_HomeTel = arr[2].c_str();
	m_MobileTel = arr[3].c_str();
	m_OfficeTel = arr[4].c_str();
	m_strEmail = arr[5].c_str();
	UpdateData(FALSE);
}
/////////////////////////////////// 리스트 끝/////////////////////////////////////////
//int CMFCContactManagerMon2Dlg::hash_func(string _Name)
//{
//	const char* Name = _Name.c_str();
//	int n = 0;
//	if (Name[0] >= 'A' && Name[0] <= 'Z')
//	{
//		n = (int)Name[0] - 'A';//문자를 아스키코드로 바꿔서 계산
//	}
//	else if (Name[0] >= 'a' && Name[0] <= 'z')
//	{
//		n = (int)Name[0] - 'a';
//	}
//	else
//	{
//		n = (int)Name[0];
//		n = n % 26;
//	}
//
//
//	return n;
//}
void CMFCContactManagerMon2Dlg::tockenstring(vector<string>& arr, CString& str)
{
	string t = "";
	for (int i = 0; i < str.GetLength(); i++)
	{
		char s = str.GetAt(i);
		if (s == ',')
		{
			arr.push_back(t);
			t = ""; continue;
		}
		t += s;
	}
	arr.push_back(t);
	
}
void CMFCContactManagerMon2Dlg::displayhashtoList()
{
	m_ctrlList.ResetContent();

	NODE** bucketArray = hash->getBucketArray();
	for (int i = 0; i < hash->getBucketSize() ; i++)
	{
		NODE* t = bucketArray[i];
		if (t == NULL) continue;
		while (1)
		{
			string str = t->Name + "," + t->Birth + "," + t->HomeTel + "," + t->MobileTel + "," + t->OfficeTel + "," + t->Email;
			m_ctrlList.AddString(str.c_str());

			t = t->next;
			if (t == NULL)break;
		}
	}
}
