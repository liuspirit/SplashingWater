#pragma once


// AddFriendDlg 对话框

class AddFriendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddFriendDlg)
private:
	//CString m_cstr


public:
	AddFriendDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddFriendDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_AddFriend };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
