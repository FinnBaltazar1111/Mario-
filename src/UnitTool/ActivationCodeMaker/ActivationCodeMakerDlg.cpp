
// ActivationCodeMakerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ActivationCodeMaker.h"
#include "ActivationCodeMakerDlg.h"
#include "afxdialogex.h"

#include "ServerRequest.h"
#include "JsonManager.h"

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


// CActivationCodeMakerDlg ��ȭ ����



CActivationCodeMakerDlg::CActivationCodeMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACTIVATIONCODEMAKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CActivationCodeMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CActivationCodeMakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CHECK, &CActivationCodeMakerDlg::OnBnClickedBtnCheck)
END_MESSAGE_MAP()


// CActivationCodeMakerDlg �޽��� ó����

BOOL CActivationCodeMakerDlg::OnInitDialog()
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

void CActivationCodeMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CActivationCodeMakerDlg::OnPaint()
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
HCURSOR CActivationCodeMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CActivationCodeMakerDlg::OnBnClickedBtnCheck()
{
	CString strText;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);
	NaString strNum = strText;
	if (strNum.GetLength() == 0)
	{
		MessageBox(L"Enter ticket number", L"Error", MB_OK);
		return;
	}

	int nTicketNumber = strNum.ToInt();
	if (nTicketNumber < 0)
	{
		MessageBox(L"Enter ticket number", L"Error", MB_OK);
		return;
	}

	GetDlgItem(IDC_EDIT2)->SetWindowTextW(L"");

	NaCurl curl;
	NaString strUrl = ServerRequest::s_strBaseUrl;
	strUrl += L"register.json";

	NaString strRet = curl.Post(strUrl);
	Json::Value jRet;
	Json::Reader jReader;
	if (!jReader.parse(strRet.cstr(), jRet))
	{
		MessageBox(L"Parse error.", L"Error", MB_OK);
		return;
	}

	for (auto jIt = jRet.begin(); jIt != jRet.end(); jIt++)
	{
		NaString strKey = jIt.key().toStyledString().c_str();
		NaString strUid = strKey.Mid(1);
		strUid = strUid.Left(strUid.GetLength() - 2);

		if (strUid.CompareNoCase(L"LastTicketNumber") == 0)
			continue;

		ServerRegisterTicket *pTicket = new ServerRegisterTicket;
		pTicket->BuildPropertyMap();

		try
		{
			JsonManager::LoadJsonObjectProperty(pTicket, *jIt);
		}
		catch (Json::LogicError &e)
		{
			NaDebugOut(L"Error: Bad ticket: %d\n", pTicket->m_nTicketNumber);
			delete pTicket;
			continue;
		}

		NaString strTicketHash = pTicket->m_strTicketHash = strUid;
		if (pTicket->m_nTicketNumber == nTicketNumber)
		{
			NaString strRightCode = L"";
			int nTemp = 0;
			for (int i = 0; i < strTicketHash.GetLength(); i++)
			{
				NaDebugOut(L"%c / %d\n", strTicketHash[i], strTicketHash[i]);
				if (i % 5 == 0)
					nTemp += (strTicketHash[i]);
				if (i % 5 == 1)
					nTemp += (strTicketHash[i]) / 2;
				if (i % 5 == 2)
					nTemp += (strTicketHash[i]) / 4;
				if (i % 5 == 3)
					nTemp += (strTicketHash[i]) / 5;
				if (i % 5 == 4)
				{
					nTemp += (strTicketHash[i]) / 3;
					if (nTemp > 255)
						nTemp = nTemp % 255;

					NaString strTemp;
					strTemp.Format(L"%X", nTemp);
					strRightCode += strTemp;

					nTemp = 0;
				}
			}

			GetDlgItem(IDC_EDIT2)->SetWindowTextW(strRightCode.wstr());

			NaString strJson = (*jIt).toStyledString().c_str();
			strJson.ReplaceAll(L",", L",\r\n");

			GetDlgItem(IDC_EDIT3)->SetWindowTextW(strJson.wstr());
		}
	}
}
