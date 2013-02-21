// UIButtonAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UIButtonApp.h"
#include "UIButtonAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUIButtonAppDlg �Ի���




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


// CUIButtonAppDlg ��Ϣ�������

BOOL CUIButtonAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	EnableToolTips();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUIButtonAppDlg::OnPaint()
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
		CPaintDC dc(this);
		if(m_btn.IsValid())
		{
			m_btn.Create(this,&dc,CRect(10,10,49,30),"�ر�");
			m_btn.InitilizeMem(L"./img/btn.png");
		}
		m_btn.Refresh(&dc);
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUIButtonAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUIButtonAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_btn.OnLButtonDown(nFlags,point);
	CDialog::OnLButtonDown(nFlags, point);
}

void CUIButtonAppDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_btn.OnLButtonUp(nFlags,point))
		OnbtnClose();
	CDialog::OnLButtonUp(nFlags, point);
}

void CUIButtonAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_btn.OnMouseMove(nFlags,point);
	CDialog::OnMouseMove(nFlags, point);
}

void CUIButtonAppDlg::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_btn.OnMouseHover(nFlags,point);
	CDialog::OnMouseHover(nFlags, point);
}

void CUIButtonAppDlg::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_btn.OnMouseLeave();
	CDialog::OnMouseLeave();
}

void CUIButtonAppDlg::OnbtnClose()
{
	SendMessage(WM_CLOSE,0,0);
}

BOOL CUIButtonAppDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_btn.ToolTipRelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}
