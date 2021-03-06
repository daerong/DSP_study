#pragma once


// Dialog_Input_Locate 대화 상자

class Dialog_Input_Locate : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Input_Locate)

public:
	Dialog_Input_Locate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dialog_Input_Locate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOCATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl h_sliderLocate;
	int m_editLocate;
	CEdit h_editLocate;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditLocate();
};
