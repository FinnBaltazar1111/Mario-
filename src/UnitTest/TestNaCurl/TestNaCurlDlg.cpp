
// TestNaCurlDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TestNaCurl.h"
#include "TestNaCurlDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <ostream>

#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_ios.h"
#include "curl_exception.h"

#include "NaString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTestNaCurlDlg ��ȭ ����



CTestNaCurlDlg::CTestNaCurlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTNACURL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestNaCurlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestNaCurlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestNaCurlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestNaCurlDlg �޽��� ó����

BOOL CTestNaCurlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CTestNaCurlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTestNaCurlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTestNaCurlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestNaCurlDlg::OnBnClickedButton1()
{
	CString strUrl = L"https://superfanmademariobros-cc9a3.firebaseio.com/test.json";
	GetDlgItem(IDC_EDIT1)->SetWindowText(strUrl);
	GetDlgItem(IDC_EDIT1)->GetWindowText(strUrl);

	NaString nstrUrl = strUrl;

	using std::cout;
	using std::endl;
	using std::ostringstream;

	using curl::curl_easy;
	using curl::curl_ios;
	using curl::curl_easy_exception;
	using curl::curlcpp_traceback;
	
	ostringstream str;
	curl_ios<ostringstream> writer(str);

	// Pass the writer to the easy constructor and watch the content returned in that variable!
	curl_easy easy(writer);

	// Add some option to the easy handle
	easy.add<CURLOPT_URL>(nstrUrl.cstr());
	easy.add<CURLOPT_FOLLOWLOCATION>(1L);

	//easy.add<CURLOPT_SSLVERSION>(3);
	//easy.add<CURLOPT_ISSUERCERT>("curl-ca-bundle.cer");
	easy.add<CURLOPT_SSL_VERIFYPEER>(0);

	easy.add<CURLOPT_POSTFIELDS>("{\"title\":\"fromcpp\", \"author\":\"neoarc\", \"map\":\"shit!!\"}");

	try 
	{
		// Execute the request.
		easy.perform();
	}
	catch (curl_easy_exception error) 
	{
		// If you want to get the entire error stack we can do:
		curlcpp_traceback errors = error.get_traceback();
		// Otherwise we could print the stack like this:
		error.print_traceback();
	}

	// Let's print the stream content.
	const std::string tmp = str.str();
	const char* cstr = tmp.c_str();

	NaString nstr = cstr;
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(nstr.wstr());
}
