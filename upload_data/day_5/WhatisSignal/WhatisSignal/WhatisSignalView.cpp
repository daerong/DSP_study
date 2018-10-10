
// WhatisSignalView.cpp: CWhatisSignalView 클래스의 구현



#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WhatisSignal.h"
#endif

#include "WhatisSignalDoc.h"
#include "WhatisSignalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* Disp_Coor에서 사용 */
#define X_Start 20
#define Y_Start 20
#define X_End X_Start+650
#define Y_End Y_Start+800
#define Y_Depth 3
/* Disp_Coor에서 사용 */


// CWhatisSignalView

IMPLEMENT_DYNCREATE(CWhatisSignalView, CView)

BEGIN_MESSAGE_MAP(CWhatisSignalView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWhatisSignalView 생성/소멸

CWhatisSignalView::CWhatisSignalView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWhatisSignalView::~CWhatisSignalView()
{
}

BOOL CWhatisSignalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWhatisSignalView 그리기

void CWhatisSignalView::OnDraw(CDC* pDC)
{
	CWhatisSignalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	Disp_Coor(pDC);
}


// CWhatisSignalView 인쇄

BOOL CWhatisSignalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWhatisSignalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWhatisSignalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CWhatisSignalView 진단

#ifdef _DEBUG
void CWhatisSignalView::AssertValid() const
{
	CView::AssertValid();
}

void CWhatisSignalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWhatisSignalDoc* CWhatisSignalView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWhatisSignalDoc)));
	return (CWhatisSignalDoc*)m_pDocument;
}
#endif //_DEBUG


// CWhatisSignalView 메시지 처리기


void CWhatisSignalView::Disp_Coor(CDC *pDC)
{
	// TODO: 여기에 구현 코드 추가.

	pDC->Rectangle(X_Start, Y_Start, X_End, Y_End);
	//문자출력
	CString Text;
	Text = "Generate Signal";
	pDC->TextOut(30, 30, Text);
	//x 축y축그리기
	pDC->MoveTo(X_Start, Y_Start + 200);
	pDC->LineTo(X_End, Y_Start + 200);
	pDC->MoveTo(X_Start, Y_Start + 400);
	pDC->LineTo(X_End, Y_Start + 400);
	pDC->MoveTo(X_Start, Y_Start + 600);
	pDC->LineTo(X_End, Y_Start + 600);

}


