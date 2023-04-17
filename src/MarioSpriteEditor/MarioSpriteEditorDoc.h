#pragma once

#include <vector>
#include "Sprite.h"

#include "SpriteWork.h"
#include "SpritePatchData.h"

#define LOGBASE			NaDebugOut(L"[%s:%05d] ", __FUNCTIONW__, __LINE__); NaDebugOut
#define LOG(arg, ...)	LOGBASE(arg, __VA_ARGS__);

class CMarioSpriteEditorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMarioSpriteEditorDoc();
	DECLARE_DYNCREATE(CMarioSpriteEditorDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMarioSpriteEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	HBITMAP m_hBitmap;
	SIZE m_sizeBitmap;
	Sprite m_Sprite;
	CRect FindSpriteArea(int x, int y);
	SpriteWork m_SpriteWork;
	static int GetEncoderClsid(const wchar_t *format, CLSID *pClsid);
	void RearrangeSprites(CDC *dc, int nMode = 0);
	void PatchThemed(SpritePatchDataVector &vec, CDC *dc);
	void PatchThemedBitmap(wchar_t* szTheme, SpritePatchDataVector &vec, CDC *dc);
	NaString m_strFilename;
	NaString m_strBitmapFilename;

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
