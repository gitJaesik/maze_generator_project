#include <iostream>
#include <vector>
using namespace std;

#pragma once


// CShowResult 대화 상자입니다.

class CShowResult : public CDialog
{
	DECLARE_DYNAMIC(CShowResult)

public:
	CShowResult(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShowResult();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int iMode;
	void setMode(int mode);
	CString szMazeFilePath;
	void setFilePath(CString filename);
	afx_msg void OnPaint();
	void DrawBack();
	int init();
	vector<int> otherAnswers;
	int shortestAnswer;
	vector<string> strArr;
};
