#pragma once

#define BTN_NORMAL		0x01	//	Normal style
#define BTN_HOVER		0x10	//	Hover style
#define BTN_SELECTED	0x100	//	Selected style
#define BTN_NONE		0x1000	//	No style	

#include "../UIButtonApp.h"

/*
*	Author:daoluan	date:2012-09-06
*	Home:daoluan.net
*	bool GetNom();	//	Check normal style
*	bool GetHov();	//	Check hover style 
*	bool GetSel();	//	Check selected style
*	void SetNom();	//	Set normal style
*	void SetHov();	//	Set hover style 	
*	void SetSel();	//	Set selected style
*	bool None();	//	Unset all style
*/

class	UINotify
{
private:
	int iNotifyFlag;
public:
	UINotify();
	UINotify(int notify);
	bool GetNom();
	bool GetHov();
	bool GetSel();
	bool GetNone();

	void SetNom();
	void SetHov();
	void SetSel();
	void SetNone();
	bool None(){return iNotifyFlag==0;}
};

class UIButton
{
private:
	CDC m_memNomal;
	CDC m_memHover;
	CDC m_memSelected;
	CDC m_memNone;
	CDC * m_memCurrent;	//	The current dc mem
	CDC * pDC;			//	No usage

	CRect rct;			//	The rct in client
	CWnd * m_pParent;
	
	CToolTipCtrl * m_ctlToolTip;
	UINotify m_Notify;	//	Notify

	bool m_bMouseIn;
	bool m_bTracking;	
	bool m_bPush;

public:
	UIButton();
	~UIButton(void);

	bool Create(CWnd * pParent,CDC * pDC,CRect rct,char * strToolTip = NULL);
	void InitilizeMem(WCHAR * SrcFileName);
	void Refresh(CDC * pDC,UINotify notify = 0);
	bool PtInRect(CPoint &pt){return rct.PtInRect(pt);}
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnMouseHover(UINT nFlags, CPoint point);
	void OnMouseLeave();
	void OnLButtonDown(UINT nFlags, CPoint point);
	bool OnLButtonUp(UINT nFlags, CPoint point);
	void ToolTipRelayEvent(MSG* pMsg);
	bool IsValid(){return m_memCurrent==NULL;}
};

