#pragma once


// Dialog_Trans_Chebyshev 대화 상자

class Dialog_Trans_Chebyshev : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Trans_Chebyshev)

public:
	Dialog_Trans_Chebyshev(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dialog_Trans_Chebyshev();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHEBY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl h_sliderFreq;
	CEdit h_editFreq;
	int m_editFreq;
	CSliderCtrl h_sliderDegree;
	CEdit h_editDegree;
	int m_editDegree;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditFreq();
	afx_msg void OnEnChangeEditDegree();
};
