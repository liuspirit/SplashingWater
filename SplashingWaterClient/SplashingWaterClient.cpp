
// SplashingWaterClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "SplashingWaterClient.h"
#include "SplashingWaterClientDlg.h"
#include "LogicDlg.h"
#include "MessageBuffer.h"
#include "MainPageDlg.h"
#include "StateStrategy.h"
#include "SmartPtr.h"
#include "ConfigReader.h"
#include "Converter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSplashingWaterClientApp

BEGIN_MESSAGE_MAP(CSplashingWaterClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSplashingWaterClientApp ����

CSplashingWaterClientApp::CSplashingWaterClientApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSplashingWaterClientApp ����

CSplashingWaterClientApp theApp;


// CSplashingWaterClientApp ��ʼ��

BOOL CSplashingWaterClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	ConfigReader configReader;
	string strLogLevel = configReader.read("LogLevel");
	LogManager::getInstance()->setOutLevel(std::stoi(strLogLevel));
	

	HttpClient::getInstance();
	MessageBuffer::getInstance();

	HttpClient::getInstance()->initial();
	MessageBuffer::getInstance()->initial();

	
	
	string strServerIP = configReader.read("ServerIP");
	if (!HttpClient::getInstance()->connectServer(strServerIP.c_str(), 5120)) //������127.0.0.1���˿ں�
	{
		return FALSE;
	}
	


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	

	INT_PTR nResponse;
	
	LogicDlg logicDlg;
	m_pMainWnd = &logicDlg;
	nResponse = logicDlg.DoModal();
	if (nResponse == IDCANCEL)
	{
		SmartPtr<IStrategy> offline = new StateStrategy(0);
		offline->processPackage();
		return FALSE;
	}

	MainPageDlg mdlg;
	m_pMainWnd = &mdlg;
	nResponse = mdlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else
	{

	}

	SmartPtr<IStrategy> offline = new StateStrategy(0);
	offline->processPackage();
	
	MessageBuffer::DestoryInstance();


	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	HttpClient::getInstance()->disConnectServer();
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

