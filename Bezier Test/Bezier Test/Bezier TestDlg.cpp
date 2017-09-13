
// Bezier TestDlg.cpp : �����t�@�C��
//
// 20170913 githab�ɃR�~�b�g - C.mura

#include "stdafx.h"
#include "Bezier Test.h"
#include "Bezier TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBezierTestDlg �_�C�A���O



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


// CBezierTestDlg ���b�Z�[�W �n���h���[

BOOL CBezierTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
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

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CBezierTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CBezierTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBezierTestDlg::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	//CDialogEx::OnOK();
}


void CBezierTestDlg::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnCancel();
}


void CBezierTestDlg::OnBnClickedTestBtn()
{
	//�@�f�o�C�X�R���e�L�X�g�擾
	CDC* pDC = m_cDrawStcCtl.GetDC();

	// ���z�f�o�C�X�R���e�L�X�g
	CDC memDC, memDCBG, memDCPen, memDCPenAE;
	// ���z�f�o�C�X�R���e�L�X�g�p�r�b�g�}�b�v
	CBitmap memBmp, memBmpBG, memBmpPen, memBmpPenAE;
	// �R���g���[��(�_�C�A���O)��`
	CRect rect;

	// ��`�̎擾
	m_cDrawStcCtl.GetClientRect(rect);
	// ���z�f�o�C�X�R���e�L�X�g�̐���
	memDC.CreateCompatibleDC(pDC);
	memDCBG.CreateCompatibleDC(pDC);
	memDCPen.CreateCompatibleDC(pDC);
	memDCPenAE.CreateCompatibleDC(pDC);
	// ���z�f�r�o�C�X�R���e�L�X�g�p�r�b�g�}�b�v�̐���
	memBmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memBmpBG.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memBmpPen.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memBmpPenAE.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	// �r�b�g�}�b�v�����z�f�o�C�X�R���e�L�X�g�Ɋ��蓖��
	memDC.SelectObject(&memBmp);
	memDCBG.SelectObject(&memBmpBG);
	memDCPen.SelectObject(&memBmpPen);
	memDCPenAE.SelectObject(&memBmpPenAE);

	// ����������`�揈����
	//�A�w�i��(�����y���E�����u���V)
	memDC.Rectangle(rect);
	memDCBG.Rectangle(rect);
	memDCPen.Rectangle(rect);
	memDCPenAE.Rectangle(rect);

	// �i�q�`��
	for(int loop = 0; loop < rect.Width(); loop += 50){
		memDCBG.MoveTo(loop, 0);
		memDCBG.LineTo(loop, rect.Height());
	}
	for(int loop = 0; loop < rect.Height(); loop += 50){
		memDCBG.MoveTo(0, loop);
		memDCBG.LineTo(rect.Width(), loop);
	}

	//�B�y���E�u���V�쐬
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

	//�B�y���E�u���V�ύX
	CPen* oldpen = memDCPen.SelectObject(&pen_red);
	CBrush* oldbr = memDCPen.SelectObject(&br_yellow);
	for(int loop = 0; loop < 100; loop++){
		memDCPen.Ellipse(m_Pt[0][loop].x - 3, m_Pt[0][loop].y - 3, m_Pt[0][loop].x + 3, m_Pt[0][loop].y + 3);
	}

	//������
	memDCPen.SelectObject(oldpen);
	memDCPen.SelectObject(oldbr);
	// �������܂ŕ`�揈����

	// ���z�f�o�C�X�R���e�L�X�g���f�o�C�X�R���e�L�X�g�ɓ\��t��
//	::BitBlt(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), memDCBG.GetSafeHdc(), 0, 0, SRCCOPY);
	// AlphaBlend(); ���s���ۂ̐ݒ���s��.
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;

	// ���ߗ��̐ݒ�.
	// 0 = 0%(���S����), 255 = 100%(�s����).
	bf.SourceConstantAlpha = 192;

	// AlphaBlend(); ���g�p����,�f�o�C�X�R���e�L�X�g�ւ̃R�s�[���s��.
	bf.SourceConstantAlpha = 255;
	memDC.AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(), &memDCBG, rect.left, rect.top, rect.Width(), rect.Height(), bf);
	bf.SourceConstantAlpha = 223;
	memDC.AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(), &memDCPenAE, rect.left, rect.top, rect.Width(), rect.Height(), bf);
	bf.SourceConstantAlpha = 160;
	memDC.AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(), &memDCPen, rect.left, rect.top, rect.Width(), rect.Height(), bf);

	::BitBlt(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), memDC.GetSafeHdc(), 0, 0, SRCCOPY);

	// �g�p�ς݃I�u�W�F�N�g�̔j��
	::DeleteObject(memDC);
	::DeleteObject(memBmp);

//	wchar_t	chHello[] = L"Hello, world!";
//	pDC->TextOut(0, 0, chHello, wcslen(chHello));

	//�ĕ`��
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
				//�ĕ`��
				OnBnClickedTestBtn();
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
