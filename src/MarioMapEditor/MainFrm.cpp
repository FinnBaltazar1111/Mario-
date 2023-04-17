
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "MarioMapEditor.h"

#include "MainFrm.h"

#include "../NaLib/NaCommon.h"

#include "MarioMapEditorDoc.h"
#include "MarioMapEditorView.h"

#include "Game.h"
#include "Stage.h"
#include "DesignStage.h"

#include "PathManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_UPDATE_COMMAND_UI(ID_FILE_UPLOAD, &CMainFrame::OnUpdateUpload)
	// Toolbars
	ON_COMMAND_RANGE(ID_BTN__________________________BLOCKS_START, ID_BTN__________________________VEHICLES_END, &CMainFrame::OnToolBars)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BTN__________________________BLOCKS_START, ID_BTN__________________________VEHICLES_END, &CMainFrame::OnUpdateToolBars)
	ON_COMMAND(ID_BTN_TOGGLE_PLAYEDSHADOW, &CMainFrame::OnTogglePlayedShadow)
	ON_UPDATE_COMMAND_UI(ID_BTN_TOGGLE_PLAYEDSHADOW, &CMainFrame::OnUpdateTogglePlayedShadow)
	// Design Play/Stop
	ON_COMMAND(ID_BTN_PLAY, &CMainFrame::OnPlay)
	ON_COMMAND(ID_BTN_STOP, &CMainFrame::OnStop)
	ON_COMMAND(ID_BTN_PLAYONGAME, &CMainFrame::OnPlayOnGame)
	ON_UPDATE_COMMAND_UI(ID_BTN_PLAY, &CMainFrame::OnUpdatePlay)
	ON_UPDATE_COMMAND_UI(ID_BTN_STOP, &CMainFrame::OnUpdateStop)
	ON_UPDATE_COMMAND_UI(ID_BTN_PLAYONGAME, &CMainFrame::OnUpdatePlayOnGame)
	ON_WM_CLOSE()
	// Tab Change
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGING_ACTIVE_TAB, &CMainFrame::OnChangingActiveTab)
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, &CMainFrame::OnChangeActiveTab)
	// StatusBar
	ON_COMMAND_RANGE(ID_INDICATOR_TYPENAME, ID_INDICATOR_EDITMODE, &CMainFrame::OnStatusBar)
	ON_UPDATE_COMMAND_UI_RANGE(ID_INDICATOR_TYPENAME, ID_INDICATOR_EDITMODE, &CMainFrame::OnUpdateStatusBar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_EDITMODE,
	ID_INDICATOR_TYPENAME,
	ID_INDICATOR_CURSOR,
	//ID_INDICATOR_POSITION,
	//ID_INDICATOR_SIZE,
	//ID_INDICATOR_CAMERAPOS,

	/*
	// Don't need
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	*/
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);

	m_nCurTool = -1;
	m_pActiveView = nullptr;
	m_pDesignPlayThread = nullptr;
	m_pResourceHolder = nullptr;

	m_bOnClosing = false;
}

