
// MarioMapEditor.h : MarioMapEditor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#include <DbgHelp.h>

// CMarioMapEditorApp:
// �� Ŭ������ ������ ���ؼ��� MarioMapEditor.cpp�� �����Ͻʽÿ�.
//

class CMarioMapEditorApp : public CWinAppEx
{
public:
	CMarioMapEditorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	static LONG WINAPI CrashHandler(EXCEPTION_POINTERS* pException);
};

extern CMarioMapEditorApp theApp;
