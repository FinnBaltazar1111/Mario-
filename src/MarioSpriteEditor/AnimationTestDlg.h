#pragma once
#include "afxcmn.h"

#include "Sprite.h"
#include "afxwin.h"

// AnimationTestDlg ��ȭ �����Դϴ�.

class CMarioSpriteEditorView;
class AnimationTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AnimationTestDlg)

public:
	AnimationTestDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~AnimationTestDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATION_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void Init();
	int GetSelectedListIndex();
	void SelectListItem(int nIdx);
	SpriteFrame GetCurSpriteFrame();
	int GetCurAnimationFrameCount();

	CMarioSpriteEditorView *m_pMainView;
	CListCtrl m_List;
	CEdit m_Edit;
	int m_nCurFrame;
	int m_nZoomFactor;
	int m_nCurRow, m_nCurCol;
};
