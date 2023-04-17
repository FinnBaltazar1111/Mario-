
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MarioMapEditor.h"

#include "MarioMapEditorView.h"
#include "Sprite.h"
#include "DesignStage.h"
#include "GameObjectBase.h"
#include "MapObjectBase.h"
#include "Themes.h"
#include "DesignGame.h"

#include "MapObjectPipe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar �޽��� ó����

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	/*
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
	*/

	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �޺� ���ڸ� ����ϴ�.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	/*
	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("�Ӽ� �޺� ���ڸ� ������ ���߽��ϴ�. \n");
		return -1;      // ������ ���߽��ϴ�.
	}
	*/

	// Disabled
	/*
	m_wndObjectCombo.AddString(_T("���� ���α׷�"));
	m_wndObjectCombo.AddString(_T("�Ӽ� â"));
	m_wndObjectCombo.SetCurSel(0);
	*/

	/*
	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();
	*/

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("�Ӽ� ǥ�� ������ ���߽��ϴ�. \n");
		return -1;      // ������ ���߽��ϴ�.
	}

	InitPropList();

	/*
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE); // ��� 
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE); // ���

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// ��� ����� �θ� �������� �ƴ� �� ��Ʈ���� ���� ����õ˴ϴ�.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
	*/

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_PropMap.Clear();
	SetRedraw(FALSE);

	if (!theApp.m_pMainWnd)
	{
		NaDebugOut(L"InitPropList: MainWnd is null\n");
	}
	else
	{
		CFrameWnd *pFrame = ((CMainFrame*)theApp.m_pMainWnd)->GetActiveFrame();
		CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
		if (!pView)
		{
			NaDebugOut(L"InitPropList: View is null\n");
		}
		else
		{
			DesignStage *pStage = pView->GetStage();

			// Selected Object Property
			switch (pStage->m_nCurToolType)
			{
			case TOOLTYPE_EVENTOBJECT:
				{
					GameObjectBase* pObj = pStage->m_pEventObject;
					m_PropMap.AddProperty(L"Type", &pObj->m_nType, VT_I4, L"EventObject", false);
					m_PropMap.AddProperties(pObj);
				}
				break;
			case TOOLTYPE_ENEMY:
				{
					GameObjectBase* pObj = pStage->m_pEnemyObject;
					m_PropMap.AddProperty(L"Type", &pObj->m_nType, VT_I4, L"Enemy", false);
					m_PropMap.AddProperties(pObj);
				}
				break;
			case TOOLTYPE_MAPOBJECT:
				{
					MapObjectBase* pObj = pStage->m_pMapObject;
					m_PropMap.AddProperty(L"Type", &pObj->m_nType, VT_I4, L"MapObject", false);
					m_PropMap.AddProperties(pObj);

					if (pObj->m_nType == MAPOBJECT_PIPE)
					{
						MapObjectPipe *pPipe = ((MapObjectPipe*)pObj);
						if (pPipe->m_bUseNewStyle)
						{
							m_PropMap.SetPropertyEnable(L"UpToDown", false);
							m_PropMap.SetPropertyEnable(L"LeftToRight", false);
						}
						else
						{
							m_PropMap.SetPropertyEnable(L"Direction", false);
						}
					}
				}
				break;
			case TOOLTYPE_ITEM:
				{
					m_PropMap.AddProperty(L"Type", &pStage->m_nCurType, VT_I4, L"Item", false);
					}
				break;
			case TOOLTYPE_TILE:
				{
					m_PropMap.AddProperty(L"Type", &pStage->m_nCurType, VT_I4, L"Tile", false);
				}
				break;
			case TOOLTYPE_VEHICLE:
				{
					GameObjectBase* pObj = pStage->m_pVehicleObject;
					m_PropMap.AddProperty(L"Type", &pStage->m_nCurType, VT_I4, L"Vehicle", false);
					m_PropMap.AddProperties(pObj);
				}
				break;
			default:
				{
					// Stage Property
					m_PropMap.AddProperties(pStage);
					if (pStage->m_strCustomThemeName.GetLength() > 0)
					{
						m_PropMap.SetPropertyEnable(L"ThemeSet", false);
						m_PropMap.SetPropertyEnable(L"Theme", false);
					}
					else if (pStage->m_nThemeSet != STAGETHEMESET_CUSTOM)
					{
						m_PropMap.SetPropertyEnable(L"Theme", false);
						m_PropMap.SetPropertyEnable(L"BackgroundTheme", false);
						m_PropMap.SetPropertyEnable(L"BackgroundColor", false);
					}
					m_PropMap.SetPropertyEnable(L"UniqueId", false);
					m_PropMap.SetPropertyEnable(L"Revision", false);

					// Dynamic add Custom Game Theme List
					m_PropMap.SetPropertyOptionList(L"GameTheme", ((DesignGame*)((pStage)->m_pGame))->m_arGameTheme);
				}
				break;
			}
		}
	}

	m_PropMap.BindControl(&m_wndPropList);
	m_PropMap.InitControl();

	SetRedraw(TRUE);

	/*
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("���"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D ���"), (_variant_t) false, _T("â�� ���� �۲��� �ƴ� �۲��� �����ϰ�, ��Ʈ�ѿ� 3D �׵θ��� �����մϴ�.")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�׵θ�"), _T("Dialog Frame"), _T("None, Thin, Resizable �Ǵ� Dialog Frame �� �ϳ��� �����մϴ�."));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ĸ��"), (_variant_t) _T("����"), _T("â�� ���� ǥ���ٿ� ǥ�õǴ� �ؽ�Ʈ�� �����մϴ�.")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("â ũ��"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("����"), (_variant_t) 250l, _T("â�� ���̸� �����մϴ�."));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("�ʺ�"), (_variant_t) 150l, _T("â�� �ʺ� �����մϴ�."));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("�۲�"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	_tcscpy_s(lf.lfFaceName, _T("���� ���"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("�۲�"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("â�� �⺻ �۲��� �����մϴ�.")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("�ý��� �۲��� ����մϴ�."), (_variant_t) true, _T("â���� MS Shell Dlg �۲��� ����ϵ��� �����մϴ�.")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("��Ÿ"));
	pProp = new CMFCPropertyGridProperty(_T("(�̸�)"), _T("���� ���α׷�"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("â ����"), RGB(210, 192, 254), NULL, _T("â�� �⺻ ������ �����մϴ�."));
	pColorProp->EnableOtherButton(_T("��Ÿ..."));
	pColorProp->EnableAutomaticButton(_T("�⺻��"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("������ ����(*.ico)|*.ico|��� ����(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("������"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("â �������� �����մϴ�.")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("����"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("����"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("ù��° ���� ����"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("�� ��° ���� ����"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�׸� 1"), (_variant_t) _T("�� 1"), _T("�����Դϴ�.")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�׸� 2"), (_variant_t) _T("�� 2"), _T("�����Դϴ�.")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�׸� 3"), (_variant_t) _T("�� 3"), _T("�����Դϴ�.")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
	*/
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	/*
	m_wndObjectCombo.SetFont(&m_fntPropList);
	*/
}


