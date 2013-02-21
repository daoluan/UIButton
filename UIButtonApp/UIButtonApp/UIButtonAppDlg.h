// UIButtonAppDlg.h : ͷ�ļ�
//

#pragma once

#include "./UIButton/UIButton.h"

// CUIButtonAppDlg �Ի���
class CUIButtonAppDlg : public CDialog
{
// ����
public:
	CUIButtonAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UIBUTTONAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	UIButton m_btn;
	// ���ɵ���Ϣӳ�亯��
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
