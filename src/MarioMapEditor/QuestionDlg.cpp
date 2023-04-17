// QuestionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MarioMapEditor.h"
#include "QuestionDlg.h"
#include "afxdialogex.h"


// QuestionDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(QuestionDlg, CDialogEx)

QuestionDlg::QuestionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_QNA, pParent)
	, m_strQuestion(_T(""))
	, m_strAnswer(_T(""))
{

}

QuestionDlg::~QuestionDlg()
{
}

void QuestionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_QUESTION, m_strQuestion);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_strAnswer);
}


BEGIN_MESSAGE_MAP(QuestionDlg, CDialogEx)
END_MESSAGE_MAP()


// QuestionDlg �޽��� ó�����Դϴ�.
