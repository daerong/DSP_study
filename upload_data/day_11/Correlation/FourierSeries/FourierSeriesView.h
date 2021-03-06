
// FourierSeriesView.h: CFourierSeriesView 클래스의 인터페이스
//

#pragma once

#define RectStartX 20
#define RectStartY 20
#define RectEndX 800 + RectStartX
#define RectEndY 600 + RectStartY

#define OriginX 0
#define SignalStart 0

#define DataVolume 800		// Array에 저장할 Data의 크기


class CFourierSeriesView : public CView
{
protected: // serialization에서만 만들어집니다.
	CFourierSeriesView() noexcept;
	DECLARE_DYNCREATE(CFourierSeriesView)

// 특성입니다.
public:
	CFourierSeriesDoc* GetDocument() const;

// 작업입니다.
public:
	int m_CoeNo, m_FS_Freq; 
	double m_InFSData[DataVolume];
	double m_OutFSData_Sin[DataVolume];
	double m_OutFSData_Cos[DataVolume];
	int displayType;
	double m_InCoData1[DataVolume];
	double m_InCoData2[DataVolume];
	double m_OutCoData[DataVolume];
	double m_InCoDisp1[DataVolume];
	double m_InCoDisp2[DataVolume];
	double m_OutCoDisp[DataVolume];
	double m_WhiteNoise[DataVolume];

	double m_FreqData1[DataVolume];
	double m_FreqData2[DataVolume];
	double m_FreqData3[DataVolume];

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CFourierSeriesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFourierseries();
	afx_msg void OnFouriercal();
	afx_msg void OnGensigX1();
	afx_msg void OnGensigX2();
	afx_msg void OnAutocorrelation();
	afx_msg void OnCrosscorrelation();
	afx_msg void OnClear();
	afx_msg void OnGensigWhite();
	afx_msg void OnGensigWhite2();
};

#ifndef _DEBUG  // FourierSeriesView.cpp의 디버그 버전
inline CFourierSeriesDoc* CFourierSeriesView::GetDocument() const
   { return reinterpret_cast<CFourierSeriesDoc*>(m_pDocument); }
#endif

