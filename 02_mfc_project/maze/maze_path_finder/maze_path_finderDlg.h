
// maze_path_finderDlg.h : ��� ����
//

#pragma once


// Cmaze_path_finderDlg ��ȭ ����
class Cmaze_path_finderDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cmaze_path_finderDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAZE_PATH_FINDER_DIALOG };
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
	afx_msg void OnBnClickedButtonOpen();
	CString m_strFilePath;
	afx_msg void OnBnClickedButtonFindMaze();
};
