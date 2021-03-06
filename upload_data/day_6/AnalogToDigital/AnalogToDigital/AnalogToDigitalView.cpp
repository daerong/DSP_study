
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

	CString strStyle;
	CString strTitle;

	int x_Raise = 0;
	int y_Raise = (RectEnd_Y - RectStart_Y) / 7;	// (720 - 20) / 7 = 100 

	strTitle = "파형을 그려보자";

	Draw_XY CD(RectStart_X, RectStart_Y, RectEnd_X, RectEnd_Y);
	CD.setMatrix(5, 0);						// 여기서는 간격이 자동 설정됨
	CD.setRaise(x_Raise, y_Raise);			// 직접 설정
	CD.setTitle(strTitle);
	CD.Disp_Coor(pDC);

	strStyle = "cos";

	Gen_Signal GS(strStyle, 50, 256, 1024);	// Gen_Signal(CString style, int amplitude, int frequency, int sampling)
	GS.setStyle(strStyle);					// 파형 선택
	GS.setAmp(1);							// 진폭 선택
	GS.setFreq(4);							// 주파수 1
	GS.setSampling(256);					// sampling rate
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성
	 
	for(int i=0; i< Total_Data; i++) {
		Signal_Data[0][i] = GS.Signal_Data[i];
	}

	CPoint CP;								// CPoint : (x, y)와 같은 좌표 형태로 표현하기 위한 클래스
	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + y_Raise;			// 시작점 y좌표, 2번칸의 시작줄에 그릴 것이므로 +y_Raise  


	strTitle = "Cos, A=1, f=4, fs=256";

	Disp_Signal DS;
	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Data[0], Total_Data);	// memcpy로 배열 복사
	// View클래스에서 DS 메모리에 접근하여 덮어쓰는 것이 빠를까?
	// 아니면 DS의 함수에서 view 클래스의 메모리에 접근하여 덮어쓰는 것이 빠를까?

	DS.Draw_Wave(pDC, CP, 255, 0, 0);
	DS.Draw_Impulse(pDC, CP, 255, 100, 100);
	DS.Draw_Dot(pDC, CP, 100, 0, 0);




	/* 파형 발생 */
	strStyle = "sin";
	GS.setStyle(strStyle);					// 파형 선택
	GS.setAmp(1);							// 진폭 선택
	GS.setFreq(4);							// 주파수 1
	GS.setSampling(256);					// sampling rate
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data; i++) {
		Signal_Data[1][i] = GS.Signal_Data[i];
	}

	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + 2 * y_Raise;		// 시작점 y좌표 

	strTitle = "Sin, A=1, f=4, fs=256";
	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Data[1], Total_Data);	// memcpy로 배열 복사
	DS.Draw_Wave(pDC, CP, 0, 0, 255);
	DS.Draw_Impulse(pDC, CP, 100, 100, 255);
	DS.Draw_Dot(pDC, CP, 0, 0, 100);
	/* 파형 발생 */

	/* 파형 발생 */
	strStyle = "cos";
	GS.setStyle(strStyle);					// 파형 선택
	GS.setAmp(1);							// 진폭 선택
	GS.setFreq(4);							// 주파수 1
	GS.setSampling(512);					// sampling rate
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data; i++) {
		Signal_Data[2][i] = GS.Signal_Data[i];
	}

	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + 3 * y_Raise;		// 시작점 y좌표

	strTitle = "Cos, A=1, f=4, fs=512";
	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Data[2], Total_Data);	// memcpy로 배열 복사
	DS.Draw_Wave(pDC, CP, 0, 255, 0);
	DS.Draw_Impulse(pDC, CP, 100, 255, 100);
	DS.Draw_Dot(pDC, CP, 0, 100, 0);
	/* 파형 발생 */

	/* 파형 발생 */
	strStyle = "sin";
	GS.setStyle(strStyle);					// 파형 선택
	GS.setAmp(1);							// 진폭 선택
	GS.setFreq(4);							// 주파수 1
	GS.setSampling(512);					// sampling rate
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data; i++) {
		Signal_Data[3][i] = GS.Signal_Data[i];
	}

	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + 4 * y_Raise;		// 시작점 y좌표

	strTitle = "Sin, A=1, f=4, fs=512";
	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Data[3], Total_Data);	// memcpy로 배열 복사
	DS.Draw_Wave(pDC, CP, 255, 255, 0);
	DS.Draw_Impulse(pDC, CP, 255, 255, 100);
	DS.Draw_Dot(pDC, CP, 100, 100, 0);
	/* 파형 발생 */

	/* 파형 발생 */
	strStyle = "sin";
	GS.setStyle(strStyle);					// 파형 선택
	GS.setAmp(1);							// 진폭 선택
	GS.setFreq(4);							// 주파수 1
	GS.setSampling(1024);					// sampling rate
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data; i++) {
		Signal_Data[4][i] = GS.Signal_Data[i];
	}

	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + 5 * y_Raise;		// 시작점 y좌표

	strTitle = "Sin, A=1, f=4, fs=1024";
	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Data[4], Total_Data);	// memcpy로 배열 복사
	DS.Draw_Wave(pDC, CP, 0, 255, 255);
	DS.Draw_Impulse(pDC, CP, 100, 255, 255);
	DS.Draw_Dot(pDC, CP, 0, 100, 100);
	/* 파형 발생 */

	/* 합성 신호 */
	for (int i = 0; i < Total_Data; i++) {
		Signal_Sum[i] = (Signal_Data[0][i] + Signal_Data[1][i] + Signal_Data[2][i] + Signal_Data[3][i] + Signal_Data[4][i]) / 5;
	}

	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + 6 * y_Raise;		// 시작점 y좌표

	strTitle = "합성신호";
	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Sum, Total_Data);	// memcpy로 배열 복사
	DS.Draw_Wave(pDC, CP, 0, 0, 0);
	DS.Draw_Impulse(pDC, CP, 200, 200, 200);
	DS.Draw_Dot(pDC, CP, 0, 0, 0);
	/* 합성 신호 */

	pDC->TextOut(0, 0, NULL);

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
