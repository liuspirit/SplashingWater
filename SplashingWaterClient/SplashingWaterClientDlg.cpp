
// SplashingWaterClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SplashingWaterClient.h"
#include "SplashingWaterClientDlg.h"
#include "afxdialogex.h"
#include "Converter.h"
#include "MessageBuffer.h"
#include "IStrategy.h"
#include "SendStrategy.h"
#include "SmartPtr.h"

//#include "MessageParser.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSplashingWaterClientDlg 对话框



CSplashingWaterClientDlg::CSplashingWaterClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSplashingWaterClientDlg::IDD, pParent)
	, m_csSendData(_T(""))
	, m_AccountName(_T(""))
{
	m_Account = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSplashingWaterClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SendButton, m_SendButton);
	DDX_Control(pDX, IDC_EDIT_AllMessage, m_EditAllMessage);
	DDX_Text(pDX, IDC_EDIT_Send, m_csSendData);
	DDX_Text(pDX, IDC_EDIT_Name, m_AccountName);
}

BEGIN_MESSAGE_MAP(CSplashingWaterClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SendButton, &CSplashingWaterClientDlg::OnBnClickedSendbutton)
END_MESSAGE_MAP()


// CSplashingWaterClientDlg 消息处理程序

BOOL CSplashingWaterClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//HttpClient::getInstance()->addObserver(this);

	m_strAccount = Converter::toString(m_Account);

	start_Thread();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSplashingWaterClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSplashingWaterClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSplashingWaterClientDlg::run()
{
	//检测是否有消息，如果有，则更新，否则，则跳过
	if (MessageBuffer::getInstance()->getFriendMsgFlag(m_strAccount.c_str()))
	{
		CString csOld;
		m_ReceiveMsg = MessageBuffer::getInstance()->getFriendMsg(5, m_strAccount.c_str());
		for (int i = 0; i < m_ReceiveMsg.size(); i++)
		{
			m_EditAllMessage.GetWindowTextW(csOld);
			csOld += _T("Other say:\r\n");
			csOld += Converter::toCString(m_ReceiveMsg[i]);
			csOld += _T("\r\n");
			m_EditAllMessage.SetWindowTextW(csOld);
		}
	}
}

void CSplashingWaterClientDlg::OnBnClickedSendbutton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);//控件到变量
	if (m_csSendData == "")
	{
		return;
	}
	
	SmartPtr<IStrategy> pSendMsg = new SendStrategy(m_strAccount, Converter::toString(m_csSendData));
	pSendMsg->processPackage();

	CString csOld;
	m_EditAllMessage.GetWindowTextW(csOld);
	CString str = _T("\r\n");
	csOld = csOld + (_T("Own say:\r\n"));
	csOld = csOld + m_csSendData;
	csOld = csOld + str;
	m_EditAllMessage.SetWindowTextW(csOld);
}


BOOL CSplashingWaterClientDlg::DestroyWindow()
{
	// TODO:  在此添加专用代码和/或调用基类
	end_Thread();
	return __super::DestroyWindow();
}
