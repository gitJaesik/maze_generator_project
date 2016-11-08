
// maze_generatorDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// Cmaze_generatorDlg ��ȭ ����



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


// Cmaze_generatorDlg �޽��� ó����

BOOL Cmaze_generatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_strFilePath = "output.txt";
	m_iHeight = 64;
	m_iWidth = 64;
	m_iX = 0;
	m_iY = 0;
	UpdateData(FALSE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cmaze_generatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Cmaze_generatorDlg::OnEnChangeEditFilepath()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Cmaze_generatorDlg::OnEnChangeEditMazeStartx()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Cmaze_generatorDlg::OnBnClickedButtonGen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	// �̷� ���� Ŭ���� ��ü ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (FileExists(m_strFilePath) == FALSE) {
		AfxMessageBox(_T("�ùٸ� ������ �ҷ��ּ���!"));
		return;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CShowResult Dlg;
	Dlg.setFilePath(m_strFilePath);
	Dlg.setMode(1);
	if (Dlg.init() == -1) {
		AfxMessageBox(_T("�̷θ� ����� ã�� ���߽��ϴ�. ������ Ȯ�����ּ���!"));
		return;
	}

	INT_PTR nResult = Dlg.DoModal();
	if (nResult == IDOK) {
		//AfxMessageBox(_T("ok ��ư Ŭ��"));
	}


}
