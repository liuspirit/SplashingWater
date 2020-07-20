#pragma once

// LogicDlg 对话框

class LogicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LogicDlg)

public:
	LogicDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LogicDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Logic };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogic();
	afx_msg void OnBnClickedRegister();
	virtual BOOL DestroyWindow();

private:
	CString m_cstrAccount;
	CString m_cstrPassword;
};
