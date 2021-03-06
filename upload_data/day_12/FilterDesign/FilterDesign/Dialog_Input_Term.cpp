// Dialog_Input_Term.cpp: 구현 파일
//

#include "stdafx.h"
#include "FilterDesign.h"
#include "Dialog_Input_Term.h"
#include "afxdialogex.h"

#define MIN_TERM 2
#define MAX_TERM 200

// Dialog_Input_Term 대화 상자

IMPLEMENT_DYNAMIC(Dialog_Input_Term, CDialogEx)

Dialog_Input_Term::Dialog_Input_Term(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TERM, pParent)
	, m_editTerm(MIN_TERM)
{

}

Dialog_Input_Term::~Dialog_Input_Term()
{
}

void Dialog_Input_Term::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_TREM, h_sliderTerm);
	DDX_Text(pDX, IDC_EDIT_TERM, m_editTerm);
	DDX_Control(pDX, IDC_EDIT_TERM, h_editTerm);
	DDV_MinMaxInt(pDX, m_editTerm, MIN_TERM, MAX_TERM);
}


BEGIN_MESSAGE_MAP(Dialog_Input_Term, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_TERM, &Dialog_Input_Term::OnEnChangeEditTerm)
END_MESSAGE_MAP()


// Dialog_Input_Term 메시지 처리기


void Dialog_Input_Term::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	h_sliderTerm.SetRange(MIN_TERM, MAX_TERM);

	int nTerm = h_sliderTerm.GetPos();
	CString strTerm;
	strTerm.Format(_T("%d"), nTerm);


	if (pScrollBar->GetSafeHwnd() == h_sliderTerm.m_hWnd) {
		h_editTerm.SetWindowTextW(strTerm);
		m_editTerm = nTerm;
	}
	else { return; }

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Dialog_Input_Term::OnEnChangeEditTerm()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_editTerm < MIN_TERM) MessageBox(_T("최소 입력 범위를 벗어났습니다."), _T("범위 미달"));
	else if (m_editTerm > MAX_TERM) MessageBox(_T("최대 입력 범위를 벗어났습니다."), _T("범위 초과"));
	h_sliderTerm.SetPos(m_editTerm);
}
