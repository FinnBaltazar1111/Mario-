
// ActivationCodeMaker.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CActivationCodeMakerApp:
// �� Ŭ������ ������ ���ؼ��� ActivationCodeMaker.cpp�� �����Ͻʽÿ�.
//

class CActivationCodeMakerApp : public CWinApp
{
public:
	CActivationCodeMakerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CActivationCodeMakerApp theApp;