// Dialog_Trans_Butterworth.cpp: 구현 파일
//

#include "stdafx.h"
#include "FilterDesign.h"
#include "Dialog_Trans_Butterworth.h"
#include "afxdialogex.h"

#define MIN_FREQ 1
#define MAX_FREQ 199
#define MIN_DEGREE 1
#define MAX_DEGREE 20

// Dialog_Trans_Butterworth 대화 상자

IMPLEMENT_DYNAMIC(Dialog_Trans_Butterworth, CDialogEx)

Dialog_Trans_Butterworth::Dialog_Trans_Butterworth(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BUTTER, pParent)
	, m_editFreq(MIN_FREQ)
	, m_editDegree(MIN_DEGREE)
{

}

Dialog_Trans_Butterworth::~Dialog_Trans_Butterworth()
{
}

void Dialog_Trans_Butterworth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_FREQ, h_sliderFreq);
	DDX_Control(pDX, IDC_EDIT_FREQ, h_editFreq);
	DDX_Text(pDX, IDC_EDIT_FREQ, m_editFreq);
	DDX_Control(pDX, IDC_SLIDER_DEGREE, h_sliderDegree);
	DDX_Control(pDX, IDC_EDIT_DEGREE, h_editDegree);
	DDX_Text(pDX, IDC_EDIT_DEGREE, m_editDegree);
	DDV_MinMaxInt(pDX, m_editFreq, MIN_FREQ, MAX_FREQ);
	DDV_MinMaxInt(pDX, m_editDegree, MIN_DEGREE, MAX_DEGREE);
}


BEGIN_MESSAGE_MAP(Dialog_Trans_Butterworth, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_FREQ, &Dialog_Trans_Butterworth::OnEnChangeEditFreq)
	ON_EN_CHANGE(IDC_EDIT_DEGREE, &Dialog_Trans_Butterworth::OnEnChangeEditDegree)
END_MESSAGE_MAP()


// Dialog_Trans_Butterworth 메시지 처리기


void Dialog_Trans_Butterworth::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	h_sliderFreq.SetRange(MIN_FREQ, MAX_FREQ);
	h_sliderDegree.SetRange(MIN_DEGREE, MAX_DEGREE);

	int nFreq = h_sliderFreq.GetPos();
	int nDegree = h_sliderDegree.GetPos();
	CString strFreq;
	CString strDegree;
	strFreq.Format(_T("%d"), nFreq);
	strDegree.Format(_T("%d"), nDegree);


	if (pScrollBar->GetSafeHwnd() == h_sliderFreq.m_hWnd) {
		h_editFreq.SetWindowTextW(strFreq);
		m_editFreq = nFreq;
	}
	else if (pScrollBar->GetSafeHwnd() == h_sliderDegree.m_hWnd) {
		h_editDegree.SetWindowTextW(strDegree);
		m_editDegree = nDegree;
	}
	else { return; }

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Dialog_Trans_Butterworth::OnEnChangeEditFreq()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_editFreq < MIN_FREQ) MessageBox(_T("최소 입력 범위를 벗어났습니다."), _T("범위 미달"));
	else if (m_editFreq > MAX_FREQ) MessageBox(_T("최대 입력 범위를 벗어났습니다."), _T("범위 초과"));
	h_sliderFreq.SetPos(m_editFreq);
}


void Dialog_Trans_Butterworth::OnEnChangeEditDegree()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_editDegree < MIN_FREQ) MessageBox(_T("최소 입력 범위를 벗어났습니다."), _T("범위 미달"));
	else if (m_editDegree > MAX_FREQ) MessageBox(_T("최대 입력 범위를 벗어났습니다."), _T("범위 초과"));
	h_sliderDegree.SetPos(m_editDegree);
}
