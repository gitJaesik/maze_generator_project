// ShowResult.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "maze_generator.h"
#include "ShowResult.h"
#include "afxdialogex.h"
//#include "MazeFinder.h"
#include "Maze.h"
#include <sstream>

// CShowResult 대화 상자입니다.

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


// CShowResult 메시지 처리기입니다.


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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

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

	dc.SetTextColor(RGB(255, 255, 255));
	//dc.SetBkMode(TRANSPARENT);

	int increament = 10;
	if (strArr.size() < 66) {
		CFont font, *pOldFont;
		font.CreatePointFont(90, _T("Garamond"));
		pOldFont = (CFont*)dc.SelectObject(&font);

		for (int i = 0; i < strArr.size(); i++) {
			for (int j = 0; j < strArr[i].length(); j++) {
				CString charToStr(strArr[i][j]);
				dc.TextOutW(10 + increament * j, startPos + increament * i, charToStr);
			}
		}

		dc.SelectObject(pOldFont);
	}
	else {
		dc.TextOutW(10, startPos, _T("크기가 너무 커서 창에 표현하지 못하였습니다. 출력된 파일을 확인해주세요"));
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

	ifstream input(szMazeFilePath);
	string line;

	while (getline(input, line)) {
		strArr.push_back(line);
	}

	if (strArr.size() == 0)
	{
		return -1;
	}



	return 0;
}
