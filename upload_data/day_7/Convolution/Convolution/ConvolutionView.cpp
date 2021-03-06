
// ConvolutionView.cpp: CConvolutionView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Convolution.h"
#endif

#include "ConvolutionDoc.h"
#include "ConvolutionView.h"

#include "Draw_XY.h"
#include "Gen_signal.h"
#include "Disp_Signal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConvolutionView

IMPLEMENT_DYNCREATE(CConvolutionView, CView)

BEGIN_MESSAGE_MAP(CConvolutionView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_InputDC, &CConvolutionView::OnInputdc)
	ON_COMMAND(ID_TransformDC, &CConvolutionView::OnTransformdc)
	ON_COMMAND(ID_Convolution, &CConvolutionView::OnConvolution)
	ON_COMMAND(ID_InputSINE, &CConvolutionView::OnInputsine)
	ON_COMMAND(ID_TransformCOS, &CConvolutionView::OnTransformcos)
END_MESSAGE_MAP()

// CConvolutionView 생성/소멸

CConvolutionView::CConvolutionView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CConvolutionView::~CConvolutionView()
{
}

BOOL CConvolutionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CConvolutionView 그리기

void CConvolutionView::OnDraw(CDC* pDC)
{
	CConvolutionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CString strTitle;

	int x_Raise = 0;
	int y_Raise = (RectEnd_Y - RectStart_Y) / 7;	// (720 - 20) / 7 = 100 

	strTitle = "파형을 그려보자";

	Draw_XY CD(RectStart_X, RectStart_Y, RectEnd_X, RectEnd_Y);
	CD.setMatrix(5, 0);						// 여기서는 간격이 자동 설정됨
	CD.setRaise(x_Raise, y_Raise);			// 직접 설정
	CD.setTitle(strTitle);
	CD.Disp_Coor(pDC);

	/////////////////////////////////////////////



	CPoint CP;								// CPoint : (x, y)와 같은 좌표 형태로 표현하기 위한 클래스
	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + y_Raise;			// 시작점 y좌표, 2번칸의 시작줄에 그릴 것이므로 +y_Raise  


	strTitle = "Input Signal";

	Disp_Signal DS;
	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Input, Total_Data);	// memcpy로 배열 복사
	// View클래스에서 DS 메모리에 접근하여 덮어쓰는 것이 빠를까?
	// 아니면 DS의 함수에서 view 클래스의 메모리에 접근하여 덮어쓰는 것이 빠를까?

	DS.Draw_Wave(pDC, CP, 255, 0, 0);
	//DS.Draw_Impulse(pDC, CP, 255, 100, 100);
	//DS.Draw_Dot(pDC, CP, 100, 0, 0);

	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + 2 * y_Raise;			// 시작점 y좌표, 3번칸의 시작줄에 그릴 것이므로 +y_Raise  


	strTitle = "Transform Signal";

	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Transform, Total_Data);	// memcpy로 배열 복사
	// View클래스에서 DS 메모리에 접근하여 덮어쓰는 것이 빠를까?
	// 아니면 DS의 함수에서 view 클래스의 메모리에 접근하여 덮어쓰는 것이 빠를까?

	DS.Draw_Wave(pDC, CP, 0, 0, 255);
	//DS.Draw_Impulse(pDC, CP, 100, 100, 255);
	//DS.Draw_Dot(pDC, CP, 0, 0, 100);

	CP.x = RectStart_X;						// 시작점 x좌표 
	CP.y = RectStart_Y + 3 * y_Raise;			// 시작점 y좌표, 3번칸의 시작줄에 그릴 것이므로 +y_Raise  

	CString ResizeInfo;
	ResizeInfo.Format(_T("%f"), resizeFactor);

	strTitle = "Result Signal // resize factor = ";
	strTitle += ResizeInfo;

	DS.setSubject(strTitle);
	DS.setVolume(Total_Data);				// Data(점) 갯수
	DS.setSignal(Signal_Result, Total_Data);	// memcpy로 배열 복사
	// View클래스에서 DS 메모리에 접근하여 덮어쓰는 것이 빠를까?
	// 아니면 DS의 함수에서 view 클래스의 메모리에 접근하여 덮어쓰는 것이 빠를까?

	DS.Draw_Wave(pDC, CP, 255, 0, 255);
	//DS.Draw_Impulse(pDC, CP, 255, 100, 255);
	//DS.Draw_Dot(pDC, CP, 100, 0, 100);
}


// CConvolutionView 인쇄

BOOL CConvolutionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CConvolutionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CConvolutionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CConvolutionView 진단

#ifdef _DEBUG
void CConvolutionView::AssertValid() const
{
	CView::AssertValid();
}

void CConvolutionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CConvolutionDoc* CConvolutionView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CConvolutionDoc)));
	return (CConvolutionDoc*)m_pDocument;
}
#endif //_DEBUG


// CConvolutionView 메시지 처리기


void CConvolutionView::OnInputdc()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CString strStyle;

	strStyle = "dc";

	Gen_Signal GS(strStyle, 1, 0, 0);
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data/2; i++) {
		Signal_Input[i] = GS.Signal_Data[i];
	}
}

void CConvolutionView::OnInputsine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CString strStyle;

	strStyle = "sin";

	Gen_Signal GS(strStyle, 1, 4, 256);
	GS.setAmp(1);							// 진폭 선택
	GS.setFreq(4);							// 주파수 1
	GS.setSampling(256);					// sampling rate
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data/2; i++) {
		Signal_Input[i] = GS.Signal_Data[i];
	}
}


void CConvolutionView::OnTransformdc()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CString strStyle;

	strStyle = "dc";

	Gen_Signal GS(strStyle, 1, 0, 0);
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data/2; i++) {
		Signal_Transform[i] = GS.Signal_Data[i];
	}
}

void CConvolutionView::OnTransformcos()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	CString strStyle;

	strStyle = "cos";

	Gen_Signal GS(strStyle, 1, 4, 256);
	GS.setAmp(1);							// 진폭 선택
	GS.setFreq(4);							// 주파수 1
	GS.setSampling(256);					// sampling rate
	GS.setVolume(Total_Data);				// Data(점) 갯수
	GS.Make_Signal();						// 신호 생성

	for (int i = 0; i < Total_Data / 2; i++) {
		Signal_Transform[i] = GS.Signal_Data[i];
	}
}



void CConvolutionView::OnConvolution()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	resizeFactor = 0;

	for (int i = 0; i < Total_Data; i++) {
		int convolutionResult = 0;
		for (int j = 0; j <= i; j++) {
			convolutionResult += Signal_Input[j] * Signal_Transform[i - j];
		}
		Signal_Result[i] = convolutionResult;
		if (resizeFactor < Signal_Result[i]) { resizeFactor = Signal_Result[i]; }
	}
	
	for (int i = 0; i < Total_Data; i++) { Signal_Result[i] /= resizeFactor; }

	

}

