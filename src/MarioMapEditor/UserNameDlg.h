#pragma once
#include "afxwin.h"


// UserNameDlg ��ȭ �����Դϴ�.

class UserNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserNameDlg)

public:
	UserNameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~UserNameDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USERNAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
};
