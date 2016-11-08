
// maze_generatorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "maze_generator.h"
#include "maze_generatorDlg.h"
#include "afxdialogex.h"
#include "Maze.h"
#include "ShowResult.h"

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


// Cmaze_generatorDlg 대화 상자



Cmaze_generatorDlg::Cmaze_generatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAZE_GENERATOR_DIALOG, pParent)
	, m_strFilePath(_T(""))
	, m_iWidth(0)
	, m_iHeight(0)
	, m_iX(0)
	, m_iY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmaze_generatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_strFilePath);
	DDX_Text(pDX, IDC_EDIT_MAZE_WIDTH, m_iWidth);
	DDV_MinMaxInt(pDX, m_iWidth, 2, 254);
	DDX_Text(pDX, IDC_EDIT_MAZE_HEIGHT, m_iHeight);
	DDV_MinMaxInt(pDX, m_iHeight, 2, 254);
	DDX_Text(pDX, IDC_EDIT_MAZE_STARTX, m_iX);
	DDV_MinMaxInt(pDX, m_iX, 0, 122);
	DDX_Text(pDX, IDC_EDIT_MAZE_STARTY, m_iY);
	DDV_MinMaxInt(pDX, m_iY, 0, 122);
}

BEGIN_MESSAGE_MAP(Cmaze_generatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &Cmaze_generatorDlg::OnBnClickedButtonSave)
	ON_EN_CHANGE(IDC_EDIT_FILEPATH, &Cmaze_generatorDlg::OnEnChangeEditFilepath)
	ON_EN_CHANGE(IDC_EDIT_MAZE_STARTX, &Cmaze_generatorDlg::OnEnChangeEditMazeStartx)
	ON_BN_CLICKED(IDC_BUTTON_GEN, &Cmaze_generatorDlg::OnBnClickedButtonGen)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_MAZE, &Cmaze_generatorDlg::OnBnClickedButtonShowMaze)
END_MESSAGE_MAP()


// Cmaze_generatorDlg 메시지 처리기

BOOL Cmaze_generatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	m_strFilePath = "output.txt";
	m_iHeight = 64;
	m_iWidth = 64;
	m_iX = 0;
	m_iY = 0;
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cmaze_generatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cmaze_generatorDlg::OnPaint()
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
HCURSOR Cmaze_generatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmaze_generatorDlg::OnBnClickedButtonSave()
{
	CString strTmp = _T("");
	CFileDialog Dlg(FALSE, _T("txt"), NULL,
		OFN_OVERWRITEPROMPT,
		_T("TXT Files(*.txt)|*.txt|All Files(*.*)|*.*||"), this);

	if (Dlg.DoModal() == IDOK) {
		strTmp.Format(_T("%s"), Dlg.GetFileName());
		m_strFilePath = Dlg.GetPathName();
		UpdateData(false);
		
		//AfxMessageBox(strTmp);
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Cmaze_generatorDlg::OnEnChangeEditFilepath()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Cmaze_generatorDlg::OnEnChangeEditMazeStartx()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Cmaze_generatorDlg::OnBnClickedButtonGen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	// 미로 생성 클래스 객체 생성
	Maze mz;
	mz.setMazeHeight(m_iHeight);
	mz.setMazeWidth(m_iWidth);
	mz.setStart(m_iY, m_iX);
	//mz.setMazeFileName("C:\\Users\\Phee\\Documents\\Visual Studio 2015\\Projects\\pnp\\output.txt");

	CT2CA pszConvertedAnsiString(m_strFilePath);
	string str(pszConvertedAnsiString);
	mz.setMazeFileName(str);

	mz.maze_start();

}


BOOL FileExists(LPCTSTR lpszFileName)
{
	CFile fil;
	if (fil.Open(lpszFileName, CFile::modeRead | CFile::shareDenyNone))
	{
		// Open succeeded, file exists 
		fil.Close();
		return TRUE;
	}
	// Open failed because file not found 
	if (ERROR_FILE_NOT_FOUND == ::GetLastError()) return FALSE;
	// Open failed because directory inaccessible or other failure 
	CFileException::ThrowOsError((LONG)::GetLastError());
	return FALSE;
}

void Cmaze_generatorDlg::OnBnClickedButtonShowMaze()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (FileExists(m_strFilePath) == FALSE) {
		AfxMessageBox(_T("올바른 파일을 불러주세요!"));
		return;
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CShowResult Dlg;
	Dlg.setFilePath(m_strFilePath);
	Dlg.setMode(1);
	if (Dlg.init() == -1) {
		AfxMessageBox(_T("미로를 제대로 찾지 못했습니다. 파일을 확인해주세요!"));
		return;
	}

	INT_PTR nResult = Dlg.DoModal();
	if (nResult == IDOK) {
		//AfxMessageBox(_T("ok 버튼 클릭"));
	}


}
