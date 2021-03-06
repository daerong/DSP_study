
// YDS24View.h: CYDS24View 클래스의 인터페이스
//

#pragma once


#define RectStartX 20
#define RectStartY 20
#define RectEndX 1024 + RectStartX
#define RectEndY 600 + RectStartY

#define OriginX 0
#define SignalStart 0

#define DataVolume 1024		// Array에 저장할 Data의 크기


class CYDS24View : public CView
{
protected: // serialization에서만 만들어집니다.
	CYDS24View() noexcept;
	DECLARE_DYNCREATE(CYDS24View)

// 특성입니다.
public:
	CYDS24Doc* GetDocument() const;

// 작업입니다.
public:
	int m_CoeNo24;

	_complex m_FsInput1[1024];
	_complex m_FsInput2[1024];
	double m_FsOut[1024];

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
	virtual ~CYDS24View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCk1Fre2();
	afx_msg void OnCk1Fre8();
	afx_msg void OnCk1Fre64();
	afx_msg void OnCk1Fre256();
	afx_msg void OnFourierStart();
	afx_msg void OnReverseStart();
};

#ifndef _DEBUG  // YDS24View.cpp의 디버그 버전
inline CYDS24Doc* CYDS24View::GetDocument() const
   { return reinterpret_cast<CYDS24Doc*>(m_pDocument); }
#endif

