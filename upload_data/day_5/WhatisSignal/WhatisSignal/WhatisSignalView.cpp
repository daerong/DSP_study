
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

/* Disp_Coor()에서 사용 */
#define X_Start 20
#define Y_Start 20
#define X_End X_Start+650
#define Y_End Y_Start+800
#define Y_Depth 3
#define Y_Raise 100
/* Disp_Coor()에서 사용 */


/* Gen_Signal()에서 사용 */
#define Pi 3.14159
#define FreQ 1 //1Hz 주파수
#define Sampling_256 256
#define Sampling_512 512 //1주기data수
#define Sampling_1024 1024
#define M 50 //신호크기배율
#include <math.h>
/* Gen_Signal()에서 사용 */


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
	Gen_Signal(pDC);
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
	
	for (int i = Y_Raise; i < Y_End; i += Y_Raise) {
		pDC->MoveTo(X_Start, Y_Start + i);
		pDC->LineTo(X_End, Y_Start + i);
	}
}

void CWhatisSignalView::Gen_Signal(CDC* pDC)
{
	CString Text;

	int x;

	Text = "Sin함수, A = 1, f = 1[Hz], N = 256[Hz]";
	pDC->TextOut(X_End + 10, 10 + Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + Pi);
		pDC->SetPixel(X_Start + x, Y_Start + Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + 3* Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + 2 * Pi);
		pDC->SetPixel(X_Start + x, Y_Start + Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}
/*
	Text = "Cos함수, A = 1, f = 1[Hz], N = 256[Hz]";
	pDC->TextOut(X_End + 10, 10 + 2 * Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_256)*x + Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_256)*x + Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_256)*x + 3 * Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_256)*x + 2 * Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}

	Text = "Sin함수, A = 0.5, f = 1[Hz], N = 256[Hz]";
	pDC->TextOut(X_End + 10, 10 + 3 * Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + Pi / 2) / 2;
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + Pi) / 2;
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + 3 * Pi / 2) / 2;
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*FreQ / Sampling_256)*x + 2 * Pi) / 2;
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}

	Text = "Sin함수, A = 1, f = 2[Hz], N = 256[Hz]";
	pDC->TextOut(X_End + 10, 10 + 4 * Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*2*FreQ / Sampling_256)*x + Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*2*FreQ / Sampling_256)*x + Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*2*FreQ / Sampling_256)*x + 3 * Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi*2*FreQ / Sampling_256)*x + 2 * Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}

	Text = "Sin함수, A = 1, f = 1[Hz], N = 512[Hz]";
	pDC->TextOut(X_End + 10, 10 + 5 * Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi * FreQ / Sampling_512)*x + Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 5 * Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi * FreQ / Sampling_512)*x + Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 5 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi * FreQ / Sampling_512)*x + 3 * Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 5 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = sin((2 * Pi * FreQ / Sampling_512)*x + 2 * Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 5 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}*/


	Text = "Sin함수, A = 1, f = 1[Hz], N = 512[Hz]";
	pDC->TextOut(X_End + 10, 10 + 2 * Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_512)*x + Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_512)*x + Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_512)*x + 3 * Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_512)*x + 2 * Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}

	Text = "Sin함수, A = 1, f = 1[Hz], N = 1024[Hz]";
	pDC->TextOut(X_End + 10, 10 + 3 * Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_1024)*x + Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_1024)*x + Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_1024)*x + 3 * Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / Sampling_1024)*x + 2 * Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}

	Text = "Sin함수, A = 1, f = 1[Hz], N = 32[Hz]";
	pDC->TextOut(X_End + 10, 10 + 4 * Y_Raise, Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / 32)*x + Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / 32)*x + Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 255, 0));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / 32)*x + 3 * Pi / 2);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 255));
	}
	for (x = 0; x < X_End - X_Start; x++)
	{
		Signal_Data1[x] = cos((2 * Pi*FreQ / 32)*x + 2 * Pi);
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int(Signal_Data1[x] * M), RGB(0, 0, 0));
	}
}

