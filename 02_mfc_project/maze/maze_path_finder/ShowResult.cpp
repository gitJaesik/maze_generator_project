// ShowResult.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "maze_path_finder.h"
#include "ShowResult.h"
#include "afxdialogex.h"
#include "MazeFinder.h"


// CShowResult ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShowResult, CDialog)

CShowResult::CShowResult(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_SHOW_RESULT, pParent)
	, iMode(0)
	, szMazeFilePath(_T(""))
	, shortestAnswer(0)
{
}

CShowResult::~CShowResult()
{
}

void CShowResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowResult, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CShowResult �޽��� ó�����Դϴ�.


void CShowResult::setMode(int mode)
{
	iMode = mode;
}


void CShowResult::setFilePath(CString filename)
{
	szMazeFilePath = filename;
}


void CShowResult::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CDialog::OnPaint();
	DrawBack();
}


void CShowResult::DrawBack()
{
	CClientDC dc(this);

	CPen MyPen(PS_SOLID, 0, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&MyPen);

	CBrush MyBrush(RGB(0, 0, 0));
	CBrush *oldBrush = dc.SelectObject(&MyBrush);

	CWnd* pCtrl = this;
	CRect rectCtrl;
	pCtrl->GetWindowRect(rectCtrl);

	dc.Rectangle(10, 10, 1200, 700);


	//dc.SelectObject(oldPen);
	//CPen MyPen2(PS_SOLID, 0, RGB(255, 255, 255));
	//oldPen = dc.SelectObject(&MyPen2);

	dc.SetBkColor(RGB(0, 0, 0));
	int startPos = 10;

	dc.SetTextColor(RGB(200, 200, 0));
	CString answerTemplate = _T("=============================================== Goal");

	for (int i = 0; i < otherAnswers.size(); i++) {
		CString strGoal;
		strGoal.Format(_T("%s  (%d)"), answerTemplate, otherAnswers[i]);
		dc.TextOutW(10, startPos, strGoal);
		startPos += 20;
	}

	if (otherAnswers.size() != 0) {
		startPos += 40;
	}

	CString strShortestPath;
	strShortestPath.Format(_T("=============================================== Shortest Distance (%d)"), shortestAnswer);
	dc.TextOutW(10, startPos, strShortestPath);
	startPos += 20;



	dc.SetTextColor(RGB(255, 255, 255));
	//dc.SetBkMode(TRANSPARENT);

	int increament = 8.5;
	if (strArr.size() < 66) {
		CFont font, *pOldFont;
		font.CreatePointFont(85, _T("Garamond"));
		pOldFont = (CFont*)dc.SelectObject(&font);

		for (int i = 0; i < strArr.size() - 1; i++) {
			for (int j = 0; j < strArr[i].length(); j++) {
				//dc.TextOutW(10, loc, szGraph[i]);
				CString charToStr(strArr[i][j]);
				dc.TextOutW(10 + increament * j, startPos + increament * i, charToStr);
			}
		}

		dc.SelectObject(pOldFont);
	}
	else {
		dc.TextOutW(10, startPos, _T("ũ�Ⱑ �ʹ� Ŀ�� â�� ǥ������ ���Ͽ����ϴ�. outputWithShortestPath.txt ������ Ȯ�����ּ���"));
	}
	//dc.TextOut(10, 10, szGraph);

	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
}


vector<string> split(const string &s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

int CShowResult::init()
{
	// MazeFinder class ���
	CMazeFinder mazeFinder;

	CT2CA pszConvertedAnsiString(szMazeFilePath);
	string str(pszConvertedAnsiString);

	mazeFinder.setFilePath(str);

	if (mazeFinder.findMaze() == -1) {
		return -1;
	}


	string strMazeGraph = mazeFinder.mazeGraph();

	ofstream out("outputWithShortestPath.txt");
	out << strMazeGraph;
	out.close();

	strArr = split(strMazeGraph, '\n');

	shortestAnswer = mazeFinder.shortestPathDepth;

	otherAnswers = mazeFinder.getOtherPaths();

	return 0;
}
