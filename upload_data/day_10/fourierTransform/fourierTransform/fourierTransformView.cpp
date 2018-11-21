
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
END_MESSAGE_MAP()

// CfourierTransformView 생성/소멸

CfourierTransformView::CfourierTransformView() noexcept
{
	for (int i = 0; i < DataVolume; i++) {
		m_FTOut[i] = 0.0;
		m_FTIn[i] = 0.0;
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
	DM.SetDivide(4, 1);
	DM.StartDraw(pDC);

	CPoint CP;
	DrawSignal DS(DataVolume);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 150;
	DS.setSignal(m_FTIn, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 255, 0, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 300;
	DS.setSignal(m_FTIn, DataVolume);
	DS.drawImpulse(pDC, CP, SignalStart, 0, 0, 255);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 450;
	DS.setSignal(m_FTOut, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 255);


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
	GenSignal GS(DataVolume), GS1(DataVolume), GS2(DataVolume), GS3(DataVolume), GS4(DataVolume), GS5(DataVolume), GS6(DataVolume);
	GenSignal GSC1(DataVolume), GSC2(DataVolume), GSC3(DataVolume), GSC4(DataVolume), GSC5(DataVolume), GSC6(DataVolume), GSC7(DataVolume);

	int m_Freq = 512, m_Freq1 = 23, m_Freq2 = 40, m_Freq3 = 80, m_Freq4 = 160, m_Freq5 = 220, m_Freq6 = 275;

	GS.setStyle("Sin");
	GS.makeSin(m_Freq, DataVolume, 0);
	//GS1.setStyle("Sin");
	//GS1.makeSin(m_Freq1, DataVolume, 0);
	//GS2.setStyle("Sin");
	//GS2.makeSin(m_Freq2, DataVolume, 0);
	//GS3.setStyle("Sin");
	//GS3.makeSin(m_Freq3, DataVolume, 0);
	//GS4.setStyle("Sin");
	//GS4.makeSin(m_Freq4, DataVolume, 0);
	//GS5.setStyle("Sin");
	//GS5.makeSin(m_Freq5, DataVolume, 0);
	//GS6.setStyle("Sin");
	//GS6.makeSin(m_Freq6, DataVolume, 0);

	//GSC1.setStyle("Cos");
	//GSC1.makeCos(300, DataVolume, 0);
	//GSC2.setStyle("Cos");
	//GSC2.makeCos(400, DataVolume, 0);
	//GSC3.setStyle("Cos");
	//GSC3.makeCos(500, DataVolume, 0);
	//GSC4.setStyle("Cos");
	//GSC4.makeCos(600, DataVolume, 0);
	//GSC5.setStyle("Cos");
	//GSC5.makeCos(700, DataVolume, 0);
	//GSC6.setStyle("Cos");
	//GSC6.makeCos(800, DataVolume, 0);
	//GSC7.setStyle("Cos");
	//GSC7.makeCos(900, DataVolume, 0);

	for (int i = 0; i < DataVolume; i++) {
		m_FTIn[i] = GS.m_SigData[i] + GS1.m_SigData[i] + GS2.m_SigData[i] + GS3.m_SigData[i] + GS4.m_SigData[i] + GS5.m_SigData[i] + GS6.m_SigData[i];
		m_FTIn[i] += GSC1.m_SigData[i] + GSC2.m_SigData[i] + GSC3.m_SigData[i] + GSC4.m_SigData[i] + GSC5.m_SigData[i] + GSC6.m_SigData[i] + GSC7.m_SigData[i];
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
		m_FTOut[fre] = sqrt(T_Real*T_Real + T_Image * T_Image);				// 실수, 허수의 크기를 취함
	}
	Invalidate();
}
