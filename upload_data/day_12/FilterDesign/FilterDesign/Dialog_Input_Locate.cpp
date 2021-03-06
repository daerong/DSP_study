// Dialog_Input_Locate.cpp: 구현 파일
//

#include "stdafx.h"
#include "FilterDesign.h"
#include "Dialog_Input_Locate.h"
#include "afxdialogex.h"


// Dialog_Input_Locate 대화 상자

#define MIN_LOCATE -199
#define MAX_LOCATE 199

IMPLEMENT_DYNAMIC(Dialog_Input_Locate, CDialogEx)

Dialog_Input_Locate::Dialog_Input_Locate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOCATE, pParent)
	, m_editLocate(MIN_LOCATE)
{

}

Dialog_Input_Locate::~Dialog_Input_Locate()
{
}

void Dialog_Input_Locate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_LOCATE, h_sliderLocate);
	DDX_Text(pDX, IDC_EDIT_LOCATE, m_editLocate);
	DDX_Control(pDX, IDC_EDIT_LOCATE, h_editLocate);
	DDV_MinMaxInt(pDX, m_editLocate, MIN_LOCATE, MAX_LOCATE);
}


BEGIN_MESSAGE_MAP(Dialog_Input_Locate, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_LOCATE, &Dialog_Input_Locate::OnEnChangeEditLocate)
END_MESSAGE_MAP()


// Dialog_Input_Locate 메시지 처리기


void Dialog_Input_Locate::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	h_sliderLocate.SetRange(MIN_LOCATE, MAX_LOCATE);

	int nLocate = h_sliderLocate.GetPos();
	CString strLocate;
	strLocate.Format(_T("%d"), nLocate);


	if (pScrollBar->GetSafeHwnd() == h_sliderLocate.m_hWnd) {
		h_editLocate.SetWindowTextW(strLocate);
		m_editLocate = nLocate;
	}
	else { return; }

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Dialog_Input_Locate::OnEnChangeEditLocate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_editLocate < MIN_LOCATE) MessageBox(_T("최소 입력 범위를 벗어났습니다."), _T("범위 미달"));
	else if (m_editLocate > MAX_LOCATE) MessageBox(_T("최대 입력 범위를 벗어났습니다."), _T("범위 초과"));
	h_sliderLocate.SetPos(m_editLocate);
}
