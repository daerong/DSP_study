
// fourierTransformView.h: CfourierTransformView 클래스의 인터페이스
//

#pragma once

#define RectStartX 20
#define RectStartY 20
#define RectEndX 1024 + RectStartX
#define RectEndY 600 + RectStartY

#define OriginX 0
#define SignalStart 0

#define DataVolume 1024		// Array에 저장할 Data의 크기


class CfourierTransformView : public CView
{
protected: // serialization에서만 만들어집니다.
	CfourierTransformView() noexcept;
	DECLARE_DYNCREATE(CfourierTransformView)

// 특성입니다.
public:
	CfourierTransformDoc* GetDocument() const;

// 작업입니다.
public:
	double m_FTIn[DataVolume];
	double m_FTOut[DataVolume];


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
	virtual ~CfourierTransformView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFouriertransformInput();
	afx_msg void OnFouriertransformStart();
};

#ifndef _DEBUG  // fourierTransformView.cpp의 디버그 버전
inline CfourierTransformDoc* CfourierTransformView::GetDocument() const
   { return reinterpret_cast<CfourierTransformDoc*>(m_pDocument); }
#endif

