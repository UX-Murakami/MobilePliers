
// Bezier TestDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"


// CBezierTestDlg �_�C�A���O
class CBezierTestDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CBezierTestDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
	enum { IDD = IDD_BEZIERTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedTestBtn();
	CStatic m_cDrawStcCtl;

	POINT m_Pt[10][100];
	COLORREF m_Cr[10];
	COLORREF m_CrL[10];
	int m_edCount;
	BOOL m_edInit;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	BOOL bSwitch;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
