// UserNameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MarioMapEditor.h"
#include "UserNameDlg.h"
#include "afxdialogex.h"


// UserNameDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(UserNameDlg, CDialogEx)

UserNameDlg::UserNameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_USERNAME, pParent)
	, m_strName(_T(""))
{

}

UserNameDlg::~UserNameDlg()
{
}

void UserNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(UserNameDlg, CDialogEx)
END_MESSAGE_MAP()


// UserNameDlg �޽��� ó�����Դϴ�.
