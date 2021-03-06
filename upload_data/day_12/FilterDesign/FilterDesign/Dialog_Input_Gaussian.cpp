// Dialog_Input_Gaussian.cpp: 구현 파일
//

#include "stdafx.h"
#include "FilterDesign.h"
#include "Dialog_Input_Gaussian.h"
#include "afxdialogex.h"

#define MIN_MEAN -199
#define MAX_MEAN 199
#define MIN_SIGMA 1
#define MAX_SIGMA 100

// Dialog_Input_Gaussian 대화 상자

IMPLEMENT_DYNAMIC(Dialog_Input_Gaussian, CDialogEx)

Dialog_Input_Gaussian::Dialog_Input_Gaussian(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GAUSSIAN, pParent)
	, m_editMean(MIN_MEAN)
	, m_editSigma(MIN_SIGMA)
{

}

Dialog_Input_Gaussian::~Dialog_Input_Gaussian()
{
}

void Dialog_Input_Gaussian::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_MEAN, h_sliderMean);
	DDX_Control(pDX, IDC_SLIDER_SIGMA, h_sliderSigma);
	DDX_Text(pDX, IDC_EDIT_MEAN, m_editMean);
	DDX_Text(pDX, IDC_EDIT_SIGMA, m_editSigma);
	DDX_Control(pDX, IDC_EDIT_MEAN, h_editMean);
	DDX_Control(pDX, IDC_EDIT_SIGMA, h_editSigma);
	DDV_MinMaxInt(pDX, m_editMean, MIN_MEAN, MAX_SIGMA);
	DDV_MinMaxInt(pDX, m_editSigma, MIN_SIGMA, MAX_SIGMA);
}


BEGIN_MESSAGE_MAP(Dialog_Input_Gaussian, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_MEAN, &Dialog_Input_Gaussian::OnEnChangeEditMean)
	ON_EN_CHANGE(IDC_EDIT_SIGMA, &Dialog_Input_Gaussian::OnEnChangeEditSigma)
END_MESSAGE_MAP()


// Dialog_Input_Gaussian 메시지 처리기


void Dialog_Input_Gaussian::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	h_sliderMean.SetRange(MIN_MEAN, MAX_MEAN);
	h_sliderSigma.SetRange(MIN_SIGMA, MAX_SIGMA);

	int nMean = h_sliderMean.GetPos();
	int nSigma = h_sliderSigma.GetPos();
	CString strMean;
	CString strSigma;
	strMean.Format(_T("%d"), nMean);
	strSigma.Format(_T("%d"), nSigma);

	if (pScrollBar->GetSafeHwnd() == h_sliderMean.m_hWnd) {
		h_editMean.SetWindowTextW(strMean);
		m_editMean = nMean;
	}
	else if (pScrollBar->GetSafeHwnd() == h_sliderSigma.m_hWnd) {
		h_editSigma.SetWindowTextW(strSigma);
		m_editSigma = nSigma;
	}
	else { return; }

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Dialog_Input_Gaussian::OnEnChangeEditMean()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_editMean < MIN_MEAN) MessageBox(_T("최소 입력 범위를 벗어났습니다."),_T("범위 미달"));
	else if(m_editMean > MAX_MEAN) MessageBox(_T("최대 입력 범위를 벗어났습니다."), _T("범위 초과"));
	h_sliderMean.SetPos(m_editMean);
}


void Dialog_Input_Gaussian::OnEnChangeEditSigma()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_editSigma < MIN_SIGMA) MessageBox(_T("최소 입력 범위를 벗어났습니다."), _T("범위 미달"));
	else if (m_editSigma > MAX_SIGMA) MessageBox(_T("최대 입력 범위를 벗어났습니다."), _T("범위 초과"));
	h_sliderSigma.SetPos(m_editSigma);
}
