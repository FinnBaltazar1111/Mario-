#pragma once

#include <vector>

// SelectAbilityDlg ��ȭ �����Դϴ�.
class AbilityControl
{
public:
	AbilityControl(int c, int a)
	{
		m_nControl = c;
		m_nAbilityFlag = a;
	};
	int m_nControl;
	int m_nAbilityFlag;
};

class SelectAbilityDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelectAbilityDlg)

public:
	SelectAbilityDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SelectAbilityDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ABILITY };
#endif

	int m_nAbilityFlag;
	std::vector<AbilityControl> m_vecAbilityControl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
