
// MarioConfig.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMarioConfigApp:
// �� Ŭ������ ������ ���ؼ��� MarioConfig.cpp�� �����Ͻʽÿ�.
//

class CMarioConfigApp : public CWinApp
{
public:
	CMarioConfigApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMarioConfigApp theApp;