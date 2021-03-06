// GenFilter_Dialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "TermProject.h"
#include "GenFilter_Dialog.h"
#include "afxdialogex.h"


// GenFilter_Dialog 대화 상자

IMPLEMENT_DYNAMIC(GenFilter_Dialog, CDialogEx)

GenFilter_Dialog::GenFilter_Dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GENFILTER, pParent)
	, m_FilterType(_T(""))
	, m_FilterDegree(0)
	, m_FilterFreq(0)
{

}

GenFilter_Dialog::~GenFilter_Dialog()
{
}

void GenFilter_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FilterType, h_Combo_FilterType);
	DDX_CBString(pDX, IDC_COMBO_FilterType, m_FilterType);
	DDX_Text(pDX, IDC_EDIT_FilterDegree, m_FilterDegree);
	DDX_Text(pDX, IDC_EDIT_FilterFreq, m_FilterFreq);
}


BEGIN_MESSAGE_MAP(GenFilter_Dialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_FilterType, &GenFilter_Dialog::OnCbnSelchangeComboFiltertype)
END_MESSAGE_MAP()


// GenFilter_Dialog 메시지 처리기


void GenFilter_Dialog::OnCbnSelchangeComboFiltertype()
{
	h_Combo_FilterType.GetLBText(h_Combo_FilterType.GetCurSel(), m_FilterType); // 값 가져오기

	if (m_FilterType == "Low Pass") {
		GetDlgItem(IDC_EDIT_FilterDegree)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FilterFreq)->EnableWindow(TRUE);
	}
	else if (m_FilterType == "Chebyshev" || m_FilterType == "Butterworth") {
		GetDlgItem(IDC_EDIT_FilterDegree)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FilterFreq)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT_FilterDegree)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FilterFreq)->EnableWindow(TRUE);
	}

	UpdateData();
}
