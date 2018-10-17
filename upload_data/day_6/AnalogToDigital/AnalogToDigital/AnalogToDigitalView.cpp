
// AnalogToDigitalView.cpp: CAnalogToDigitalView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AnalogToDigital.h"
#endif

#include "AnalogToDigitalDoc.h"
#include "AnalogToDigitalView.h"


#include "Draw_XY.h"
#include "Gen_signal.h"
#include "Disp_Signal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnalogToDigitalView

IMPLEMENT_DYNCREATE(CAnalogToDigitalView, CView)

BEGIN_MESSAGE_MAP(CAnalogToDigitalView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CAnalogToDigitalView 생성/소멸

CAnalogToDigitalView::CAnalogToDigitalView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAnalogToDigitalView::~CAnalogToDigitalView()
{
}

BOOL CAnalogToDigitalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAnalogToDigitalView 그리기

void CAnalogToDigitalView::OnDraw(CDC* pDC)
{
	CAnalogToDigitalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	Draw_XY CD; 
	CD.Disp_Coor(pDC);

	Gen_Signal GS;								//신호발생 
	GS.DATA_No =1024;							//data 수 
	GS.m_FreQ=1;								//신호 주파수 
	GS.m_string="cos";							//발생신호 
	GS.Signal_Data();							//신호발생 
	for(int i=0; i<GS.DATA_No; i++) { 
		Signal_Data1[i] = GS.Signal_Data1[i];
		Signal_Data2[i] = GS.Signal_Data2[i];
		Signal_Data3[i] = GS.Signal_Data3[i];
		Signal_Sum[i] = (GS.Signal_Data1[i] + GS.Signal_Data2[i] + GS.Signal_Data3[i])/3;
	}
	Disp_text1 = GS.Text1;
	Disp_text2 = GS.Text2;
	Disp_text3 = GS.Text3;
	//발생신호 view class에서 저장

	Disp_Signal Ds; 
	for (int i = 0; i < GS.DATA_No; i++) {
		Ds.Disp_Data[i] = Signal_Data1[i]; //발생신호를 그리기용 변수로 이동 
	} 

	CPoint CP; //X, Y좌표를 위한 객체 생성 
	CP.x = X_Start; //시작 x좌표 
	CP.y = Y_Start + Y_Raise; //시작 y 좌표 // 
	Ds.Display_Signal(pDC, X_Start, Y_Start + Y_Raise, Disp_text1, 255, 0, 0);
	Ds.Display_Signal(pDC, CP, 255, 0, 0);

	for (int i = 0; i < GS.DATA_No; i++) {
		Ds.Disp_Data[i] = Signal_Data2[i]; //발생신호를 그리기용 변수로 이동 
	}

	CP.x = X_Start; //시작 x좌표 
	CP.y = Y_Start + 2 * Y_Raise; //시작 y 좌표 // 
	Ds.Display_Signal(pDC, X_Start, Y_Start + 2 * Y_Raise, Disp_text2, 0, 255, 0);
	Ds.Display_Signal(pDC, CP, 0, 255, 0);

	for (int i = 0; i < GS.DATA_No; i++) {
		Ds.Disp_Data[i] = Signal_Data3[i]; //발생신호를 그리기용 변수로 이동 
	}
 
	CP.x = X_Start; //시작 x좌표 
	CP.y = Y_Start + 3 * Y_Raise; //시작 y 좌표 // 
	Ds.Display_Signal(pDC, X_Start, Y_Start + 3 * Y_Raise, Disp_text3, 0, 0, 255);
	Ds.Display_Signal(pDC, CP, 0, 0, 255);

	for (int i = 0; i < GS.DATA_No; i++) {
		Ds.Disp_Data[i] = Signal_Sum[i]; //발생신호를 그리기용 변수로 이동 
	}

	CP.x = X_Start; //시작 x좌표 
	CP.y = Y_Start + 4 * Y_Raise; //시작 y 좌표 // 
	Ds.Display_Signal(pDC, X_Start, Y_Start + 4 * Y_Raise, NULL , 0, 0, 0);
	Ds.Display_Signal(pDC, CP, 0, 0, 0);

}


// CAnalogToDigitalView 인쇄

BOOL CAnalogToDigitalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAnalogToDigitalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAnalogToDigitalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAnalogToDigitalView 진단

#ifdef _DEBUG
void CAnalogToDigitalView::AssertValid() const
{
	CView::AssertValid();
}

void CAnalogToDigitalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnalogToDigitalDoc* CAnalogToDigitalView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnalogToDigitalDoc)));
	return (CAnalogToDigitalDoc*)m_pDocument;
}
#endif //_DEBUG


// CAnalogToDigitalView 메시지 처리기
