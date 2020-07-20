// MainPageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplashingWaterClient.h"
#include "MainPageDlg.h"
#include "afxdialogex.h"
#include "Converter.h"
#include "StrTool.h"
#include "MessageHandler.h"
#include "SplashingWaterClientDlg.h"
#include "MessageBuffer.h"
#include "HttpClient.h"
#include "UpdateStrategy.h"
#include "SmartPtr.h"
#include "AddFriendDlg.h"

// MainPageDlg �Ի���

IMPLEMENT_DYNAMIC(MainPageDlg, CDialogEx)

MainPageDlg::MainPageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MainPageDlg::IDD, pParent)
{

}

MainPageDlg::~MainPageDlg()
{
}

void MainPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FriendList, m_FriendList);
}


BEGIN_MESSAGE_MAP(MainPageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &MainPageDlg::OnBnClickedDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FriendList, &MainPageDlg::OnNMDblclkListFriendlist)
	ON_BN_CLICKED(IDC_BUTTON1, &MainPageDlg::OnBnClickedAddFriend)
END_MESSAGE_MAP()


// MainPageDlg ��Ϣ�������

/*
����λ��
�ǳƣ����ߣ���Ϣ��
*/

BOOL MainPageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//����
	m_FriendList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_FriendList.InsertColumn(0, _T("Account"), LVCFMT_LEFT, 53);
	m_FriendList.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 50);
	m_FriendList.InsertColumn(2, _T("Statues"), LVCFMT_LEFT, 50);
	m_FriendList.InsertColumn(3, _T("Message"), LVCFMT_LEFT, 55);

	//�ǳƣ����ߣ��˺�
	string strSource = MessageBuffer::getInstance()->getLogicMsg(1);
	
	vector<string> vSource;
	StrTool::SplitString(strSource, vSource, FriendList_INTERVAL);
	
	int nIndex = 0, nItemIndex = 0;
	while (nIndex < vSource.size() - 2)
	{
		m_FriendList.InsertItem(nItemIndex, _T(""));
		m_FriendList.SetItemText(nItemIndex, 0, Converter::toCString(vSource.at(nIndex)));
		m_FriendList.SetItemText(nItemIndex, 1, Converter::toCString(vSource.at(nIndex + 1)));
		m_FriendList.SetItemText(nItemIndex, 2, Converter::toCString(vSource.at(nIndex + 2)));
		m_FriendList.SetItemText(nItemIndex, 3, _T("0"));

		nItemIndex++;
		nIndex += 3;
	}

	GetDlgItem(IDC_EDIT_Account)->SetWindowTextW(Converter::toCString(vSource.at(0)));
	GetDlgItem(IDC_EDIT_Name)->SetWindowTextW(Converter::toCString(vSource.at(1)));

	HttpClient::getInstance()->addMsgObserver(this);
	//�����߳�
	setSleepTime(1000);
	start_Thread();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void MainPageDlg::update(struct SubjectData subjectData)
{
	Log_Info("MainPageDlg::update    begin");
	if (subjectData.nInt == 2)
	{
		//����״̬
		Log_Info("MainPageDlg::update  status");
		string strState = subjectData.pData2;
		string strAccount = subjectData.pChar;

		for (int i = 0; i < m_FriendList.GetItemCount(); i++)
		{
			if (Converter::toString(m_FriendList.GetItemText(i, 0)) == strAccount)
			{
				m_FriendList.SetItemText(i, 2, Converter::toCString(strState));
				break;
			}
		}
	}
	else if (subjectData.nInt == 4)
	{
		//�����б�
		Log_Info("MainPageDlg::update list");
		string strOper = subjectData.pData2;
		string strAccountInfo = subjectData.pChar;

		if (strOper == "1")
		{
			//add
			Log_Info("MainPageDlg::update list-----add");
			
			vector<string> vSource;
			StrTool::SplitString(strAccountInfo, vSource, FriendList_INTERVAL);
			if (vSource.size() == 4)
			{
				int nCount = m_FriendList.GetItemCount();
				m_FriendList.InsertItem(nCount, _T(""));
				m_FriendList.SetItemText(nCount, 0, Converter::toCString(vSource.at(1)));
				m_FriendList.SetItemText(nCount, 1, Converter::toCString(vSource.at(2)));
				m_FriendList.SetItemText(nCount, 2, Converter::toCString(vSource.at(3)));
				m_FriendList.SetItemText(nCount, 3, _T("0"));
			}
			else if (vSource.size() == 1)
			{
				if (vSource[0] == "1")
				{
					AfxMessageBox(_T("���˻�������"));
				}
			}
		}
		else if (strOper == "0")
		{
			//delete
			Log_Info("MainPageDlg::update list-----delete");
			for (int i = 0; i < m_FriendList.GetItemCount(); i++)
			{
				if (Converter::toString(m_FriendList.GetItemText(i, 0)) == strAccountInfo)
				{				
					m_FriendList.DeleteItem(i);
					m_FriendList.Arrange(LVA_DEFAULT);
					m_FriendList.RedrawItems(0, m_FriendList.GetItemCount());
					break;
				}
			}
		}
	}
	Log_Info("MainPageDlg::update    end");
}

void MainPageDlg::run()
{
	//�����߳�ȥ�����Ϣ״̬������ֵ
	string strAccount = "";
	bool bMsgFlag = false;
	for (int i = 0; i < m_FriendList.GetItemCount(); i++)
	{
		strAccount = Converter::toString(m_FriendList.GetItemText(i, 0));
		bMsgFlag = MessageBuffer::getInstance()->getFriendMsgFlag(strAccount.c_str());

		if (bMsgFlag)
		{
			m_FriendList.SetItemText(i, 3, _T("1"));
		}
		else
		{
			m_FriendList.SetItemText(i, 3, _T("0"));
		}
	}
}


BOOL MainPageDlg::DestroyWindow()
{
	// TODO:  �ڴ����ר�ô����/����û���
	end_Thread();
	return __super::DestroyWindow();
}


void MainPageDlg::OnBnClickedDel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//��ȡѡ�е�ѡ��
	int n = m_FriendList.GetNextItem(-1, LVIS_SELECTED);
	
	string strAccount = Converter::toString(m_FriendList.GetItemText(n, 0));
	int nChoice = 0;
	SmartPtr<IStrategy> up = new UpdateStrategy(nChoice, strAccount);
	up->processPackage();

}

void MainPageDlg::OnNMDblclkListFriendlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_FriendList.GetFirstSelectedItemPosition();
	int nIndex = m_FriendList.GetNextSelectedItem(pos);

	if (m_FriendList.GetItemText(nIndex, 2) == "0")
	{
		MessageBox(_T("This friend is not online"), _T("Tip"), MB_ICONINFORMATION | MB_YESNOCANCEL);
	}
	else
	{
		CSplashingWaterClientDlg dlg;
		dlg.m_AccountName = m_FriendList.GetItemText(nIndex, 1);
		dlg.m_Account = m_FriendList.GetItemText(nIndex, 0);
		dlg.DoModal();
	}

	UpdateData(false);

	*pResult = 0;
}


void MainPageDlg::OnBnClickedAddFriend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AddFriendDlg dlg;
	dlg.DoModal();
}
