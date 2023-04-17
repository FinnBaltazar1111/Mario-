
// MarioConfigDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

enum InputTypes
{
	INPUT_L = 0,
	INPUT_R,
	INPUT_U,
	INPUT_D,
	INPUT_J,
	INPUT_F,
};

// CMarioConfigDlg ��ȭ ����
class CMarioConfigDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMarioConfigDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MARIOCONFIG_DIALOG };
#endif

	void EditInput(int nInput);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboRenderEngine;
	CButton m_chkSoftwareFrameskip;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnLeft();
	afx_msg void OnBnClickedBtnRight();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnAccel();
	afx_msg void OnBnClickedBtnJump();
	afx_msg void OnBnClickedBtnInputReset();

	struct InputInfo
	{
		CString strInputName;
		int nKeyCode;
		int nButtonID;
	};

	InputInfo m_InputInfo[6];
	void RemoveDuplicatedInput(int nNewKeyCode);

	void StartCaptureInput();
	void StopCaptureInput();
	afx_msg void OnRawInput(UINT nInputcode, HRAWINPUT hRawInput);
	bool m_bCaptureInput;
	int m_nCaptureInputIndex;
	void UpdateInputButtons();
	void UpdateInputButton(int nIndex);
	CComboBox m_cboWindowSize;
};
