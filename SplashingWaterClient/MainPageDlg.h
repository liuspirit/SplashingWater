#pragma once
#include "afxcmn.h"
#include "HttpThread.h"
#include "Observer\ObserverInterface.h"
// MainPageDlg �Ի���

class MainPageDlg : public CDialogEx, public HttpThread, public ObserverInterface
{
	DECLARE_DYNAMIC(MainPageDlg)

public:
	MainPageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MainPageDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_FriendList;
	virtual BOOL OnInitDialog();
	virtual void run();
	virtual void update(struct SubjectData subjectData);
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedDel();
	afx_msg void OnNMDblclkListFriendlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddFriend();
};
