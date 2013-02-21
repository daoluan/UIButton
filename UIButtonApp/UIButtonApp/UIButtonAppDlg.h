// UIButtonAppDlg.h : 头文件
//

#pragma once

#include "./UIButton/UIButton.h"

// CUIButtonAppDlg 对话框
class CUIButtonAppDlg : public CDialog
{
// 构造
public:
	CUIButtonAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UIBUTTONAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	UIButton m_btn;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();

	afx_msg void OnbtnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
