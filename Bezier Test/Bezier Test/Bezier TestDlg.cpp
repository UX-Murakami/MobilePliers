
// Bezier TestDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Bezier Test.h"
#include "Bezier TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBezierTestDlg ダイアログ



CBezierTestDlg::CBezierTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBezierTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBezierTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRAW_STATIC, m_cDrawStcCtl);
}

BEGIN_MESSAGE_MAP(CBezierTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBezierTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBezierTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_TEST_BTN, &CBezierTestDlg::OnBnClickedTestBtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CBezierTestDlg メッセージ ハンドラー

BOOL CBezierTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	for(int loop = 0; loop < 100; loop++){
		for(int inloop = 0; inloop < 10; inloop++){
			m_Pt[inloop][loop] = {0, 0};
		}
	}

	for(int inloop = 0; inloop < 10; inloop++){
		int r = rand() % 160;
		int g = rand() % 160;
		int b = rand() % 160;
		m_Cr[inloop] = RGB(r + 82, g + 82, b + 82);
		m_CrL[inloop] = RGB(r + 96, g + 96, b + 96);
	}

	m_edCount = 0;
	m_edInit = FALSE;
//	OnBnClickedTestBtn();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CBezierTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CBezierTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBezierTestDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	//CDialogEx::OnOK();
}


void CBezierTestDlg::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnCancel();
}


