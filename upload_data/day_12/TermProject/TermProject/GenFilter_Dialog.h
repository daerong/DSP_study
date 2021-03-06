#pragma once


// GenFilter_Dialog 대화 상자

class GenFilter_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(GenFilter_Dialog)

public:
	GenFilter_Dialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GenFilter_Dialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GENFILTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox h_Combo_FilterType;
	CString m_FilterType;
	int m_FilterDegree;
	afx_msg void OnCbnSelchangeComboFiltertype();
	int m_FilterFreq;
};
