
// maze_path_finder.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cmaze_path_finderApp:
// �� Ŭ������ ������ ���ؼ��� maze_path_finder.cpp�� �����Ͻʽÿ�.
//

class Cmaze_path_finderApp : public CWinApp
{
public:
	Cmaze_path_finderApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cmaze_path_finderApp theApp;