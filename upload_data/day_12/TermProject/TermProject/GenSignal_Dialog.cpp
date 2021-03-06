// GenSignal_Dialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "TermProject.h"
#include "GenSignal_Dialog.h"
#include "afxdialogex.h"


// GenSignal_Dialog 대화 상자

IMPLEMENT_DYNAMIC(GenSignal_Dialog, CDialogEx)

GenSignal_Dialog::GenSignal_Dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GENSIG, pParent)
	, m_SigType(_T(""))
	, m_SigFreq(0)
	, m_SigVol(0)
	, m_SigLoc(0)
	, m_SigWidth(0)
{

}

GenSignal_Dialog::~GenSignal_Dialog()
{
}

void GenSignal_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_SigType, m_SigType);
	DDX_Text(pDX, IDC_EDIT_SigFreq, m_SigFreq);
	DDX_Text(pDX, IDC_EDIT_SigVol, m_SigVol);
	DDX_Text(pDX, IDC_EDIT_SigLoc, m_SigLoc);
	DDX_Text(pDX, IDC_EDIT_SigWidth, m_SigWidth);
	DDX_Control(pDX, IDC_COMBO_SigType, h_Combo_SigType);
}


BEGIN_MESSAGE_MAP(GenSignal_Dialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SigType, &GenSignal_Dialog::OnCbnSelchangeComboSigtype)
END_MESSAGE_MAP()


// GenSignal_Dialog 메시지 처리기


void GenSignal_Dialog::OnCbnSelchangeComboSigtype()
{
	h_Combo_SigType.GetLBText(h_Combo_SigType.GetCurSel(), m_SigType); // 값 가져오기

	if (m_SigType == "Sin" || m_SigType == "Cos") {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(FALSE);
	}
	else if (m_SigType == "Impulse") {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(FALSE);
	}
	else if (m_SigType == "Triangular" || m_SigType == "Rectangle") {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(FALSE);
	}

	UpdateData();
}

void GenSignal_Dialog::FirstUpdate() {
	if (m_SigType == "Sin" || m_SigType == "Cos") {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(FALSE);
	}
	else if (m_SigType == "Impulse") {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(FALSE);
	}
	else if (m_SigType == "Triangular" || m_SigType == "Rectangle") {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT_SigFreq)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigVol)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigLoc)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SigWidth)->EnableWindow(FALSE);
	}

	UpdateData();
}
