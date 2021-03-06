
// ConvolutionView.h: CConvolutionView 클래스의 인터페이스
//

#pragma once
#define Total_Data 1024
#define RectStart_X 20
#define RectStart_Y 20
#define RectEnd_X 1024 + RectStart_X
#define RectEnd_Y 720


class CConvolutionView : public CView
{
protected: // serialization에서만 만들어집니다.
	CConvolutionView() noexcept;
	DECLARE_DYNCREATE(CConvolutionView)

// 특성입니다.
public:
	CConvolutionDoc* GetDocument() const;

// 작업입니다.
public:
	double Signal_Input[Total_Data] = { 0 };
	double Signal_Transform[Total_Data] = { 0 };
	double Signal_Result[2*Total_Data] = { 0 };
	double resizeFactor = 0;
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
	virtual ~CConvolutionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInputdc();
	afx_msg void OnTransformdc();
	afx_msg void OnConvolution();
	afx_msg void OnInputsine();
	afx_msg void OnTransformcos();
};

#ifndef _DEBUG  // ConvolutionView.cpp의 디버그 버전
inline CConvolutionDoc* CConvolutionView::GetDocument() const
   { return reinterpret_cast<CConvolutionDoc*>(m_pDocument); }
#endif

