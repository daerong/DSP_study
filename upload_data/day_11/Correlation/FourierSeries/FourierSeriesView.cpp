// #define _CRT_NONSTDC_NO_DEPRECATE		
// j1 : 1종 베셀함수의 컴파일을 위해 전처리기에 추가


// FourierSeriesView.cpp: CFourierSeriesView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FourierSeries.h"
#endif

#include "FourierSeriesDoc.h"
#include "FourierSeriesView.h"

#include "DrawMatrix.h"
#include "GenSignal.h"
#include "DrawSignal.h"
#include "SignalFunction.h"
#include "AdjMax.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFourierSeriesView

IMPLEMENT_DYNCREATE(CFourierSeriesView, CView)

BEGIN_MESSAGE_MAP(CFourierSeriesView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FOURIERSERIES, &CFourierSeriesView::OnFourierseries)
	ON_COMMAND(ID_FOURIERCAL, &CFourierSeriesView::OnFouriercal)
	ON_COMMAND(ID_GenSig_X1, &CFourierSeriesView::OnGensigX1)
	ON_COMMAND(ID_GenSig_X2, &CFourierSeriesView::OnGensigX2)
	ON_COMMAND(ID_AUTOCORRELATION, &CFourierSeriesView::OnAutocorrelation)
	ON_COMMAND(ID_CROSSCORRELATION, &CFourierSeriesView::OnCrosscorrelation)
	ON_COMMAND(ID_CLEAR, &CFourierSeriesView::OnClear)
	ON_COMMAND(ID_GenSig_White, &CFourierSeriesView::OnGensigWhite)
	ON_COMMAND(ID_GenSig_White2, &CFourierSeriesView::OnGensigWhite2)
END_MESSAGE_MAP()

// CFourierSeriesView 생성/소멸

CFourierSeriesView::CFourierSeriesView() noexcept : m_CoeNo(128), m_FS_Freq(DataVolume), displayType(0)
{
	for (int i = 0; i < DataVolume; i++) {
		m_InFSData[i] = 0;
		m_OutFSData_Sin[i] = 0;
		m_OutFSData_Cos[i] = 0;
		m_InCoData1[i] = 0;
		m_InCoData2[i] = 0;
		m_OutCoData[i] = 0;
		m_InCoDisp1[i] = 0;
		m_InCoDisp2[i] = 0;
		m_OutCoDisp[i] = 0;
		m_WhiteNoise[i] = 0;

		m_FreqData1[i] = 0;
		m_FreqData2[i] = 0;
		m_FreqData3[i] = 0;
	}
}

CFourierSeriesView::~CFourierSeriesView()
{
}

BOOL CFourierSeriesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CFourierSeriesView 그리기

void CFourierSeriesView::OnDraw(CDC* pDC)
{
	CFourierSeriesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawMatrix DM(RectStartX, RectStartY, RectEndX, RectEndY);		// Height = 600
	DM.SetDivide(4, 1);
	DM.StartDraw(pDC);
	DM.SetOutline(RectStartX + 850, RectStartY, RectEndX + 850, RectEndY);
	DM.SetDivide(4, 1);
	DM.StartDraw(pDC);


	CPoint CP;
	DrawSignal DS(DataVolume);
	DS.setVolume(DataVolume);

	if (displayType == 0) {
		CP.x = OriginX + RectStartX;
		CP.y = RectStartY + 150;
		DS.setSignal(m_InFSData, DataVolume);
		DS.drawImpulse(pDC, CP, SignalStart, 0, 0, 0);

		CP.x = OriginX + RectStartX;
		CP.y = RectStartY + 300;
		DS.setSignal(m_OutFSData_Sin, DataVolume);
		DS.drawImpulse(pDC, CP, SignalStart, 0, 0, 255);

		CP.x = OriginX + RectStartX;
		CP.y = RectStartY + 450;
		DS.setSignal(m_OutFSData_Cos, DataVolume);
		DS.drawImpulse(pDC, CP, SignalStart, 255, 0, 0);
	}
	else {
		CP.x = OriginX + RectStartX;
		CP.y = RectStartY + 150;
		DS.setSignal(m_InCoDisp1, DataVolume);
		DS.drawImpulse(pDC, CP, SignalStart, 0, 0, 0);

		

		CP.x = OriginX + RectStartX;
		CP.y = RectStartY + 300;
		DS.setSignal(m_InCoDisp2, DataVolume);
		DS.drawImpulse(pDC, CP, SignalStart, 0, 0, 255);

		CP.x = OriginX + RectStartX;
		CP.y = RectStartY + 450;
		DS.setSignal(m_OutCoDisp, DataVolume);
		DS.drawImpulseNormalize(pDC, CP, SignalStart, 255, 0, 0);

	}

	CP.x = OriginX + RectStartX + 850;
	CP.y = RectStartY + 150;
	DS.setSignal(m_FreqData1, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 0);

	CP.x = OriginX + RectStartX + 850;
	CP.y = RectStartY + 300;
	DS.setSignal(m_FreqData2, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 255);

	CP.x = OriginX + RectStartX + 850;
	CP.y = RectStartY + 450;
	DS.setSignal(m_FreqData3, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 255, 0, 0);
}