void CPropertiesWnd::RefreshPropValues(CMarioMapEditorView *pView)
{
	if (pView == nullptr)
	{
		if (!theApp.m_pMainWnd)
		{
			NaDebugOut(L"RefreshPropValued: MainWnd is null\n");
			return;
		}

		CFrameWnd *pFrame = ((CMainFrame*)theApp.m_pMainWnd)->GetActiveFrame();
		CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
		if (!pView)
		{
			NaDebugOut(L"RefreshPropValued: View is null\n");
			return;
		}
	}

	DesignStage *pStage = pView->GetStage();
	if (!pStage)
	{
		NaDebugOut(L"RefreshPropValued: Stage is null\n");
		return;
	}

	InitPropList();

	m_PropMap.RefreshControl();
	m_wndPropList.ExpandAll();
}


LRESULT CPropertiesWnd::OnPropertyChange(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty * pProp = (CMFCPropertyGridProperty *)lParam;
	int nID = pProp->GetData();

	NaDebugOut(L"PropertyChange: 0x%08x, %d\n", nID, lParam);

	if (!theApp.m_pMainWnd)
		return 0;

	CFrameWnd *pFrame = ((CMainFrame*)theApp.m_pMainWnd)->GetActiveFrame();
	CMarioMapEditorView *pView = (CMarioMapEditorView*)pFrame->GetActiveView();
	if (!pView)
		return 0;

	COleVariant var = pProp->GetValue();
	m_PropMap.SetPropertyByID(nID, var);

	NaString strPropName = m_PropMap.GetPropertyNameByID(nID);
	pView->OnPropertyChange(strPropName);

	return LRESULT();
}