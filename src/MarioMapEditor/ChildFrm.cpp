
// ChildFrm.cpp : CChildFrame Ŭ������ ����
//

#include "stdafx.h"
#include "MarioMapEditor.h"

#include "ChildFrm.h"

#include "MarioMapEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame ����/�Ҹ�

CChildFrame::CChildFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ����

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame �޽��� ó����


void CChildFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		CMarioMapEditorView *pView = (CMarioMapEditorView*)GetActiveView();
		if (pView)
		{
			if (pView->IsPlaying())
			{
				pView->StopPlaying();

				// Wait until stop playing thread
				while (pView->IsPlaying())
				{
					Sleep(500);
				}
			}
		}
	}

	CMDIChildWndEx::OnSysCommand(nID, lParam);
}


void CChildFrame::OnClose()
{
	CMarioMapEditorView *pView = (CMarioMapEditorView*)GetActiveView();
	if (pView)
	{
		if (pView->IsPlaying())
		{
			pView->StopPlaying();
			
			// Wait until stop playing thread
			while (pView->IsPlaying())
			{
				Sleep(500);
			}			
		}
	}

	CMDIChildWndEx::OnClose();
}

