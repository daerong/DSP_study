
// MFC_PracticeView.h: CMFCPracticeView 클래스의 인터페이스
//

#pragma once

#define Total_Data 1024


class CMFCPracticeView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCPracticeView() noexcept;
	DECLARE_DYNCREATE(CMFCPracticeView)

// 특성입니다.
public:
	CMFCPracticeDoc* GetDocument() const;

// 작업입니다.
public:
	double Signal_Data1[Total_Data] = { 0 };
	double Signal_Data2[Total_Data] = { 0 };
	double Signal_Data3[Total_Data] = { 0 };

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
	virtual ~CMFCPracticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void Disp_Coor(CDC *pDC);
	afx_msg void OnCos1hz();
	afx_msg void OnCos2hz();
	afx_msg void OnSin1hz();
	afx_msg void OnSin2hz();
	void Gen_Signal(CDC *pDC);
	afx_msg void OnSin5hz();
	afx_msg void OnSin50hz();
	afx_msg void OnCos5hz();
	afx_msg void OnCos50hz();
	afx_msg void OnSin3hz();
	afx_msg void OnSin6hz();
	afx_msg void OnCos6hz();
	afx_msg void OnCos3hz();
};

#ifndef _DEBUG  // MFC_PracticeView.cpp의 디버그 버전
inline CMFCPracticeDoc* CMFCPracticeView::GetDocument() const
   { return reinterpret_cast<CMFCPracticeDoc*>(m_pDocument); }
#endif

