#pragma once


// CDialogSignal 대화 상자

class CDialogSignal : public CDialog
{
	DECLARE_DYNAMIC(CDialogSignal)

public:
	CDialogSignal(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDialogSignal();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_SigType1;
	CString m_SigType2;
	int m_SigFreq1;
	int m_SigFreq2;
	int m_SigVol1;
	int m_SigVol2;
	afx_msg void OnCbnSelchangeComboSigtype1();
	CComboBox h_SigType1;
	CComboBox h_SigType2;
	afx_msg void OnCbnSelchangeComboSigtype2();
	int m_SigLoc1;
	int m_SigLoc2;
	int m_SigWidth1;
	int m_SigWidth2;
};