CMainFrame::~CMainFrame()
{
	if (m_pResourceHolder)
	{
		delete m_pResourceHolder;
		m_pResourceHolder = nullptr;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����� �� �ִ� �ٸ� ��Ÿ��...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // FALSE�� �����Ͽ� �� ���� �����ʿ� �ݱ� ���߸� ��ġ�մϴ�.
	mdiTabParams.m_bTabIcons = FALSE;    // TRUE�� �����Ͽ� MDI ���� ���� �������� Ȱ��ȭ�մϴ�.
	mdiTabParams.m_bAutoColor = TRUE;    // FALSE�� �����Ͽ� MDI ���� �ڵ� �� ������ ��Ȱ��ȭ�մϴ�.
	mdiTabParams.m_bDocumentMenu = TRUE; // �� ������ ������ �����ڸ��� ���� �޴��� Ȱ��ȭ�մϴ�.
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("�޴� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// �޴� ������ Ȱ��ȭ�ص� ��Ŀ���� �̵����� �ʰ� �մϴ�.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// ����� ���� ���� ���� �۾��� ����մϴ�.
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);
	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//m_wndStatusBar.SetPaneInfo(0, 0, ~SBPS_STRETCH, 0);

	// TODO: ���� ���� �� �޴� ������ ��ŷ�� �� ���� �Ϸ��� �� �ټ� ���� �����Ͻʽÿ�.
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);

	InitToolbars();

	// Visual Studio 2005 ��Ÿ�� ��ŷ â ������ Ȱ��ȭ�մϴ�.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 ��Ÿ�� ��ŷ â �ڵ� ���� ������ Ȱ��ȭ�մϴ�.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// �޴� �׸� �̹����� �ε��մϴ�(ǥ�� ���� ������ ����).
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ��ŷ â�� ����ϴ�.
	if (!CreateDockingWindows())
	{
		TRACE0("��ŷ â�� ������ ���߽��ϴ�.\n");
		return -1;
	}

	if (m_wndFileView.m_hWnd)
	{
		m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_wndFileView);

		CDockablePane* pTabbedBar = NULL;
		m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	}
	if (m_wndClassView.m_hWnd)
		m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);

	if (m_wndOutput.m_hWnd)
	{
		m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
		DockPane(&m_wndOutput);
	}

	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	// ������ ���� ���� ���־� ������ �� ��Ÿ���� �����մϴ�.
	OnApplicationLook(theApp.m_nAppLook);

	// ���� â ���� ��ȭ ���ڸ� Ȱ��ȭ�մϴ�.
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���� ���� �� ��ŷ â �޴� �ٲٱ⸦ Ȱ��ȭ�մϴ�.
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ����(<Alt> Ű�� ���� ä ����) ���� ���� ����� ������ Ȱ��ȭ�մϴ�.
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// ����� ���� ���� ���� �̹����� �ε��մϴ�.
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// �޴� ���� ������ Ȱ��ȭ�մϴ�(���� �ֱٿ� ����� ���).
	// TODO: ������� �⺻ ����� �����Ͽ� �� Ǯ�ٿ� �޴��� �ϳ� �̻��� �⺻ ����� ���Խ�ŵ�ϴ�.
	/*
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);
	*/

	// â ���� ǥ���ٿ��� ���� �̸� �� ���� ���α׷� �̸��� ������ ��ȯ�մϴ�.
	// ���� �̸��� ����� �׸��� �Բ� ǥ�õǹǷ� �۾� ǥ������ ��ɼ��� �����˴ϴ�.
	ModifyStyle(0, FWS_PREFIXTITLE);

	// for Hold Resource 
	m_pResourceHolder = new ResourceHolder;
	m_pResourceHolder->m_bUseDirectX = true;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Not use yet
	/*
	// Ŭ���� �並 ����ϴ�.
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Ŭ���� �� â�� ������ ���߽��ϴ�.\n");
		return FALSE; // ������ ���߽��ϴ�.
	}

	// ���� �並 ����ϴ�.
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("���� �� â�� ������ ���߽��ϴ�.\n");
		return FALSE; // ������ ���߽��ϴ�.
	}

	// ��� â�� ����ϴ�.
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("��� â�� ������ ���߽��ϴ�.\n");
		return FALSE; // ������ ���߽��ϴ�.
	}
	*/

	// �Ӽ� â�� ����ϴ�.
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("�Ӽ� â�� ������ ���߽��ϴ�.\n");
		return FALSE; // ������ ���߽��ϴ�.
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	if (m_wndFileView.m_hWnd)
	{
		HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
		m_wndFileView.SetIcon(hFileViewIcon, FALSE);
	}

	if (m_wndClassView.m_hWnd)
	{
		HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
		m_wndClassView.SetIcon(hClassViewIcon, FALSE);
	}

	if (m_wndOutput.m_hWnd)
	{
		HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
		m_wndOutput.SetIcon(hOutputBarIcon, FALSE);
	}

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* �޴��� �˻��մϴ�. */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	if (m_wndOutput.m_hWnd)
		m_wndOutput.UpdateFonts();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// �⺻ Ŭ������ ���� �۾��� �����մϴ�.
	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// ��� ����� ���� ������ ����� ���� ���߸� Ȱ��ȭ�մϴ�.
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	//m_wndOutput.UpdateFonts();
}


BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return CMDIFrameWndEx::OnNotify(wParam, lParam, pResult);
}

LRESULT CMainFrame::OnChangingActiveTab(WPARAM wparam, LPARAM lparam)
{
	if (m_pResourceHolder == nullptr) // after OnClose
		return 0;

	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
	{
		CString str = pView->GetDocument()->GetTitle();

		if (pView->IsPlaying())
		{
			pView->StopPlaying();
		}
	}

	// Wait until stop playing thread
	if (m_pDesignPlayThread)
		WaitForSingleObject(m_pDesignPlayThread->m_hThread, INFINITE);

	return 0;
}

LRESULT CMainFrame::OnChangeActiveTab(WPARAM wparam, LPARAM lparam)
{
	if (m_pResourceHolder == nullptr) // after OnClose
		return 0;

	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
	{
		m_pActiveView = pView;
		pView->OnActivateView();

		Invalidate();
	}

	return 0;
}

int CMainFrame::InitToolbars()
{
#define INIT_TOOLBAR(var, idr, _id) \
	while (true) { \
	if (!var.LoadToolBar(idr)) \
	{ \
		TRACE("Fail to LoadToolbar %s\n", #var); \
		break; \
	} \
	if (!var.CreateEx( \
		this, \
		TBSTYLE_FLAT, \
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, \
		CRect(1,1,1,1), \
		_id)) \
	{ \
		TRACE("Fail to CreateEx Toolbar %s\n", #var); \
		break; \
	} \
	::SetWindowText(var.m_hWnd, NaString(#var).wstr()); \
	var.EnableDocking(CBRS_ALIGN_ANY); \
	DockPane(&var); \
	break; \
	}

	INIT_TOOLBAR(m_wndToolBarBlocks, IDR_TOOLBAR_BLOCKS, (AFX_IDW_TOOLBAR + 7)); 
	INIT_TOOLBAR(m_wndToolBarItems, IDR_TOOLBAR_ITEMS, (AFX_IDW_TOOLBAR + 8));
	INIT_TOOLBAR(m_wndToolBarMapObjects, IDR_TOOLBAR_MAPOBJECTS, (AFX_IDW_TOOLBAR + 9));
	INIT_TOOLBAR(m_wndToolBarEnemies, IDR_TOOLBAR_ENEMIES, (AFX_IDW_TOOLBAR + 10));
	INIT_TOOLBAR(m_wndToolBarEventObjects, IDR_TOOLBAR_EVENTOBJECTS, (AFX_IDW_TOOLBAR + 11));
	INIT_TOOLBAR(m_wndToolBarVehicles, IDR_TOOLBAR_VEHICLES, (AFX_IDW_TOOLBAR + 12));

	return 0;
}

void CMainFrame::OnUpdateToolBars(CCmdUI * pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_BTN_OBJ_LOOPFLAG:
	case ID_BTN_OBJ_LOOPHANDLER:
	case ID_BTN_OBJ_BOOMBOOM:
	case ID_BTN_OBJ_LEAF:
    case ID_BTN_OBJ_VINE:
		pCmdUI->Enable(FALSE);
		return;
		break;
	}

	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
	{
        pCmdUI->Enable(!pView->IsPlaying());

		int nCurTool = (pView)->GetCurToolID();
		pCmdUI->SetCheck(pCmdUI->m_nID == nCurTool);
	}
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CMainFrame::OnTogglePlayedShadow()
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
	{
		DesignStage *pStage = pView->GetStage();
		pStage->m_bShowPlayedShadow = !pStage->m_bShowPlayedShadow;

		pView->InvalidateGame();
	}
}

void CMainFrame::OnUpdateTogglePlayedShadow(CCmdUI * pCmdUI)
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
	{
		DesignStage *pStage = pView->GetStage();
		pCmdUI->SetCheck(pStage->m_bShowPlayedShadow);
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::SetStatusText(int nID, LPCTSTR lpszNewText, BOOL bUpdate)
{
	int nIndex = -1;
	int nCnt = sizeof(indicators) / sizeof(UINT);
	for (int i=0; i<nCnt; i++)
	{
		if (indicators[i] == nID)
		{
			nIndex = i;
			break;
		}
	}

	if (nIndex == -1)
		return;
	
	m_wndStatusBar.SetPaneText(nIndex, lpszNewText, bUpdate);
	m_wndStatusBar.SetPaneStyle(nIndex, ~SBPS_DISABLED);
}

void CMainFrame::OnToolBars(UINT id)
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
	{
		pView->SetCurTool(id);
	}
}

void CMainFrame::OnClose()
{
	m_bOnClosing = true;

	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView && pView->IsPlaying())
	{
		pView->StopPlaying();
	}

	// Wait until stop playing thread
	if (m_pDesignPlayThread)
		WaitForSingleObject(m_pDesignPlayThread->m_hThread, INFINITE);

	CMDIFrameWndEx::OnClose();
}

void CMainFrame::OnPlay()
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView && !pView->IsPlaying())
	{
		pView->DoPlaying(-1, -1);
	}
}

