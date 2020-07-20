
// SplashingWaterClientDlg.cpp : ʵ���ļ�
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


// CSplashingWaterClientDlg �Ի���



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


// CSplashingWaterClientDlg ��Ϣ�������

BOOL CSplashingWaterClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//HttpClient::getInstance()->addObserver(this);

	m_strAccount = Converter::toString(m_Account);

	start_Thread();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSplashingWaterClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSplashingWaterClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSplashingWaterClientDlg::run()
{
	//����Ƿ�����Ϣ������У�����£�����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);//�ؼ�������
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
	// TODO:  �ڴ����ר�ô����/����û���
	end_Thread();
	return __super::DestroyWindow();
}
