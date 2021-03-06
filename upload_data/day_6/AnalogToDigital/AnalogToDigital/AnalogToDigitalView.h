
// AnalogToDigitalView.h: CAnalogToDigitalView 클래스의 인터페이스
//

#pragma once
#define Total_Data 1024
#define RectStart_X 20
#define RectStart_Y 20
#define RectEnd_X 1024 + RectStart_X
#define RectEnd_Y 720

class CAnalogToDigitalView : public CView
{
protected: // serialization에서만 만들어집니다.
	CAnalogToDigitalView() noexcept;
	DECLARE_DYNCREATE(CAnalogToDigitalView)

// 특성입니다.
public:
	CAnalogToDigitalDoc* GetDocument() const;

// 작업입니다.
public:
	double Signal_Data[5][Total_Data] = { 0 };
	double Signal_Sum[Total_Data] = { 0 };
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
	virtual ~CAnalogToDigitalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // AnalogToDigitalView.cpp의 디버그 버전
inline CAnalogToDigitalDoc* CAnalogToDigitalView::GetDocument() const
   { return reinterpret_cast<CAnalogToDigitalDoc*>(m_pDocument); }
#endif

