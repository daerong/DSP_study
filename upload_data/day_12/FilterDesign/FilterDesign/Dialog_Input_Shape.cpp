// Dialog_Input_Shape.cpp: 구현 파일
//

#include "stdafx.h"
#include "FilterDesign.h"
#include "Dialog_Input_Shape.h"
#include "afxdialogex.h"

#define MIN_LOCATE -199
#define MAX_LOCATE 199
#define MIN_WIDTH 1
#define MAX_WIDTH 400

// Dialog_Input_Shape 대화 상자

IMPLEMENT_DYNAMIC(Dialog_Input_Shape, CDialogEx)

Dialog_Input_Shape::Dialog_Input_Shape(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SHAPE, pParent)
	, m_editLocate(MIN_LOCATE)
	, m_editWidth(MIN_WIDTH)
{

}

Dialog_Input_Shape::~Dialog_Input_Shape()
{
}

void Dialog_Input_Shape::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_LOCATE, h_sliderLocate);
	DDX_Control(pDX, IDC_SLIDER_WIDTH, h_sliderWidth);
	DDX_Text(pDX, IDC_EDIT_LOCATE, m_editLocate);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_editWidth);
	DDX_Control(pDX, IDC_EDIT_LOCATE, h_editLocate);
	DDX_Control(pDX, IDC_EDIT_WIDTH, h_editWidth);
	DDV_MinMaxInt(pDX, m_editLocate, MIN_LOCATE, MAX_LOCATE);
	DDV_MinMaxInt(pDX, m_editWidth, MIN_WIDTH, MAX_WIDTH);
}


BEGIN_MESSAGE_MAP(Dialog_Input_Shape, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_LOCATE, &Dialog_Input_Shape::OnEnChangeEditLocate)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &Dialog_Input_Shape::OnEnChangeEditWidth)
END_MESSAGE_MAP()


// Dialog_Input_Shape 메시지 처리기


void Dialog_Input_Shape::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	h_sliderLocate.SetRange(MIN_LOCATE, MAX_LOCATE);
	h_sliderWidth.SetRange(MIN_WIDTH, MAX_WIDTH);

	int nLocate = h_sliderLocate.GetPos();
	int nWidth = h_sliderWidth.GetPos();
	CString strLocate;
	CString strWidth;
	strLocate.Format(_T("%d"), nLocate);
	strWidth.Format(_T("%d"), nWidth);

	if (pScrollBar->GetSafeHwnd() == h_sliderLocate.m_hWnd) {
		h_editLocate.SetWindowTextW(strLocate);
		m_editLocate = nLocate;
	}
	else if (pScrollBar->GetSafeHwnd() == h_sliderWidth.m_hWnd) {
		h_editWidth.SetWindowTextW(strWidth);
		m_editWidth = nWidth;
	}
	else { return; }

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Dialog_Input_Shape::OnEnChangeEditLocate()
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


void Dialog_Input_Shape::OnEnChangeEditWidth()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_editWidth < MIN_WIDTH) MessageBox(_T("최소 입력 범위를 벗어났습니다."), _T("범위 미달"));
	else if (m_editWidth > MAX_WIDTH) MessageBox(_T("최대 입력 범위를 벗어났습니다."), _T("범위 초과"));
	h_sliderWidth.SetPos(m_editWidth);
}
