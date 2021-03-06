#pragma once


// Dialog_Input_Gaussian 대화 상자

class Dialog_Input_Gaussian : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Input_Gaussian)

public:
	Dialog_Input_Gaussian(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dialog_Input_Gaussian();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAUSSIAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl h_sliderMean;
	CSliderCtrl h_sliderSigma;
	int m_editMean;
	int m_editSigma;
	CEdit h_editMean;
	CEdit h_editSigma;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditMean();
	afx_msg void OnEnChangeEditSigma();
};
