
// SplashingWaterClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSplashingWaterClientApp: 
// �йش����ʵ�֣������ SplashingWaterClient.cpp
//

class CSplashingWaterClientApp : public CWinApp
{
public:
	CSplashingWaterClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSplashingWaterClientApp theApp;