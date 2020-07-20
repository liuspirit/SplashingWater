// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplashingWaterClient.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SmartPtr.h"
#include "RegisterStrategy.h"
#include "MessageBuffer.h"
#include "Converter.h"
// RegisterDlg �Ի���

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RegisterDlg::IDD, pParent)
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RegisterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RegisterDlg::OnBnClickedCancel)
	ON_EN_KILLFOCUS(IDC_EDIT_Phone, &RegisterDlg::OnEnKillfocusEditPhone)
	ON_EN_KILLFOCUS(IDC_EDIT_Name, &RegisterDlg::OnEnKillfocusEditName)
	ON_EN_KILLFOCUS(IDC_EDIT_Password, &RegisterDlg::OnEnKillfocusEditPassword)
	ON_EN_KILLFOCUS(IDC_EDIT_Password2, &RegisterDlg::OnEnKillfocusEditPassword2)
END_MESSAGE_MAP()


// RegisterDlg ��Ϣ�������


void RegisterDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_cstrName == "" || m_cstrPhone == "" || m_cstrPassword == "")
	{
		AfxMessageBox(_T("Please input Name or Phone or Password"));
		return;
	}

	//checkValid();�ǿ�
	string strName = Converter::toString(m_cstrName);
	string strPhone = Converter::toString(m_cstrPhone);
	string strPassword = Converter::toString(m_cstrPassword);

	Log_Debug("register Dlg: begin to execute register strategy");
	SmartPtr<IStrategy> pRegister = new RegisterStrategy(strName, strPhone, strPassword);
	pRegister->processPackage();
	Log_Debug("register Dlg: end to execute register strategy");

	//wait account to timeout
	string strResult = MessageBuffer::getInstance()->getRegisterMsg(1);
	if (strResult == "")
	{
		AfxMessageBox(_T("Failed to register"));
	}
	else
	{
		AfxMessageBox(Converter::toCString(strResult));
	}
	CDialogEx::OnOK();
}


void RegisterDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void RegisterDlg::OnEnKillfocusEditPhone()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData();
	GetDlgItem(IDC_EDIT_Phone)->GetWindowTextW(m_cstrPhone);
	if (m_cstrPhone.GetLength() != 11)
	{
		AfxMessageBox(_T("the length of Phone is wrong!"));
	}
}


void RegisterDlg::OnEnKillfocusEditName()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	GetDlgItem(IDC_EDIT_Name)->GetWindowTextW(m_cstrName);
	if (m_cstrName == "")
	{
		AfxMessageBox(_T("Name can be null"));
	}
}

void RegisterDlg::OnEnKillfocusEditPassword()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	GetDlgItem(IDC_EDIT_Password)->GetWindowTextW(m_cstrPassword);
	int nLength = m_cstrPassword.GetLength();
	if (nLength < 6)
	{
		AfxMessageBox(_T("the length of Password is less than 6!  length = ") + Converter::toCString(nLength));
	}
}

void RegisterDlg::OnEnKillfocusEditPassword2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString cstrPassword2;
	GetDlgItem(IDC_EDIT_Password2)->GetWindowTextW(cstrPassword2);

	if (cstrPassword2 != m_cstrPassword)
	{
		AfxMessageBox(_T("the length of Password2 is wrong!"));
	}
}
