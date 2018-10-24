
// Conv01View.cpp: CConv01View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Conv01.h"
#endif

#include "Conv01Doc.h"
#include "Conv01View.h"

#include "Draw_XY.h"
#include "Disp_Signal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConv01View

IMPLEMENT_DYNCREATE(CConv01View, CView)

BEGIN_MESSAGE_MAP(CConv01View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_InputSig, &CConv01View::OnInputsig)
	ON_COMMAND(ID_TransferSig, &CConv01View::OnTransfersig)
	ON_COMMAND(ID_ConvFunc, &CConv01View::OnConvfunc)
END_MESSAGE_MAP()

// CConv01View 생성/소멸

CConv01View::CConv01View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	int i = 0;
	for (i = 0; i < 512; i++) {
		m_inputSignal[i] = 0;
		m_transSignal[i] = 0;
		m_afterSignal[i] = 0;
	}
	for (i = 512; i < 1024; i++) {
		m_afterSignal[i] = 0;
	}
}

CConv01View::~CConv01View()
{
}

BOOL CConv01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CConv01View 그리기

void CConv01View::OnDraw(CDC* pDC)
{
	CConv01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CString strTitle;
	strTitle = "Convolution Practice";

	Draw_XY DXY(RectStart_X, RectStart_Y, RectEnd_X, RectEnd_Y);
	DXY.setMatrix(4, 0);		// Raise_Y = 150;
	DXY.setTitle(strTitle);
	DXY.Disp_Coor(pDC);

	
	CPoint Position;

	strTitle = "";

	Position.x = RectStart_X;
	Position.y = RectStart_Y + 150;

	Disp_Signal DS;
	DS.setSubject(strTitle);
	DS.setDrawArea(3);
	DS.setDistanse(100);
	DS.setSignal(m_inputSignal, 512);
	DS.Draw_Impulse(pDC, Position, 0, 0, 0);

	strTitle = "";

	Position.x = RectStart_X;
	Position.y = RectStart_Y + 300;

	DS.setSubject(strTitle);
	DS.setSignal(m_transSignal, 512);
	DS.Draw_Impulse(pDC, Position, 0, 0, 0);


	Position.x = RectStart_X;
	Position.y = RectStart_Y + 450;

	strTitle = "output Signal";

	DS.setSubject(strTitle);
	DS.setDrawArea(6);
	DS.setSignal(m_afterSignal, 1024);
	DS.Draw_Impulse(pDC, Position, 0, 0, 0);


}


// CConv01View 인쇄

BOOL CConv01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CConv01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CConv01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CConv01View 진단

#ifdef _DEBUG
void CConv01View::AssertValid() const
{
	CView::AssertValid();
}

void CConv01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CConv01Doc* CConv01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CConv01Doc)));
	return (CConv01Doc*)m_pDocument;
}
#endif //_DEBUG


// CConv01View 메시지 처리기


void CConv01View::OnInputsig()
{
	// 초기화 섹션
	for (int i = 0; i < 512; i++) {
		m_inputSignal[i] = 0;
	}

	// 신호입력
	for (int x = 0; x < 512; x++) {
		m_inputSignal[x] = 1;
	}
}


void CConv01View::OnTransfersig()
{
	// 초기화 섹션
	for (int i = 0; i < 512; i++) {
		m_transSignal[i] = 0;
	}

	// 신호입력
	for (int x = 0; x < 512; x++) {
		m_transSignal[x] = 1;
	}
}


void CConv01View::OnConvfunc()
{
	// 초기화 섹션
	for (int i = 0; i < 1024; i++) {
		m_afterSignal[i] = 0;
	}

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int x = 0; x < 1024; x++) {
		for (int y = 0; y <= x; y++) {
			m_afterSignal[x] += m_inputSignal[y] * m_transSignal[x-y];
		}
	}
}
