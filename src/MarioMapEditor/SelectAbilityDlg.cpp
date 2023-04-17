// SelectAbilityDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MarioMapEditor.h"
#include "SelectAbilityDlg.h"
#include "afxdialogex.h"

#include "Common/Common.h"


// SelectAbilityDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(SelectAbilityDlg, CDialogEx)

SelectAbilityDlg::SelectAbilityDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_ABILITY, pParent)
{
	m_nAbilityFlag = 0;
}

SelectAbilityDlg::~SelectAbilityDlg()
{
}

void SelectAbilityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelectAbilityDlg, CDialogEx)
END_MESSAGE_MAP()


// SelectAbilityDlg �޽��� ó�����Դϴ�.


BOOL SelectAbilityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_vecAbilityControl.push_back(AbilityControl(IDC_CHECK_0001, ABILITY_CARRYOBJECT));
	m_vecAbilityControl.push_back(AbilityControl(IDC_CHECK_0002, ABILITY_SPINJUMP));
	m_vecAbilityControl.push_back(AbilityControl(IDC_CHECK_0004, ABILITY_AUTOACCEL));
	m_vecAbilityControl.push_back(AbilityControl(IDC_CHECK_0008, ABILITY_AUTORUN));

	for (const auto &ac : m_vecAbilityControl)
	{
		if (m_nAbilityFlag & ac.m_nAbilityFlag)
			((CButton*)GetDlgItem(ac.m_nControl))->SetCheck(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void SelectAbilityDlg::OnOK()
{
	m_nAbilityFlag = 0;
	for (const auto &ac : m_vecAbilityControl)
	{
		if (((CButton*)GetDlgItem(ac.m_nControl))->GetCheck())
			m_nAbilityFlag |= ac.m_nAbilityFlag;
	}

	CDialogEx::OnOK();
}
