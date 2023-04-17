
// MarioSpriteEditorView.h : CMarioSpriteEditorView Ŭ������ �������̽�
//

#pragma once

#include "SpriteListCtrl.h"
#include "MarioSpriteEditorDoc.h"

class AnimationTestDlg;
class CMarioSpriteEditorView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CMarioSpriteEditorView();
	DECLARE_DYNCREATE(CMarioSpriteEditorView)

// Ư���Դϴ�.
public:
	CMarioSpriteEditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	enum { IDD = IDD_MARIOSPRITEFORMVIEW };
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CMarioSpriteEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	bool m_bLoadCompleted;
	int m_nZoomFactor;
	CSpriteListCtrl m_listSprite;
	CRect m_rcCurrentArea;
	void UpdateListItem(int nIdx);
	void SelectListItem(int nIdx);
	void ClearListItems();
	int GetSelectedListIndex();
	SpriteFrame* GetSelectedSpriteFrame();
	void RefreshProperties();
	bool RefreshSelection();
	AnimationTestDlg *m_pAnimationTestDlg;

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddSprite();
	afx_msg void OnBnClickedButtonDeleteSprite();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLvnItemchangedListSprite(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonInsertSprite();
	afx_msg void OnBnClickedBtnOffsetLefttop();
	afx_msg void OnBnClickedBtnOffsetCenterbottom();
	afx_msg void OnBnClickedBtnOffsetCenter();
	afx_msg void OnBnClickedBtnOffsetRightmiddle();
	afx_msg void OnRearrange();
	afx_msg void OnRearrange8x();
	LRESULT OnLoadDialogComplete(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnShowAnimationTest();
};

#ifndef _DEBUG  // MarioSpriteEditorView.cpp�� ����� ����
inline CMarioSpriteEditorDoc* CMarioSpriteEditorView::GetDocument() const
   { return reinterpret_cast<CMarioSpriteEditorDoc*>(m_pDocument); }
#endif

