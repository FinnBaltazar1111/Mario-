#pragma once


// CreatorCommentDlg ��ȭ �����Դϴ�.

class CreatorCommentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreatorCommentDlg)

public:
	CreatorCommentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CreatorCommentDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CREATOR_COMMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strComment;
};
