
// FilterDesignView.h: CFilterDesignView 클래스의 인터페이스
//

#pragma once

#define RectStartX 20
#define RectStartY 20
#define RectEndX 800 + RectStartX
#define RectEndY 600 + RectStartY

#define OriginX 400
#define SignalStart -200

#define DataVolume 400		// Array에 저장할 Data의 크기


class CFilterDesignView : public CView
{
protected: // serialization에서만 만들어집니다.
	CFilterDesignView() noexcept;
	DECLARE_DYNCREATE(CFilterDesignView)

// 특성입니다.
public:
	CFilterDesignDoc* GetDocument() const;

// 작업입니다.
public:
	double m_InputSig[DataVolume];
	double m_InputFreq[DataVolume];
	double m_WhiteNoise[DataVolume];
	double m_TransSig[DataVolume];
	double m_TransFreq[DataVolume];
	double *m_OutputSig;
	double m_OutputFreq[DataVolume];
	int m_ResultVolume;
	int m_ResultStart;

	int inputFreq;
	int inputLocate;
	int inputTerm;
	int inputWidth;
	int filterFreq;
	int filterDegree;

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
	virtual ~CFilterDesignView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGenSine();
	afx_msg void OnGenCosine();
	afx_msg void OnGenImpulse();
	afx_msg void OnGenImpulsetrain();
	afx_msg void OnGenTriangle();
	afx_msg void OnGenRectangle();
	afx_msg void OnGenUniform();
	afx_msg void OnGenWhite();
	afx_msg void OnInputClear();
	void InputFourier();
	void TransFourier();
	afx_msg void OnGenGaussian();
	afx_msg void OnGenLpf();
	afx_msg void OnGenButterworth();
	afx_msg void OnGenChebyshev();
	afx_msg void OnConvolution();
};

#ifndef _DEBUG  // FilterDesignView.cpp의 디버그 버전
inline CFilterDesignDoc* CFilterDesignView::GetDocument() const
   { return reinterpret_cast<CFilterDesignDoc*>(m_pDocument); }
#endif

