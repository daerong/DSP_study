
// SignalConvolutionView.h: CSignalConvolutionView 클래스의 인터페이스
//

#pragma once
#define RectStartX 20
#define RectStartY 20
#define RectEndX 1024 + RectStartX
#define RectEndY 600 + RectStartY

#define DataVolume 512		// Array에 저장할 Data의 크기


class CSignalConvolutionView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSignalConvolutionView() noexcept;
	DECLARE_DYNCREATE(CSignalConvolutionView)

// 특성입니다.
public:
	CSignalConvolutionDoc* GetDocument() const;

// 작업입니다.
public:
	double m_InputSig[DataVolume];
	double m_TransSig[DataVolume];
	double *m_OutputSig;
	int m_ResultVolume;

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
	virtual ~CSignalConvolutionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInputSigSin();
	afx_msg void OnTransSigSin();
	afx_msg void OnInputSigCos();
	afx_msg void OnTransSigCos();
	afx_msg void OnInputSigImpulse();
	afx_msg void OnTransSigImpulse();
	afx_msg void OnInputSigImpulseTrain();
	afx_msg void OnTransSigImpulseTrain();
	afx_msg void OnInputSigUniform();
	afx_msg void OnTransSigUniform();
	afx_msg void OnStartConvolution();
};

#ifndef _DEBUG  // SignalConvolutionView.cpp의 디버그 버전
inline CSignalConvolutionDoc* CSignalConvolutionView::GetDocument() const
   { return reinterpret_cast<CSignalConvolutionDoc*>(m_pDocument); }
#endif

