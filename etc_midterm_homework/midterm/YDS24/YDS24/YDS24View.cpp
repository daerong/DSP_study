
// YDS24View.cpp: CYDS24View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "YDS24.h"
#endif

#include "YDS24Doc.h"
#include "YDS24View.h"


#include "DrawMatrix.h"
#include "GenSignal.h"
#include "DrawSignal.h"
#include "SignalFunction.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYDS24View

IMPLEMENT_DYNCREATE(CYDS24View, CView)

BEGIN_MESSAGE_MAP(CYDS24View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_CK1_Fre2, &CYDS24View::OnCk1Fre2)
	ON_COMMAND(ID_CK1_Fre8, &CYDS24View::OnCk1Fre8)
	ON_COMMAND(ID_CK1_Fre64, &CYDS24View::OnCk1Fre64)
	ON_COMMAND(ID_CK1_Fre256, &CYDS24View::OnCk1Fre256)
	ON_COMMAND(ID_FOURIER_START, &CYDS24View::OnFourierStart)
	ON_COMMAND(ID_Reverse_Start, &CYDS24View::OnReverseStart)
END_MESSAGE_MAP()

// CYDS24View 생성/소멸

CYDS24View::CYDS24View() noexcept : m_CoeNo24(1)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	for (int i = 0; i < DataVolume; i++) {
		m_FsInput1[i].x = 0;
		m_FsInput1[i].y = 0;
		m_FsInput2[i].x = 0;
		m_FsInput2[i].y = 0;
		m_FsOut[i] = 0;
	}
}

CYDS24View::~CYDS24View()
{
}

BOOL CYDS24View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CYDS24View 그리기

void CYDS24View::OnDraw(CDC* pDC)
{
	CYDS24Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawMatrix DM(RectStartX, RectStartY, RectEndX, RectEndY);		// Height = 600
	DM.SetDivide(4, 1);
	DM.StartDraw(pDC);

	CPoint CP;
	DrawSignal DS(DataVolume);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 150;
	DS.setComplexSignal("Cn", m_FsInput1, DataVolume);
	DS.drawImpulse(pDC, CP, SignalStart, 255, 0, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 450;
	DS.setSignal(m_FsOut, DataVolume);
	DS.drawImpulse(pDC, CP, SignalStart, 0, 0, 255);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 300;
	DS.setComplexSignal("Cn", m_FsInput2, DataVolume);
	DS.drawImpulse(pDC, CP, SignalStart, 255, 0, 0);
}


// CYDS24View 인쇄

BOOL CYDS24View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CYDS24View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CYDS24View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CYDS24View 진단

#ifdef _DEBUG
void CYDS24View::AssertValid() const
{
	CView::AssertValid();
}

void CYDS24View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYDS24Doc* CYDS24View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYDS24Doc)));
	return (CYDS24Doc*)m_pDocument;
}
#endif //_DEBUG


// CYDS24View 메시지 처리기


void CYDS24View::OnCk1Fre2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (int i = 0; i < m_CoeNo24; i += 1) {
		m_FsInput1[i].x = 0;
	}


	m_CoeNo24 = 2;

		for (int i = 0; i < m_CoeNo24; i += 1) {
			m_FsInput1[i].x = 1;
	}

		Invalidate();

}


void CYDS24View::OnCk1Fre8()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (int i = 0; i < m_CoeNo24; i += 1) {
		m_FsInput1[i].x = 0;
	}

	m_CoeNo24 = 8;

	for (int i = 0; i < m_CoeNo24; i += 1) {
		m_FsInput1[i].x = 1;
	}
	Invalidate();
}


void CYDS24View::OnCk1Fre64()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (int i = 0; i < m_CoeNo24; i += 1) {
		m_FsInput1[i].x = 0;
	}

	m_CoeNo24 = 64;

	for (int i = 0; i < m_CoeNo24; i += 1) {
		m_FsInput1[i].x = 1;
	}
	Invalidate();
}


void CYDS24View::OnCk1Fre256()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (int i = 0; i < m_CoeNo24; i += 1) {
		m_FsInput1[i].x = 0;
	}

	m_CoeNo24 = 256;

	for (int i = 0; i < m_CoeNo24; i += 1) {
		m_FsInput1[i].x = 1;
	}
	Invalidate();
}


void CYDS24View::OnFourierStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (int n = 0; n < 1024; n++) {
		m_FsOut[n] = 0;
	}

	SignalFunction SF;
	SF.inverseFourierSeries("All", m_FsInput1, m_CoeNo24, DataVolume, DataVolume/16);

	for (int n = 0; n < 1024; n++) {
		m_FsOut[n] += SF.m_SigResult[n];
	}

	Invalidate();
}


void CYDS24View::OnReverseStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (int n = 0; n < 1024; n++) {
		m_FsInput2[n].x = 0;
		m_FsInput2[n].y = 0;
	}

	SignalFunction SF;
	SF.fourierSeries(m_FsOut, DataVolume/16, DataVolume, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_FsInput2[n].x += SF.m_complexResult[n].x;
		m_FsInput2[n].y += SF.m_complexResult[n].y;
	}


	Invalidate();

}
