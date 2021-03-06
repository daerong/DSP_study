
// DialogConvolutionView.h: CDialogConvolutionView 클래스의 인터페이스
//

#pragma once

#define RectStartX 20
#define RectStartY 20
#define RectEndX 1024 + RectStartX
#define RectEndY 600 + RectStartY

#define OriginX 512
#define SignalStart -256

#define DataVolume 512		// Array에 저장할 Data의 크기


class CDialogConvolutionView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDialogConvolutionView() noexcept;
	DECLARE_DYNCREATE(CDialogConvolutionView)

// 특성입니다.
public:
	CDialogConvolutionDoc* GetDocument() const;

// 작업입니다.
public:
	double m_InputSig[DataVolume];
	double m_TransSig[DataVolume];
	double *m_OutputSig;
	int m_ResultVolume;
	int m_ResultStart;

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
	virtual ~CDialogConvolutionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSiggen();
	CString m_SigType1;
	CString m_SigType2;
	int m_SigFreq1;
	int m_SigFreq2;
	int m_SigVol1;
	int m_SigVol2;
	afx_msg void OnSigdraw();
	afx_msg void OnConvolution();
	int m_SigLoc1;
	int m_SigLoc2;
	int m_SigWidth1;
	int m_SigWidth2;
};

#ifndef _DEBUG  // DialogConvolutionView.cpp의 디버그 버전
inline CDialogConvolutionDoc* CDialogConvolutionView::GetDocument() const
   { return reinterpret_cast<CDialogConvolutionDoc*>(m_pDocument); }
#endif

