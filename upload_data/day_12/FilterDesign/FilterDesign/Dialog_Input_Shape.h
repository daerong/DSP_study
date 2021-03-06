#pragma once


// Dialog_Input_Shape 대화 상자

class Dialog_Input_Shape : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Input_Shape)

public:
	Dialog_Input_Shape(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dialog_Input_Shape();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHAPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl h_sliderLocate;
	CSliderCtrl h_sliderWidth;
	int m_editLocate;
	int m_editWidth;
	CEdit h_editLocate;
	CEdit h_editWidth;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditLocate();
	afx_msg void OnEnChangeEditWidth();
};
