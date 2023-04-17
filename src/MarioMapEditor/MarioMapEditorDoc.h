
// MarioMapEditorDoc.h : CMarioMapEditorDoc Ŭ������ �������̽�
//


#pragma once

#include "DesignGame.h"

class CMarioMapEditorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMarioMapEditorDoc();
	DECLARE_DYNCREATE(CMarioMapEditorDoc)

// Ư���Դϴ�.
public:
	bool m_bCreated;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMarioMapEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DesignGame *m_pGame;
	NaString m_strPathName;
	virtual void SetModifiedFlag(BOOL bModified = TRUE);

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
