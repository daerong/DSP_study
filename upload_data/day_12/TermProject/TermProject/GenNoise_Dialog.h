#pragma once


// GenNoise_Dialog 대화 상자

class GenNoise_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(GenNoise_Dialog)

public:
	GenNoise_Dialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GenNoise_Dialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GENNOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_NoiseAmp;
	CScrollBar h_noiseAmp_Scroll;
};
