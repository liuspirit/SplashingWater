#pragma once
#include "afxcmn.h"
#include "HttpThread.h"
#include "Observer\ObserverInterface.h"
// MainPageDlg 对话框

class MainPageDlg : public CDialogEx, public HttpThread, public ObserverInterface
{
	DECLARE_DYNAMIC(MainPageDlg)

public:
	MainPageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MainPageDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
