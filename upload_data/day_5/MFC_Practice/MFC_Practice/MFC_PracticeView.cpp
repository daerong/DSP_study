
// MFC_PracticeView.cpp: CMFCPracticeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_Practice.h"
#endif

#include "MFC_PracticeDoc.h"
#include "MFC_PracticeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* Disp_Coor()에서 사용 */
#define X_Start 20
#define Y_Start 20
#define X_End X_Start+1024
#define Y_End Y_Start+750
#define Y_Depth 3
#define Y_Raise 150
/* Disp_Coor()에서 사용 */

/* Gen_Signal()에서 사용 */
#define Pi 3.14159
#define FreQ 1			//1Hz 주파수
#define DATA_No 512		//1주기data수
#define M 50			//신호크기배율
#include <math.h>

CString Text1;
CString Text2;
CString Text3;
/* Gen_Signal()에서 사용 */


// CMFCPracticeView

IMPLEMENT_DYNCREATE(CMFCPracticeView, CView)

BEGIN_MESSAGE_MAP(CMFCPracticeView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_COS1Hz, &CMFCPracticeView::OnCos1hz)
	ON_COMMAND(ID_COS2Hz, &CMFCPracticeView::OnCos2hz)
	ON_COMMAND(ID_SIN1Hz, &CMFCPracticeView::OnSin1hz)
	ON_COMMAND(ID_SIN2Hz, &CMFCPracticeView::OnSin2hz)
	ON_COMMAND(ID_SIN5Hz, &CMFCPracticeView::OnSin5hz)
	ON_COMMAND(ID_SIN50Hz, &CMFCPracticeView::OnSin50hz)
	ON_COMMAND(ID_COS5Hz, &CMFCPracticeView::OnCos5hz)
	ON_COMMAND(ID_COS50Hz, &CMFCPracticeView::OnCos50hz)
	ON_COMMAND(ID_SIN3Hz, &CMFCPracticeView::OnSin3hz)
	ON_COMMAND(ID_SIN6Hz, &CMFCPracticeView::OnSin6hz)
	ON_COMMAND(ID_COS6Hz, &CMFCPracticeView::OnCos6hz)
	ON_COMMAND(ID_COS3Hz, &CMFCPracticeView::OnCos3hz)
END_MESSAGE_MAP()

// CMFCPracticeView 생성/소멸

CMFCPracticeView::CMFCPracticeView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCPracticeView::~CMFCPracticeView()
{
}

BOOL CMFCPracticeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCPracticeView 그리기

void CMFCPracticeView::OnDraw(CDC* pDC)
{
	CMFCPracticeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	Disp_Coor(pDC);
	Gen_Signal(pDC);
}


// CMFCPracticeView 인쇄

BOOL CMFCPracticeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCPracticeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCPracticeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCPracticeView 진단

#ifdef _DEBUG
void CMFCPracticeView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPracticeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPracticeDoc* CMFCPracticeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPracticeDoc)));
	return (CMFCPracticeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPracticeView 메시지 처리기


void CMFCPracticeView::Disp_Coor(CDC *pDC)
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


void CMFCPracticeView::OnCos1hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 1; 
	for (x = 0; x < X_End - X_Start; x++) 
	{ 
		Text1 = "Cos함수, f = 1[Hz], N = 512[Hz]";
		Signal_Data1[x] = cos((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	} 
	Invalidate();
}


void CMFCPracticeView::OnCos2hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 2;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text1 = "Cos함수, f = 2[Hz], N = 512[Hz]";
		Signal_Data1[x] = cos((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnSin1hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 1;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text1 = "Sin함수, f = 1[Hz], N = 512[Hz]";
		Signal_Data1[x] = sin((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnSin2hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 2;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text1 = "Sin함수, f = 2[Hz], N = 512[Hz]";
		Signal_Data1[x] = sin((2 * Pi* m_freQ / DATA_No)*x + Pi / 2);
	}

	Invalidate();
}




void CMFCPracticeView::OnSin5hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 5;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text2 = "Sin함수, f = 5[Hz], N = 512[Hz]";
		Signal_Data2[x] = sin((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnSin50hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 50;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text2 = "Sin함수, f = 50[Hz], N = 512[Hz]";
		Signal_Data2[x] = sin((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnCos5hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 5;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text2 = "Cos함수, f = 5[Hz], N = 512[Hz]";
		Signal_Data2[x] = sin((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnCos50hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 50;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text2 = "Cos함수, f = 50[Hz], N = 512[Hz]";
		Signal_Data2[x] = sin((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}




void CMFCPracticeView::OnSin3hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 3;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text3 = "Sin함수, f = 3[Hz], N = 512[Hz]";
		Signal_Data3[x] = sin((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnSin6hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 6;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text3 = "Sin함수, f = 6[Hz], N = 512[Hz]";
		Signal_Data3[x] = sin((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnCos3hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 3;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text3 = "Cos함수, f = 3[Hz], N = 512[Hz]";
		Signal_Data3[x] = cos((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}


void CMFCPracticeView::OnCos6hz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, m_freQ = 6;
	for (x = 0; x < X_End - X_Start; x++)
	{
		Text3 = "Cos함수, f = 6[Hz], N = 512[Hz]";
		Signal_Data3[x] = cos((2 * Pi * m_freQ / DATA_No)*x + Pi / 2);
	}
	Invalidate();
}



void CMFCPracticeView::Gen_Signal(CDC *pDC)
{
	// TODO: 여기에 구현 코드 추가.

	int x;

	pDC->TextOut(X_End + 10, 10 + Y_Raise, Text1);


	for (x = 0; x < X_End - X_Start; x++)
	{
		pDC->SetPixel(X_Start + x, Y_Start + Y_Raise - int(Signal_Data1[x] * M), RGB(255, 0, 0));
	}

	pDC->TextOut(X_End + 10, 10 + 2 * Y_Raise, Text2);

	for (x = 0; x < X_End - X_Start; x++)
	{
		pDC->SetPixel(X_Start + x, Y_Start + 2 * Y_Raise - int(Signal_Data2[x] * M), RGB(0, 255, 0));
	}

	pDC->TextOut(X_End + 10, 10 + 3 * Y_Raise, Text3);

	for (x = 0; x < X_End - X_Start; x++)
	{
		pDC->SetPixel(X_Start + x, Y_Start + 3 * Y_Raise - int(Signal_Data3[x] * M), RGB(0, 0, 255));
	}

	CString Result_Text;
	Result_Text = "합성 결과";
	pDC->TextOut(X_End + 10, 10 + 4 * Y_Raise, Result_Text);

	for (x = 0; x < X_End - X_Start; x++)
	{
		pDC->SetPixel(X_Start + x, Y_Start + 4 * Y_Raise - int((Signal_Data1[x] + Signal_Data2[x] + Signal_Data3[x]) * M), RGB(0, 0, 0));
	}

}

