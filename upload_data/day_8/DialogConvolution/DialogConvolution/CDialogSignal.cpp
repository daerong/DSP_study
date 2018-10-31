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
}


BEGIN_MESSAGE_MAP(CDialogSignal, CDialog)
END_MESSAGE_MAP()


// CDialogSignal 메시지 처리기
