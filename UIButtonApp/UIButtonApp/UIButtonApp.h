// UIButtonApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#define ULONG_PTR ULONG 
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

// CUIButtonAppApp:
// �йش����ʵ�֣������ UIButtonApp.cpp
//

class CUIButtonAppApp : public CWinApp
{
public:
	CUIButtonAppApp();

// ��д
	public:
	virtual BOOL InitInstance();

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUIButtonAppApp theApp;