
// maze_generator.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cmaze_generatorApp:
// �� Ŭ������ ������ ���ؼ��� maze_generator.cpp�� �����Ͻʽÿ�.
//

class Cmaze_generatorApp : public CWinApp
{
public:
	Cmaze_generatorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cmaze_generatorApp theApp;