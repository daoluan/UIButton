#include "StdAfx.h"
#include "UIButton.h"

UIButton::UIButton():m_ctlToolTip(NULL)
{
	m_memCurrent = NULL;
	pDC = NULL;
	m_bTracking = true;
	m_bPush = false;
	m_Notify.SetNom();
}

UIButton::~UIButton(void)
{
	delete m_ctlToolTip;
}

bool UIButton::Create( CWnd * pParent,CDC * pDC,CRect rct,char * strToolTip /*= NULL*/ )
{
	if(pDC == NULL)
		return false;

	this->m_pParent = pParent;
	this->pDC = pDC;
	this->rct = rct;

	if(strToolTip)
	{
		m_ctlToolTip = new CToolTipCtrl();
		m_ctlToolTip->Create(pParent);
		//m_ctlToolTip.SetDelayTime(200);
		m_ctlToolTip->AddTool(pParent,strToolTip,&rct,1);
	}//	if
}

void UIButton::InitilizeMem(WCHAR * SrcFileName)
{
	if (pDC == NULL)
		return;

	CDC predc;
	CBitmap bmpNom,bmpHov,bmpSel,bmpNone,membmp;
	Image * imgSrc = Image::FromFile(SrcFileName);
	int rctWidth = rct.Width(),rctHeight = rct.Height();

	predc.CreateCompatibleDC(pDC);
	bmpNom.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);
	bmpHov.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);
	bmpSel.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);
	bmpNone.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);

	predc.SelectObject(&bmpNom);
	Graphics grap(predc.GetSafeHdc());

	m_memNomal.CreateCompatibleDC(pDC);
	m_memHover.CreateCompatibleDC(pDC);
	m_memSelected.CreateCompatibleDC(pDC);
	m_memNone.CreateCompatibleDC(pDC);

//	Normal++++++++++++++++++++++++++++++++++++++++++++++
	predc.BitBlt(0,0,rctWidth,rctHeight,pDC,rct.left,rct.top,SRCCOPY);	//	Background
	//grap.DrawImage(imgSrc,0,0,rctWidth,rctHeight);	//	Img
	grap.DrawImage(imgSrc,0,0,0,0,rctWidth,rctHeight,UnitPixel);	//	Img
	membmp.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);	//	 Create bitmap
	m_memNomal.SelectObject(&membmp);
	m_memNomal.BitBlt(0,0,rctWidth,rctHeight,&predc,0,0,SRCCOPY);	//	Copy
	membmp.DeleteObject();	//	Delete normal's bitmap
	//prebmp.DeleteObject();

//	Hover++++++++++++++++++++++++++++++++++++++++++++++
	predc.SelectObject(&bmpHov);
	predc.BitBlt(0,0,rctWidth,rctHeight,pDC,rct.left,rct.top,SRCCOPY);	//	Background
	ColorMatrix HotMat = 
	{	
		1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
		0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
		0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
		0.05f, 0.05f, 0.05f, 0.00f, 1.00f	
	};

	ColorMatrix NoneMat = {	
		0.299f, 0.299f, 0.299f, 0.299f,0.299f,
		0.587f, 0.587f, 0.587f, 0.587f,0.587f,
		0.144f, 0.144f, 0.144f, 0.144f,0.144f,
		0.00f,   0.00f,   0.00f,  1.00f,   0.00f,
		0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};
	
	ImageAttributes ia;
	ia.SetColorMatrix(&HotMat);

	float width = (float)rctWidth;
	float height = (float)rctHeight;

	RectF grect; 
	grect.X=0, grect.Y=0; grect.Width = rctWidth; grect.Height = rctHeight;
	grap.DrawImage(imgSrc,grect,0,0,rctWidth,rctHeight,UnitPixel,&ia);	//	Img

	membmp.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);	//	 Recreate bitmap

	m_memHover.SelectObject(&membmp);
	m_memHover.BitBlt(0,0,rctWidth,rctHeight,&predc,0,0,SRCCOPY);	//	Copy
	membmp.DeleteObject();	//	Delete hover's bitmap
	//bmpHov.DeleteObject();

//	Selected++++++++++++++++++++++++++++++++++++++++++++++
	predc.SelectObject(&bmpSel);
	predc.BitBlt(0,0,rctWidth,rctHeight,pDC,rct.left,rct.top,SRCCOPY);	//	Background
	grap.DrawImage(imgSrc,0,0,rctWidth,0,rctWidth,rctHeight,UnitPixel);	//	Img

	membmp.DeleteObject();	//	 Recreate bitmap
	membmp.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);

	m_memSelected.SelectObject(&membmp);
	m_memSelected.BitBlt(0,0,rctWidth,rctHeight,&predc,0,0,SRCCOPY);	//	Copy
	membmp.DeleteObject();	//	Delete selected's bitmap
	//bmpSel.DeleteObject();

