// UIButtonApp.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#define ULONG_PTR ULONG 
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

// CUIButtonAppApp:
// 有关此类的实现，请参阅 UIButtonApp.cpp
//

class CUIButtonAppApp : public CWinApp
{
public:
	CUIButtonAppApp();

// 重写
	public:
	virtual BOOL InitInstance();

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
// 实现

	DECLARE_MESSAGE_MAP()
};

extern CUIButtonAppApp theApp;