#pragma once


// Dialog_Trans_LPF 대화 상자

class Dialog_Trans_LPF : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Trans_LPF)

public:
	Dialog_Trans_LPF(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dialog_Trans_LPF();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LPF };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl h_sliderFreq;
	CEdit h_editFreq;
	int m_editFreq;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditFreq();
};
