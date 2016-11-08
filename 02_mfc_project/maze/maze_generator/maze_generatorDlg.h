
// maze_generatorDlg.h : 헤더 파일
//

#pragma once


// Cmaze_generatorDlg 대화 상자
class Cmaze_generatorDlg : public CDialogEx
{
// 생성입니다.
public:
	Cmaze_generatorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAZE_GENERATOR_DIALOG };
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
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnEnChangeEditFilepath();
	CString m_strFilePath;
	int m_iWidth;
	int m_iHeight;
	afx_msg void OnEnChangeEditMazeStartx();
	int m_iX;
	int m_iY;
	afx_msg void OnBnClickedButtonGen();
	afx_msg void OnBnClickedButtonShowMaze();
};
