#pragma once

// LogicDlg �Ի���

class LogicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LogicDlg)

public:
	LogicDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LogicDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Logic };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogic();
	afx_msg void OnBnClickedRegister();
	virtual BOOL DestroyWindow();

private:
	CString m_cstrAccount;
	CString m_cstrPassword;
};
