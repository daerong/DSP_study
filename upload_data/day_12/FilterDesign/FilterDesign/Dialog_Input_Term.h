#pragma once


// Dialog_Input_Term 대화 상자

class Dialog_Input_Term : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Input_Term)

public:
	Dialog_Input_Term(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dialog_Input_Term();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TERM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl h_sliderTerm;
	int m_editTerm;
	CEdit h_editTerm;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditTerm();
};
