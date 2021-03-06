#pragma once

// GenSignal_Dialog 대화 상자

class GenSignal_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(GenSignal_Dialog)

public:
	GenSignal_Dialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GenSignal_Dialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GENSIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_SigType;
	int m_SigFreq;
	int m_SigVol;
	int m_SigLoc;
	int m_SigWidth;
	afx_msg void OnCbnSelchangeComboSigtype();
	CComboBox h_Combo_SigType;
	void FirstUpdate();
};
