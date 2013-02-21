// UIButtonAppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UIButtonApp.h"
#include "UIButtonAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUIButtonAppDlg 对话框




CUIButtonAppDlg::CUIButtonAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUIButtonAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUIButtonAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUIButtonAppDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// CUIButtonAppDlg 消息处理程序

BOOL CUIButtonAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	EnableToolTips();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUIButtonAppDlg::OnPaint()
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
		CPaintDC dc(this);
		if(m_btn.IsValid())
		{
			m_btn.Create(this,&dc,CRect(10,10,49,30),"关闭");
			m_btn.InitilizeMem(L"./img/btn.png");
		}
		m_btn.Refresh(&dc);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUIButtonAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUIButtonAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_btn.OnLButtonDown(nFlags,point);
	CDialog::OnLButtonDown(nFlags, point);
}

void CUIButtonAppDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_btn.OnLButtonUp(nFlags,point))
		OnbtnClose();
	CDialog::OnLButtonUp(nFlags, point);
}

void CUIButtonAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_btn.OnMouseMove(nFlags,point);
	CDialog::OnMouseMove(nFlags, point);
}

void CUIButtonAppDlg::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_btn.OnMouseHover(nFlags,point);
	CDialog::OnMouseHover(nFlags, point);
}

void CUIButtonAppDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_btn.OnMouseLeave();
	CDialog::OnMouseLeave();
}

void CUIButtonAppDlg::OnbtnClose()
{
	SendMessage(WM_CLOSE,0,0);
}

BOOL CUIButtonAppDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_btn.ToolTipRelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}
