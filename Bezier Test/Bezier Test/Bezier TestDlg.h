
// Bezier TestDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"


// CBezierTestDlg ダイアログ
class CBezierTestDlg : public CDialogEx
{
// コンストラクション
public:
	CBezierTestDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_BEZIERTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
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