//	None++++++++++++++++++++++++++++++++++++++++++++++
	predc.SelectObject(&bmpNone);
	predc.BitBlt(0,0,rctWidth,rctHeight,pDC,rct.left,rct.top,SRCCOPY);	//	Background

	ia.SetColorMatrix(&HotMat);

	grap.DrawImage(imgSrc,grect,0,0,rctWidth,rctHeight,UnitPixel,&ia);	//	Img

	membmp.CreateCompatibleBitmap(pDC,rctWidth,rctHeight);	//	 Recreate bitmap

	m_memNone.SelectObject(&membmp);
	m_memNone.BitBlt(0,0,rctWidth,rctHeight,&predc,0,0,SRCCOPY);	//	Copy
	membmp.DeleteObject();	//	Delete hover's bitmap
	//bmpHov.DeleteObject();

	if(m_memCurrent == NULL)
		m_memCurrent = &m_memNomal;
}

void UIButton::Refresh(CDC * pDC,UINotify notify)
{
	/*if(!notify.None())	//	if notify is valid and copy
		m_Notify = notify;*/

	if(m_Notify.GetNom())
		m_memCurrent = &m_memNomal;
	else if(m_Notify.GetHov())
		m_memCurrent = &m_memHover;
	else if(m_Notify.GetSel())	
		m_memCurrent = &m_memSelected;
	else if(m_Notify.GetNone())
		m_memCurrent = &m_memNone;
	
	pDC->BitBlt(rct.left,rct.top,rct.Width(),rct.Height(),m_memCurrent,0,0,SRCCOPY);
}

void UIButton::OnMouseMove(UINT nFlags, CPoint point )
{
	if(rct.PtInRect(point))
	{
		m_bMouseIn = true;
		if(m_bTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.hwndTrack = m_pParent->GetSafeHwnd();
			tme.dwHoverTime = 100;  //	悬停多少时间之后产生WM_MOUSEHOVER。
			::_TrackMouseEvent(&tme);
			m_bTracking = FALSE;
		}//	if
	}//	if
	else
	{
		OnMouseLeave();
	}
}

void UIButton::OnMouseHover( UINT nFlags, CPoint point )
{
	/*
		当鼠标xpos和ypos确实在UI控件范围内时，才真正启用重绘。
	*/
	if(rct.PtInRect(point))
	{
		m_Notify.SetHov();
		m_pParent->InvalidateRect(&rct);
	}//	if
}

void UIButton::OnMouseLeave()
{
	/*
	*	由于鼠标leave和hover事件只能由控件（窗口）引发，所以此函数无意义。另一方法：
	*	1、m_bMouseIn标记鼠标是否在所定义的UI控件（注意此控件不是真正的窗口控件，而
	*		是UI控件）内。
	*	2、当鼠标在UI控件内，那么m_bMouseIn设置为true
	*		（OnMouseMove函数的工作）。
	*	3、当鼠标离开UI控件（由OnMouseMove检测），那么如果上一状态“鼠标在UI控件内”
	*		（m_bMouseIn为true），重绘窗口。
	*/
	if(m_bMouseIn)
	{
		m_Notify.SetNom();
		m_bTracking = true;
		m_pParent->InvalidateRect(&rct);
		m_bMouseIn = false;
	}//	if

	//m_Notify.SetNom();
	//m_bTracking = true;
	//m_pParent->InvalidateRect(&rct);
}

bool UIButton::OnLButtonUp( UINT nFlags, CPoint point )
{
	//CPoint ptMouse;
	//GetCursorPos(&ptMouse);
	//m_pParent->ScreenToClient(&ptMouse);

	if(!m_Notify.GetNone() && rct.PtInRect(point))
	{
		m_Notify.SetHov();
		m_bPush = false;
		//	Call the btn clicked function.
		m_pParent->InvalidateRect(&rct);
		//AfxMessageBox("成功调用");
		return true;
	}//	if
	else
	{
		m_Notify.SetNom();
		m_pParent->InvalidateRect(&rct);
		return false;
	}
}

void UIButton::OnLButtonDown( UINT nFlags, CPoint point )
{
	//CPoint ptMouse;
	//GetCursorPos(&ptMouse);
	//m_pParent->ScreenToClient(&ptMouse);

	if(!m_Notify.GetNone() && rct.PtInRect(point))
	{
		m_Notify.SetSel();
		m_pParent->InvalidateRect(&rct);
	}//	if
}

void UIButton::ToolTipRelayEvent( MSG* pMsg )
{
	if(m_ctlToolTip->GetSafeHwnd())
		m_ctlToolTip->RelayEvent(pMsg);
}

bool UINotify::GetNom()
{
	return (this->iNotifyFlag & BTN_NORMAL) == BTN_NORMAL;
}

bool UINotify::GetHov()
{
	return (this->iNotifyFlag & BTN_HOVER) == BTN_HOVER;
}

bool UINotify::GetSel()
{
	return (this->iNotifyFlag & BTN_SELECTED) == BTN_SELECTED;
}

bool UINotify::GetNone()
{
	return iNotifyFlag==0;
}

void UINotify::SetNom()
{
	iNotifyFlag = BTN_NORMAL;
}

void UINotify::SetHov()
{
	iNotifyFlag = BTN_HOVER;
}

void UINotify::SetSel()
{
	iNotifyFlag = BTN_SELECTED;
}

void UINotify::SetNone()
{
	iNotifyFlag = 0;
}


UINotify::UINotify()
{
	::memset(&iNotifyFlag,0,sizeof(iNotifyFlag));
}

UINotify::UINotify( int notify )
{
	iNotifyFlag = notify;
}



