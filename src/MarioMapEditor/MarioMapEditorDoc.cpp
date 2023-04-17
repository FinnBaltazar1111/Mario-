
// MarioMapEditorDoc.cpp : CMarioMapEditorDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MarioMapEditor.h"
#endif

#include "MarioMapEditorDoc.h"

#include <propkey.h>

#include "Game.h"
#include "Stage.h"
#include "DesignStage.h"
#include "MapObjectBase.h"
#include "GameObjectBase.h"
#include "MapObjectPipe.h"
#include "json.h"
#include "MainFrm.h"
#include "ResourceHolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMarioMapEditorDoc

IMPLEMENT_DYNCREATE(CMarioMapEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMarioMapEditorDoc, CDocument)
END_MESSAGE_MAP()


// CMarioMapEditorDoc ����/�Ҹ�

CMarioMapEditorDoc::CMarioMapEditorDoc()
{
	m_pGame = new DesignGame;
	m_pGame->m_pResourceHolder = ((CMainFrame*)theApp.GetMainWnd())->m_pResourceHolder;

	m_strPathName = L"";
	m_bCreated = false;
}

CMarioMapEditorDoc::~CMarioMapEditorDoc()
{
	ResourceHolder *pHolder = m_pGame->m_pResourceHolder;
	int nRef = pHolder->m_nRef - 1;
	
	m_pGame->OnExit();
	m_pGame->Release();	
	delete m_pGame;
	m_pGame = nullptr;

	if (nRef == 0)
	{
		((CMainFrame*)theApp.GetMainWnd())->m_pResourceHolder = new ResourceHolder;
		((CMainFrame*)theApp.GetMainWnd())->m_pResourceHolder->m_bUseDirectX = true;
	}
}

BOOL CMarioMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	m_bCreated = true;

	return TRUE;
}

// CMarioMapEditorDoc serialization

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CMarioMapEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CMarioMapEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMarioMapEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMarioMapEditorDoc ����

#ifdef _DEBUG
void CMarioMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMarioMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMarioMapEditorDoc ���


BOOL CMarioMapEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	DesignStage *pStage = (DesignStage*)m_pGame->m_pCurStage;
	m_strPathName = (lpszPathName);

	//pStage->LoadFile(strPathName.cstr());

	return TRUE;
}


BOOL CMarioMapEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	DesignStage *pStage = (DesignStage*)m_pGame->m_pCurStage;
	pStage = (DesignStage*)pStage->GetTopStage();

	CFile file;
	CFileException Err;
	file.Open(lpszPathName, CFile::modeWrite | CFile::modeCreate | CFile::shareDenyNone, &Err);
	
	Json::Value j;
	{
		pStage->SaveJsonMap(j);

		std::string stdstr = j.toStyledString();
		file.Write(stdstr.c_str(), stdstr.length());

		m_strPathName = (lpszPathName);
	}

	file.Close();
	SetModifiedFlag(FALSE);

	return TRUE;
}


void CMarioMapEditorDoc::SetModifiedFlag(BOOL bModified)
{
	ASSERT(this != NULL); 
	m_bModified = bModified;

	if (bModified == TRUE)
	{
		CString str = GetTitle();
		if (str.Right(2).Compare(L" *") != 0)
		{
			CString strNew;
			strNew.Format(L"%s *", str);
			SetTitle(strNew);
		}
	}
	else
	{
		CString str = GetTitle();
		if (str.Right(2).Compare(L" *") == 0)
		{
			CString strNew = str.Left(str.GetLength() - 2);
			SetTitle(strNew);
		}
	}
}