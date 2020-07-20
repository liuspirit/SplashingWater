// LogicDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplashingWaterClient.h"
#include "LogicDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "RegisterDlg.h"
#include "SmartPtr.h"
#include "LogicStrategy.h"
#include "Converter.h"
#include "MessageBuffer.h"
// LogicDlg �Ի���

IMPLEMENT_DYNAMIC(LogicDlg, CDialogEx)

LogicDlg::LogicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LogicDlg::IDD, pParent)
{

}

LogicDlg::~LogicDlg()
{
}

void LogicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LogicDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &LogicDlg::OnBnClickedLogic)
	ON_BN_CLICKED(IDC_BUTTON1, &LogicDlg::OnBnClickedRegister)
END_MESSAGE_MAP()


// LogicDlg ��Ϣ�������

/*
void LogicDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	


	//CDialogEx::OnOK();
}
*/

void LogicDlg::OnBnClickedLogic()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	GetDlgItem(IDC_EDIT_Account)->GetWindowTextW(m_cstrAccount);
	GetDlgItem(IDC_EDIT_Password)->GetWindowTextW(m_cstrPassword);


	if (m_cstrAccount == "" || m_cstrPassword == "")
	{
		AfxMessageBox(_T("Please input Acoount or Password!"));
		return;
	}

	string strAccount = Converter::toString(m_cstrAccount);
	string strPassword = Converter::toString(m_cstrPassword);

	Log_Debug("LogicDlg: begin to execute logic strategy");
	SmartPtr<IStrategy> pLogic = new LogicStrategy(strAccount, strPassword);
	pLogic->processPackage();
	Log_Debug("LogicDlg: end to execute logic strategy");

	string strResult = MessageBuffer::getInstance()->getLogicMsg(1);
	if (strResult == "")
	{
		AfxMessageBox(_T("Failed to connect the server! TimeOut"));
	}
	else if (strResult == "wrong password")
	{
		AfxMessageBox(_T("Password and Account is wrong!"));
	}
	else
	{
		MessageBuffer::getInstance()->setLogicMsg(strResult);
		CDialogEx::OnOK();
	}
}


void LogicDlg::OnBnClickedRegister()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RegisterDlg dlg;
	dlg.DoModal();
}


BOOL LogicDlg::DestroyWindow()
{
	// TODO:  �ڴ����ר�ô����/����û���
	AfxGetApp()->m_pMainWnd = NULL;
	return CDialogEx::DestroyWindow();
}
