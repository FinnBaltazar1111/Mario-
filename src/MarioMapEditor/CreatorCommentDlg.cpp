// CreatorCommentDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MarioMapEditor.h"
#include "CreatorCommentDlg.h"
#include "afxdialogex.h"


// CreatorCommentDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CreatorCommentDlg, CDialogEx)

CreatorCommentDlg::CreatorCommentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CREATOR_COMMENT, pParent)
	, m_strComment(_T(""))
{

}

CreatorCommentDlg::~CreatorCommentDlg()
{
}

void CreatorCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_strComment);
}


BEGIN_MESSAGE_MAP(CreatorCommentDlg, CDialogEx)
END_MESSAGE_MAP()


// CreatorCommentDlg �޽��� ó�����Դϴ�.
