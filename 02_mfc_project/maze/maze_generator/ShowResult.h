#include <iostream>
#include <vector>
using namespace std;

#pragma once


// CShowResult ��ȭ �����Դϴ�.

class CShowResult : public CDialog
{
	DECLARE_DYNAMIC(CShowResult)

public:
	CShowResult(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShowResult();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