// CFourierSeriesView 인쇄

BOOL CFourierSeriesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFourierSeriesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFourierSeriesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CFourierSeriesView 진단

#ifdef _DEBUG
void CFourierSeriesView::AssertValid() const
{
	CView::AssertValid();
}

void CFourierSeriesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFourierSeriesDoc* CFourierSeriesView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFourierSeriesDoc)));
	return (CFourierSeriesDoc*)m_pDocument;
}
#endif //_DEBUG


// CFourierSeriesView 메시지 처리기


void CFourierSeriesView::OnFourierseries()
{
	displayType = 0;
	m_InFSData[0] = 1;

	//// 구형파(square wave) 발생 -> Sin
	//for (int i = 1; i < m_CoeNo; i += 2) {
	//	m_InFSData[i] = 4 / (i*Pi);
	//}

	//// 직각 삼각형(sawtooth wave) 발생 -> Sin
	//for (int i = 1; i < m_CoeNo; i += 1) {
	//	m_InFSData[i] = -4 / (i*Pi);
	//}

	//// 직각 삼각형(sawtooth wave) 발생 -> Sin
	//for (int i = 1; i < m_CoeNo; i += 1) {
	//	m_InFSData[i] = 4 / (i*Pi);
	//}

	// 삼각파(triangle wave) 발생 -> Sin
	for (int i = 1; i < m_CoeNo; i += 2) {
		m_InFSData[i] = 8 * pow(-1, (i - 1) / 2) / (i*i*PI*PI);
	}

	////반원(Semicircle) 발생 -> Cos
	//for (int i = 1; i < m_CoeNo; i += 1) {
	//	m_InFSData[i] = pow(-1, i)* j1(i*PI)/i;
	//}


	//for (int i = 1; i < m_CoeNo; i += 2) {
	//	m_InFSData[i] = 4 * cos(Pi*i/5) / (Pi*i);
	//}


	//for (int i = 1; i < m_CoeNo; i += 2) {
	//	m_InFSData[i] = 1 / (i*Pi);
	//}


	Invalidate();
}


void CFourierSeriesView::OnFouriercal()
{
	displayType = 0;
	SignalFunction SF;
	SF.setVolume(DataVolume);

	SF.fourierSeries("Sin", m_InFSData, m_CoeNo, DataVolume, DataVolume/8);

	for (int n = 0; n < DataVolume; n++) {
		m_OutFSData_Sin[n] = SF.m_SigResult[n];
	} 

	SF.fourierSeries("Cos", m_InFSData, m_CoeNo, DataVolume, DataVolume / 8);

	for (int n = 0; n < DataVolume; n++) {
		m_OutFSData_Cos[n] = SF.m_SigResult[n];
	}

	Invalidate();
}


void CFourierSeriesView::OnGensigX1()
{
	displayType = 1;

	for (int n = 0; n < DataVolume; n++) {
		m_InCoData1[n] = sin(2 * Pi * 1 * n / DataVolume);
		m_InCoDisp1[n] = m_InCoData1[n];
	}

	SignalFunction SF(DataVolume);
	SF.setVolume(DataVolume);
	SF.fourierTranseform(m_InCoData1, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_FreqData1[n] = SF.m_SigResult[n];
	}

	Invalidate();
}