void CBezierTestDlg::OnBnClickedTestBtn()
{
	//①デバイスコンテキスト取得
	CDC* pDC = m_cDrawStcCtl.GetDC();

	// 仮想デバイスコンテキスト
	CDC memDC, memDCBG, memDCPen, memDCPenAE;
	// 仮想デバイスコンテキスト用ビットマップ
	CBitmap memBmp, memBmpBG, memBmpPen, memBmpPenAE;
	// コントロール(ダイアログ)矩形
	CRect rect;

	// 矩形の取得
	m_cDrawStcCtl.GetClientRect(rect);
	// 仮想デバイスコンテキストの生成
	memDC.CreateCompatibleDC(pDC);
	memDCBG.CreateCompatibleDC(pDC);
	memDCPen.CreateCompatibleDC(pDC);
	memDCPenAE.CreateCompatibleDC(pDC);
	// 仮想デビバイスコンテキスト用ビットマップの生成
	memBmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memBmpBG.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memBmpPen.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memBmpPenAE.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	// ビットマップを仮想デバイスコンテキストに割り当て
	memDC.SelectObject(&memBmp);
	memDCBG.SelectObject(&memBmpBG);
	memDCPen.SelectObject(&memBmpPen);
	memDCPenAE.SelectObject(&memBmpPenAE);

	// ↓ここから描画処理↓
	//②背景白(初期ペン・初期ブラシ)
	memDC.Rectangle(rect);
	memDCBG.Rectangle(rect);
	memDCPen.Rectangle(rect);
	memDCPenAE.Rectangle(rect);

	// 格子描画
	for(int loop = 0; loop < rect.Width(); loop += 50){
		memDCBG.MoveTo(loop, 0);
		memDCBG.LineTo(loop, rect.Height());
	}
	for(int loop = 0; loop < rect.Height(); loop += 50){
		memDCBG.MoveTo(0, loop);
		memDCBG.LineTo(rect.Width(), loop);
	}

	//③ペン・ブラシ作成
	CPen pen_red(PS_SOLID, 1, RGB(255, 0, 0));
	CBrush br_yellow(RGB(255, 255, 0));

	int          err = 0;
	int          nPenStyle = PS_SOLID;
	int          nWidth = 14;
	int          nWidthL = 16;
	CPen myPen[10];
	CPen myPenL[10];

	for(int inloop = 0; inloop < 10; inloop++){
		if(!err) if(!myPenL[inloop].CreatePen(nPenStyle, nWidthL, m_CrL[inloop])) err = 1;
		if(!err) if(!memDCPenAE.SelectObject(&myPenL[inloop])) err = 1;
		memDCPenAE.PolyBezier(m_Pt[inloop], 100);
		if(!err) if(!myPen[inloop].CreatePen(nPenStyle, nWidth, m_Cr[inloop])) err = 1;
		if(!err) if(!memDCPen.SelectObject(&myPen[inloop])) err = 1;
		memDCPen.PolyBezier(m_Pt[inloop], 100);
		//memDCPen.MoveTo(m_Pt[inloop][98].x, m_Pt[inloop][98].y);
		//memDCPen.LineTo(m_Pt[inloop][99].x, m_Pt[inloop][99].y);

		//if(!err) if(!myPen[inloop].CreatePen(nPenStyle, nWidth, m_Cr[inloop])) err = 1;
		//if(!err) if(!memDCPen.SelectObject(&myPen[inloop])) err = 1;
		//for(int loop = 0; loop < 99; loop++){
		//	memDCPen.MoveTo(m_Pt[inloop][loop].x, m_Pt[inloop][loop].y);
		//	memDCPen.LineTo(m_Pt[inloop][loop + 1].x, m_Pt[inloop][loop + 1].y);
		//}
	}

	//③ペン・ブラシ変更
	CPen* oldpen = memDCPen.SelectObject(&pen_red);
	CBrush* oldbr = memDCPen.SelectObject(&br_yellow);
	for(int loop = 0; loop < 100; loop++){
		memDCPen.Ellipse(m_Pt[0][loop].x - 3, m_Pt[0][loop].y - 3, m_Pt[0][loop].x + 3, m_Pt[0][loop].y + 3);
	}

	//初期化
	memDCPen.SelectObject(oldpen);
	memDCPen.SelectObject(oldbr);
	// ↑ここまで描画処理↑

	// 仮想デバイスコンテキストをデバイスコンテキストに貼り付け
//	::BitBlt(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), memDCBG.GetSafeHdc(), 0, 0, SRCCOPY);
	// AlphaBlend(); を行う際の設定を行う.
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;

	// 透過率の設定.
	// 0 = 0%(完全透過), 255 = 100%(不透過).
	bf.SourceConstantAlpha = 192;

	// AlphaBlend(); を使用して,デバイスコンテキストへのコピーを行う.
	bf.SourceConstantAlpha = 255;
	memDC.AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(), &memDCBG, rect.left, rect.top, rect.Width(), rect.Height(), bf);
	bf.SourceConstantAlpha = 223;
	memDC.AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(), &memDCPenAE, rect.left, rect.top, rect.Width(), rect.Height(), bf);
	bf.SourceConstantAlpha = 160;
	memDC.AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(), &memDCPen, rect.left, rect.top, rect.Width(), rect.Height(), bf);

	::BitBlt(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), memDC.GetSafeHdc(), 0, 0, SRCCOPY);

	// 使用済みオブジェクトの破棄
	::DeleteObject(memDC);
	::DeleteObject(memBmp);

//	wchar_t	chHello[] = L"Hello, world!";
//	pDC->TextOut(0, 0, chHello, wcslen(chHello));

	//再描画
	UpdateWindow();
}


void CBezierTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	bSwitch = TRUE;
	OnMouseMove(nFlags, point);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CBezierTestDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	bSwitch = FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CBezierTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(bSwitch == TRUE){
		if(MK_LBUTTON == nFlags){
			m_edCount++;
			if(m_edCount > 0){
				m_edCount = 0;
				if(m_edInit == FALSE){
					m_edInit = TRUE;
					for(int inloop = 0; inloop < 10; inloop++){
						m_Pt[inloop][99].x = point.x + inloop * 14;
						m_Pt[inloop][99].y = point.y + inloop * 14;
					}
				}
				for(int loop = 0; loop <= 99; loop++){
					for(int inloop = 0; inloop < 10; inloop++){
						m_Pt[inloop][loop] = m_Pt[inloop][loop + 1];
					}
				}
				for(int inloop = 0; inloop < 10; inloop++){
					m_Pt[inloop][99].x = point.x + inloop * 14;
					m_Pt[inloop][99].y = point.y + inloop * 14;
				}
				//再描画
				OnBnClickedTestBtn();
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
