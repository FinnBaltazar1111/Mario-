
// MarioMapEditor.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MarioMapEditor.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "MarioMapEditorDoc.h"
#include "MarioMapEditorView.h"

#include "GameConfig.h"
#include "NaPlatformAPI.h"
#include "UserNameDlg.h"

#include "PathManager.h"
#include "NaPlatformAPI.h"
#include <aes/md5.h>
#include "NaException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMarioMapEditorApp

BEGIN_MESSAGE_MAP(CMarioMapEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMarioMapEditorApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMarioMapEditorApp ����

CMarioMapEditorApp::CMarioMapEditorApp()
{
	m_bHiColorIcons = TRUE;

	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���� ���α׷��� ���� ��� ��Ÿ�� ������ ����Ͽ� ������ ���(/clr):
	//     1) �� �߰� ������ �ٽ� ���� ������ ������ ����� �۵��ϴ� �� �ʿ��մϴ�.
	//     2) ������Ʈ���� �����Ϸ��� System.Windows.Forms�� ���� ������ �߰��ؾ� �մϴ�.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	//SetAppID(_T("Neoarc.MarioV3.MapEditor.0.4"));
	SetAppID(_T("MarioMapEditor.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CMarioMapEditorApp ��ü�Դϴ�.

CMarioMapEditorApp theApp;


// CMarioMapEditorApp �ʱ�ȭ

BOOL CMarioMapEditorApp::InitInstance()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Minidump Handler
	::SetUnhandledExceptionFilter(CMarioMapEditorApp::CrashHandler);

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("NeoarcApp"));
	//SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(16);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�.  ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MarioMapEditorTYPE,
		RUNTIME_CLASS(CMarioMapEditorDoc),
		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CMarioMapEditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �� MDI ������ â�� ����ϴ�.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  MDI ���� ���α׷������� m_pMainWnd�� ������ �� �ٷ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	// ��� ���⿡ ���� ���⸦ Ȱ��ȭ�մϴ�.
	m_pMainWnd->DragAcceptFiles();

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DDE Execute ���⸦ Ȱ��ȭ�մϴ�.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// For not open empty document
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// Temporary game instance for get path data
	Game *pGame = new Game;
	pGame->m_strGameRootDir = NaPlatform::GetCurrentPath();

	bool bDeny = false;
	GameConfig *pConfig = GameConfig::GetGameConfig(pGame);
	if (pConfig->m_strName.GetLength() == 0 ||
		pConfig->m_strUniqueId.GetLength() == 0)
	{
		/*
		UserNameDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			pConfig->m_strName = dlg.m_strName;
			pConfig->Save();
		}
		*/

		bDeny = true;
		
	}

	// Check register ticket
	auto strMacAddress = NaPlatform::GetMacAddress();
	auto strComputerName = NaPlatform::GetComputerName();
	NaDebugOut(L"MacAddress: %ls\n", strMacAddress.wstr());
	NaDebugOut(L"Computer name: %ls\n", strComputerName.wstr());

	NaString str;
	str.Format(L"%ls%ls", strMacAddress.wstr(), strComputerName.wstr());

	char szMD5[MD5_STR_LEN + 1];
	Compute_string_md5((unsigned char*)str.wstr(), str.GetBufferSize(), szMD5);
	NaString strLocalKey = szMD5;
	
	ServerRequest req;
	try
	{
		auto pTicket = req.GetRegisterTicket(strLocalKey);
		if (pTicket->m_nStatus != 1)
			bDeny = true;
	}
	catch(NaException &e)
	{
		bDeny = true;
	}

	if (bDeny)
	{
		// Re-launch
		NaString strMarioExe = PathManager::GetGameRootPath(pGame);
		strMarioExe += L"\\Mario.exe";

		ShellExecute(
			nullptr,
			L"open",
			strMarioExe.wstr(),
			nullptr,
			nullptr,
			SW_SHOW
		);

		PostQuitMessage(-1);
	}

	delete pGame;


	return TRUE;
}

int CMarioMapEditorApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMarioMapEditorApp �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CMarioMapEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

LONG CMarioMapEditorApp::CrashHandler(EXCEPTION_POINTERS * pException)
{
	NaString strPath = NaPlatform::GetCurrentPath();

	NaString strFileName;
	CTime t = CTime::GetCurrentTime();
	strFileName.Format(L"\\MarioMapEditor_CrashDump_%04d%02d%02d_%02d%02d%02d.dmp",
		t.GetYear(), t.GetMonth(), t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond()
		);

	strPath += strFileName;

	HANDLE hDumpFile = CreateFile(strPath.wstr(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = ::GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	
	MiniDumpWriteDump(
		::GetCurrentProcess(),
		::GetCurrentProcessId(), 
		hDumpFile, 
		MiniDumpNormal, 
		&dumpInfo, 
		NULL, 
		NULL);
	
	CloseHandle(hDumpFile);

	NaString strMsg;
	strMsg.Format(L"Unhandled exception has occurred.\nPlease report Crash dump to neoarc.\n\n-Crash dump created: %ls", strPath.wstr());
	::MessageBox(nullptr, strMsg.wstr(), L"Crashed :P (But our princess is safe)", MB_ICONERROR | MB_OK);

	return EXCEPTION_EXECUTE_HANDLER;
}

// CMarioMapEditorApp ����� ���� �ε�/���� �޼���

void CMarioMapEditorApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMarioMapEditorApp::LoadCustomState()
{
}

void CMarioMapEditorApp::SaveCustomState()
{
}

// CMarioMapEditorApp �޽��� ó����



