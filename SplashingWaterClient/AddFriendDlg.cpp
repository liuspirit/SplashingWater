// AddFriendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SplashingWaterClient.h"
#include "AddFriendDlg.h"
#include "afxdialogex.h"
#include "Converter.h"
#include "UpdateStrategy.h"
#include "SmartPtr.h"
// AddFriendDlg 对话框

IMPLEMENT_DYNAMIC(AddFriendDlg, CDialogEx)

AddFriendDlg::AddFriendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddFriendDlg::IDD, pParent)
{

}

AddFriendDlg::~AddFriendDlg()
{
}

void AddFriendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddFriendDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddFriendDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddFriendDlg 消息处理程序


void AddFriendDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	
	CString cstrNewFriendAccount;
	GetDlgItem(IDC_EDIT_NewAccount)->GetWindowTextW(cstrNewFriendAccount);

	if (cstrNewFriendAccount == "")
	{
		AfxMessageBox(_T("input is null"));
		return;
	}


	string strAccount = Converter::toString(cstrNewFriendAccount);
	int nAdd = 1;
	SmartPtr<IStrategy> addAccount = new UpdateStrategy(nAdd, strAccount);
	addAccount->processPackage();

	CDialogEx::OnOK();
}