void CMainFrame::OnStop()
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView && pView->IsPlaying())
	{
		pView->StopPlaying();
	}
}

void CMainFrame::OnPlayOnGame()
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
	{
		auto pDoc = pView->GetDocument();
		if (pDoc->IsModified() || pDoc->m_strPathName.GetLength() == 0)
		{
			if (MessageBox(L"You must save before test. proceed?", L"Confirm", MB_OKCANCEL) == IDCANCEL)
				return;

			if (pDoc->m_strPathName.GetLength() == 0)
				pDoc->DoSave(NULL);
			else
				pDoc->DoFileSave();
		}

		if (pView->IsPlaying())
			pView->StopPlaying();

		/*
		auto pGame = pView->GetGame();
		auto pStage = pView->GetStage();
		if (pStage->m_strUniqueId.GetLength() > 0)
		{
			MessageBox(L"You cannot do test Downloaded stage.", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		*/

		wchar_t szFileName[1024];
		HMODULE hModule = GetModuleHandle(NULL);
		GetModuleFileName(hModule, szFileName, sizeof(szFileName));

		NaString strExePath = szFileName;
		auto ar = strExePath.Split(L"\\");
		ar.Pop();
		strExePath = ar.Join(L"\\");
		strExePath += L"\\Mario.exe";

		NaString strArguments = L"-t ";
		strArguments += pView->GetDocument()->m_strPathName;

		ShellExecute(
			nullptr,
			L"open",
			strExePath.wstr(),
			strArguments.wstr(),
			nullptr,
			SW_SHOW
		);
	}
}

void CMainFrame::OnUpdatePlay(CCmdUI * pCmdUI)
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
		pCmdUI->Enable(!pView->IsPlaying());
	else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateStop(CCmdUI * pCmdUI)
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
		pCmdUI->Enable(pView->IsPlaying());
	else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdatePlayOnGame(CCmdUI * pCmdUI)
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateUpload(CCmdUI * pCmdUI)
{
	CFrameWnd *pFrame = GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (pView)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnStatusBar(UINT id)
{
	// Nothing.
}

void CMainFrame::OnUpdateStatusBar(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
