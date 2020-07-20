
// SplashingWaterClientDlg.h : 头文件
//

#pragma once
#include "HttpClient.h"
#include "HttpThread.h"
#include "afxwin.h"
#include <vector>

// CSplashingWaterClientDlg 对话框
class CSplashingWaterClientDlg : public CDialogEx, public HttpThread
{
// 构造
public:
	CSplashingWaterClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPLASHINGWATERCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual void run();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedSendbutton();

private:
	CButton m_SendButton;
	CEdit m_EditAllMessage;
	CString m_csSendData;
	string m_strAccount;

	vector<string> m_ReceiveMsg;
public:
	CString m_AccountName;
	CString m_Account;
	virtual BOOL DestroyWindow();
};
