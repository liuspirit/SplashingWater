#pragma once


// AddFriendDlg �Ի���

class AddFriendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddFriendDlg)
private:
	//CString m_cstr


public:
	AddFriendDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddFriendDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_AddFriend };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
