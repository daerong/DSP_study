// CDialogSignal.cpp: 구현 파일
//

#include "stdafx.h"
#include "DialogConvolution.h"
#include "CDialogSignal.h"
#include "afxdialogex.h"


// CDialogSignal 대화 상자

IMPLEMENT_DYNAMIC(CDialogSignal, CDialog)

CDialogSignal::CDialogSignal(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SIGSET, pParent)
	, m_SigType1(_T("Sin"))
	, m_SigType2(_T("Cos"))
	, m_SigFreq1(5)
	, m_SigFreq2(3)
	, m_SigVol1(512)
	, m_SigVol2(512)
	, m_SigLoc1(0)
	, m_SigLoc2(0)
	, m_SigWidth1(100)
	, m_SigWidth2(100)
{

}

CDialogSignal::~CDialogSignal()
{
}

void CDialogSignal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_SigType1, m_SigType1);
	DDX_CBString(pDX, IDC_COMBO_SigType2, m_SigType2);
	DDX_Text(pDX, IDC_EDIT_SigFreq1, m_SigFreq1);
	DDX_Text(pDX, IDC_EDIT_SigFreq2, m_SigFreq2);
	DDX_Text(pDX, IDC_EDIT_SigVol1, m_SigVol1);
	DDX_Text(pDX, IDC_EDIT_SigVol2, m_SigVol2);
	DDX_Control(pDX, IDC_COMBO_SigType1, h_SigType1);
	DDX_Control(pDX, IDC_COMBO_SigType2, h_SigType2);
	DDX_Text(pDX, IDC_EDIT_SigLoc1, m_SigLoc1);
	DDX_Text(pDX, IDC_EDIT_SigLoc2, m_SigLoc2);
	DDX_Text(pDX, IDC_EDIT_SigWidth1, m_SigWidth1);
	DDX_Text(pDX, IDC_EDIT_SigWidth2, m_SigWidth2);
}


BEGIN_MESSAGE_MAP(CDialogSignal, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SigType1, &CDialogSignal::OnCbnSelchangeComboSigtype1)
	ON_CBN_SELCHANGE(IDC_COMBO_SigType2, &CDialogSignal::OnCbnSelchangeComboSigtype2)
END_MESSAGE_MAP()


// CDialogSignal 메시지 처리기


void CDialogSignal::OnCbnSelchangeComboSigtype1()
{ 
	
	h_SigType1.GetLBText(h_SigType1.GetCurSel(), m_SigType1); // 값 가져오기

	if (m_SigType1 == "Sin" || m_SigType1 == "Cos") {
		GetDlgItem(IDC_EDIT_SigFreq1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigVol1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigLoc1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth1)->EnableWindow(FALSE);
	}
	else if (m_SigType1 == "Impulse") {
		GetDlgItem(IDC_EDIT_SigFreq1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth1)->EnableWindow(FALSE);
	}
	else if (m_SigType1 == "Triangular" || m_SigType1 == "Rectangle") {
		GetDlgItem(IDC_EDIT_SigFreq1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth1)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT_SigFreq1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth1)->EnableWindow(FALSE);
	}

	UpdateData();
}


void CDialogSignal::OnCbnSelchangeComboSigtype2()
{
	h_SigType2.GetLBText(h_SigType2.GetCurSel(), m_SigType2); // 값 가져오기

	if (m_SigType2 == "Sin" || m_SigType2 == "Cos") {
		GetDlgItem(IDC_EDIT_SigFreq2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigVol2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigLoc2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth2)->EnableWindow(FALSE);
	}
	else if (m_SigType2 == "Impulse") {
		GetDlgItem(IDC_EDIT_SigFreq2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth2)->EnableWindow(FALSE);
	}
	else if (m_SigType2 == "Triangular" || m_SigType2 == "Rectangle") {
		GetDlgItem(IDC_EDIT_SigFreq2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth2)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT_SigFreq2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth2)->EnableWindow(FALSE);
	}

	UpdateData();
}
