#pragma once


// RegisterDlg �Ի���

class RegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterDlg)

public:
	RegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RegisterDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Register };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnKillfocusEditPhone();
	afx_msg void OnEnKillfocusEditName();
	afx_msg void OnEnKillfocusEditPassword();
	afx_msg void OnEnKillfocusEditPassword2();

private:
	CString m_cstrName;
	CString m_cstrPhone;
	CString m_cstrPassword;
};