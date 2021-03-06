
// WhatisSignalView.h: CWhatisSignalView 클래스의 인터페이스
//

#pragma once

#define ToTal_Data 1024


class CWhatisSignalView : public CView
{
protected: // serialization에서만 만들어집니다.
	CWhatisSignalView() noexcept;
	DECLARE_DYNCREATE(CWhatisSignalView)

// 특성입니다.
public:
	CWhatisSignalDoc* GetDocument() const;

// 작업입니다.
public:
	double Signal_Data1[ToTal_Data];
	double Signal_Data2[ToTal_Data];

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
	virtual ~CWhatisSignalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Disp_Coor(CDC*);
	void Gen_Signal(CDC * pDC);
};

#ifndef _DEBUG  // WhatisSignalView.cpp의 디버그 버전
inline CWhatisSignalDoc* CWhatisSignalView::GetDocument() const
   { return reinterpret_cast<CWhatisSignalDoc*>(m_pDocument); }
#endif

