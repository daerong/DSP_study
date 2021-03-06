
// fourierTransformView.cpp: CfourierTransformView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "fourierTransform.h"
#endif

#include "fourierTransformDoc.h"
#include "fourierTransformView.h"

#include "DrawMatrix.h"
#include "GenSignal.h"
#include "DrawSignal.h"
#include "SignalFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CfourierTransformView

IMPLEMENT_DYNCREATE(CfourierTransformView, CView)

BEGIN_MESSAGE_MAP(CfourierTransformView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FOURIERTRANSFORM_INPUT, &CfourierTransformView::OnFouriertransformInput)
	ON_COMMAND(ID_FOURIERTRANSFORM_START, &CfourierTransformView::OnFouriertransformStart)
	ON_COMMAND(ID_INVERSEFOURIER, &CfourierTransformView::OnInversefourier)
	ON_COMMAND(ID_CONVOLUTION, &CfourierTransformView::OnConvolution)
END_MESSAGE_MAP()

// CfourierTransformView 생성/소멸

CfourierTransformView::CfourierTransformView() noexcept : m_OutputSig(NULL),m_ResultVolume(512)
{
	for (int i = 0; i < DataVolume; i++) {

		m_FTIn[i] = 0.0;
		m_FTIn2[i] = 0.0;
		m_FTTrans[i] = 0.0;
		m_FTTrans2[i] = 0.0;
		m_FTInvers[i] = 0.0;
		m_FTOut[i] = 0.0;
	}
}

CfourierTransformView::~CfourierTransformView()
{
}

BOOL CfourierTransformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CfourierTransformView 그리기

void CfourierTransformView::OnDraw(CDC* pDC)
{
	CfourierTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawMatrix DM(RectStartX, RectStartY, RectEndX, RectEndY);		// Height = 600
	DM.SetDivide(8, 1);
	DM.StartDraw(pDC);

	CPoint CP;
	DrawSignal DS(DataVolume);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 100;
	DS.setSignal(m_FTIn, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 255, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 200;
	DS.setSignal(m_FTIn2, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 255, 0, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 300;
	DS.setSignal(m_FTTrans, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 255, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 400;
	DS.setSignal(m_FTTrans2, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 255, 0, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 500;
	DS.setSignal(m_FTInvers, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 255);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 600;
	DS.setSignal(m_FTOut, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 0);

	if (m_OutputSig != NULL) {
		CP.x = OriginX + RectStartX;
		CP.y = RectStartY + 700;
		DS.setSignal(m_OutputSig, m_ResultVolume);
		DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 0);
	}


}


// CfourierTransformView 인쇄

BOOL CfourierTransformView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CfourierTransformView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CfourierTransformView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CfourierTransformView 진단

#ifdef _DEBUG
void CfourierTransformView::AssertValid() const
{
	CView::AssertValid();
}

void CfourierTransformView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CfourierTransformDoc* CfourierTransformView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CfourierTransformDoc)));
	return (CfourierTransformDoc*)m_pDocument;
}
#endif //_DEBUG


// CfourierTransformView 메시지 처리기


void CfourierTransformView::OnFouriertransformInput()
{
	GenSignal GS1(DataVolume), GS2(DataVolume);

	int m_Freq = 1;

	//step1 과제
	//GS1.setStyle("Sin");
	//GS1.makeSin(m_Freq, DataVolume, 0);

	//step2 과제
	GS1.setStyle("Impulse");
	GS1.makeImpulse();

	//GS1.setStyle("tri");
	//GS1.makeRectangle(16, 32);

	//GS2.setStyle("Impulse");
	//GS2.makeImpulse();

	GS2.setStyle("tri");
	GS2.makeTriangular(64, 128);

	for (int i = 0; i < DataVolume; i++) {
		m_FTIn[i] = GS1.m_SigData[i];
		m_FTTrans[i] = GS2.m_SigData[i];
	}

	Invalidate();
}


void CfourierTransformView::OnFouriertransformStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	double m_Real, m_Image;
	double T_Real, T_Image;
	for (int fre = 0; fre < DataVolume; fre++) {		// m_FTOut에 저장되는 값은 특정 freq에서 실수&허수 성분 크기
		T_Real = T_Image = 0;
		for (int n = 0; n < DataVolume; n++) {
			m_Real = m_FTIn[n] * cos(2 * Pi*fre*n / DataVolume);			// 특정 n에서의 실수값
			m_Image = m_FTIn[n] * sin(2 * Pi*fre*n / DataVolume);			// 특정 n에서의 허수값
			T_Real += m_Real;												// 특정 freq에서 실수 성분 합
			T_Image += m_Image;												// 특정 freq에서 허수 성분 합
		}

		m_FTIn2[fre] = sqrt(T_Real*T_Real + T_Image * T_Image);				// 실수, 허수의 크기를 취함
	}

	for (int fre = 0; fre < DataVolume; fre++) {		// m_FTOut에 저장되는 값은 특정 freq에서 실수&허수 성분 크기
		T_Real = T_Image = 0;
		for (int n = 0; n < DataVolume; n++) {
			m_Real = m_FTTrans[n] * cos(2 * Pi*fre*n / DataVolume);			// 특정 n에서의 실수값
			m_Image = m_FTTrans[n] * sin(2 * Pi*fre*n / DataVolume);			// 특정 n에서의 허수값
			T_Real += m_Real;												// 특정 freq에서 실수 성분 합
			T_Image += m_Image;												// 특정 freq에서 허수 성분 합
		}

		m_FTTrans2[fre] = sqrt(T_Real*T_Real + T_Image * T_Image);				// 실수, 허수의 크기를 취함
	}

	for (int i = 0; i < DataVolume; i++) {		// m_FTOut에 저장되는 값은 특정 freq에서 실수&허수 성분 크기
		m_FTInvers[i] = m_FTIn2[i] * m_FTTrans2[i];
	}

	for (int i = DataVolume / 2; i < DataVolume; i++) {
		m_FTInvers[i] = 0.0;
	}

	Invalidate();
}


void CfourierTransformView::OnInversefourier()
{


	double m_Real, m_Image;
	double T_Real, T_Image;
	for (int t = 0; t < DataVolume; t++) {		// m_FTOut에 저장되는 값은 특정 freq에서 실수&허수 성분 크기
		T_Real = T_Image = 0;
		for (int n = 0; n < DataVolume; n++) {
			m_Real = m_FTInvers[n] * cos(2 * Pi*t*n / DataVolume);			// 특정 n에서의 실수값
			m_Image = m_FTInvers[n] * sin(2 * Pi*t*n / DataVolume);			// 특정 n에서의 허수값
			T_Real += m_Real;												// 특정 freq에서 실수 성분 합
			T_Image += m_Image;												// 특정 freq에서 허수 성분 합
		}

		m_FTOut[t] = sqrt(T_Real*T_Real + T_Image * T_Image);				// 실수, 허수의 크기를 취함
	}

	Invalidate();
}


void CfourierTransformView::OnConvolution()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SignalFunction SF;
	m_ResultVolume = SF.convolution(m_FTIn, DataVolume, m_FTTrans, DataVolume);

	delete m_OutputSig;
	m_OutputSig = NULL;

	m_OutputSig = new double[m_ResultVolume];
	for (int i = 0; i < m_ResultVolume; i++) {
		m_OutputSig[i] = 0.0;
	}

	for (int i = 0; i < m_ResultVolume; i++) {
		m_OutputSig[i] = SF.m_SigResult[i];
	}

	Invalidate();
}