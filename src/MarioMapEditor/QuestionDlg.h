#pragma once


// QuestionDlg ��ȭ �����Դϴ�.

class QuestionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(QuestionDlg)

public:
	QuestionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~QuestionDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_QNA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strQuestion;
	CString m_strAnswer;
};
