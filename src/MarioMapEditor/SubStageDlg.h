#pragma once


// SubStageDlg ��ȭ �����Դϴ�.

class SubStageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SubStageDlg)

public:
	SubStageDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SubStageDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SUBSTAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nStage;
	int m_nSubStageCnt;
	virtual BOOL OnInitDialog();
};
