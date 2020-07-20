// AddFriendDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplashingWaterClient.h"
#include "AddFriendDlg.h"
#include "afxdialogex.h"
#include "Converter.h"
#include "UpdateStrategy.h"
#include "SmartPtr.h"
// AddFriendDlg �Ի���

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


// AddFriendDlg ��Ϣ�������


void AddFriendDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
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