void CFourierSeriesView::OnGensigX2()
{
	displayType = 1;

	for (int n = 0; n < DataVolume; n++) {
		m_InCoData2[n] = sin(2 * Pi * 1 * n / DataVolume);
		m_InCoDisp2[n] = m_InCoData2[n];
	}

	SignalFunction SF(DataVolume);
	SF.setVolume(DataVolume);
	SF.fourierTranseform(m_InCoData2, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_FreqData2[n] = SF.m_SigResult[n];
	}

	Invalidate();
}


void CFourierSeriesView::OnAutocorrelation()
{
	displayType = 1;

	SignalFunction SF(DataVolume);
	SF.setVolume(DataVolume);
	
	SF.correlation(m_InCoData1, DataVolume, m_InCoData1, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_OutCoData[n] = SF.m_SigResult[n];
		m_OutCoDisp[n] = SF.m_SigResult[n];
	}

	SF.fourierTranseform(m_OutCoData, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_FreqData3[n] = SF.m_SigResult[n];
	}

	Invalidate();
}


void CFourierSeriesView::OnCrosscorrelation()
{
	displayType = 1;

	SignalFunction SF(DataVolume);
	SF.setVolume(DataVolume);

	SF.correlation(m_InCoData1, DataVolume, m_InCoData2, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_OutCoData[n] = SF.m_SigResult[n];
		m_OutCoDisp[n] = SF.m_SigResult[n];
	}

	SF.fourierTranseform(m_OutCoData, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_FreqData3[n] = SF.m_SigResult[n];
	}

	Invalidate();
}

void CFourierSeriesView::OnClear()
{
	for (int i = 0; i < DataVolume; i++) {
		m_InFSData[i] = 0;
		m_OutFSData_Sin[i] = 0;
		m_OutFSData_Cos[i] = 0;
		m_InCoData1[i] = 0;
		m_InCoData2[i] = 0;
		m_OutCoData[i] = 0;
		m_InCoDisp1[i] = 0;
		m_InCoDisp2[i] = 0;
		m_OutCoDisp[i] = 0;
		m_WhiteNoise[i] = 0;

		m_FreqData1[i] = 0;
		m_FreqData2[i] = 0;
		m_FreqData3[i] = 0;
	}
	Invalidate();
}


void CFourierSeriesView::OnGensigWhite()
{
	int RandNo;
	for (int n = 0; n < DataVolume; n++)
	{
		RandNo = rand() % 100 - 50; //0-99까지 Randon 숫자 발생 -> -50~-50까지로 변경
		m_WhiteNoise[n] = double(RandNo) / 50; //+1 ~ -1로 조정
	}
	for (int n = 0; n < DataVolume; n++)
	{
		m_InCoData1[n] += m_WhiteNoise[n];
		m_InCoDisp1[n] += m_WhiteNoise[n];
	}

	SignalFunction SF(DataVolume);
	SF.setVolume(DataVolume);
	SF.fourierTranseform(m_InCoData1, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_FreqData1[n] = SF.m_SigResult[n];
	}

	Invalidate();
}


void CFourierSeriesView::OnGensigWhite2()
{
	int RandNo;
	for (int n = 0; n < DataVolume; n++)
	{
		RandNo = rand() % 100 - 50; //0-99까지 Randon 숫자 발생 -> -50~-50까지로 변경
		m_WhiteNoise[n] = double(RandNo) / 50; //+1 ~ -1로 조정
	}
	for (int n = 0; n < DataVolume; n++)
	{
		m_InCoData2[n] += m_WhiteNoise[n];
		m_InCoDisp2[n] += m_WhiteNoise[n];
	}


	SignalFunction SF(DataVolume);
	SF.setVolume(DataVolume);
	SF.fourierTranseform(m_InCoData2, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_FreqData2[n] = SF.m_SigResult[n];
	}

	Invalidate();
}
