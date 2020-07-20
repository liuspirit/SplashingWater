
// SplashingWaterClientDlg.h : ͷ�ļ�
//

#pragma once
#include "HttpClient.h"
#include "HttpThread.h"
#include "afxwin.h"
#include <vector>

// CSplashingWaterClientDlg �Ի���
class CSplashingWaterClientDlg : public CDialogEx, public HttpThread
{
// ����
public:
	CSplashingWaterClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPLASHINGWATERCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual void run();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
