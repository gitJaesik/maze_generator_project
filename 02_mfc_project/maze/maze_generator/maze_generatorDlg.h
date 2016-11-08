
// maze_generatorDlg.h : ��� ����
//

#pragma once


// Cmaze_generatorDlg ��ȭ ����
class Cmaze_generatorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cmaze_generatorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAZE_GENERATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
