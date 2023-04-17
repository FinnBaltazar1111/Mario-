
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"

#include "ResourceHolder.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Tile Block Toolbar
	CMFCToolBar m_wndToolBarBlocks;
	CMFCToolBar m_wndToolBarItems;
	CMFCToolBar m_wndToolBarEnemies;
	CMFCToolBar m_wndToolBarMapObjects;
	CMFCToolBar m_wndToolBarEventObjects;
	CMFCToolBar m_wndToolBarVehicles;
	
	int InitToolbars();
	afx_msg void OnToolBars(UINT id);
	afx_msg void OnUpdateToolBars(CCmdUI* pCmdUI);
	afx_msg void OnTogglePlayedShadow();
	afx_msg void OnUpdateTogglePlayedShadow(CCmdUI* pCmdUI);
	void SetStatusText(int nID, LPCTSTR lpszNewText, BOOL bUpdate = TRUE);

	int m_nCurTool;
	CPropertiesWnd m_wndProperties;
	ResourceHolder* m_pResourceHolder;
	CMarioMapEditorView* m_pActiveView;
	CWinThread *m_pDesignPlayThread;
	bool m_bOnClosing;

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	virtual LRESULT OnChangingActiveTab(WPARAM wparam, LPARAM lparam);
	virtual LRESULT OnChangeActiveTab(WPARAM wparam, LPARAM lparam);

public:
	afx_msg void OnClose();

	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnPlayOnGame();
	afx_msg void OnUpdatePlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlayOnGame(CCmdUI* pCmdUI);

	afx_msg void OnUpdateUpload(CCmdUI* pCmdUI);

	afx_msg void OnStatusBar(UINT id);
	afx_msg void OnUpdateStatusBar(CCmdUI* pCmdUI);
};


