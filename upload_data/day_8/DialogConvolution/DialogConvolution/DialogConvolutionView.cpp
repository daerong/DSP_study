
// DialogConvolutionView.cpp: CDialogConvolutionView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DialogConvolution.h"
#endif

#include "DialogConvolutionDoc.h"
#include "DialogConvolutionView.h"

#include "DrawMatrix.h"
#include "GenSignal.h"
#include "DrawSignal.h"
#include "SignalFunction.h"
#include "CDialogSignal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDialogConvolutionView

IMPLEMENT_DYNCREATE(CDialogConvolutionView, CView)

BEGIN_MESSAGE_MAP(CDialogConvolutionView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SigGen, &CDialogConvolutionView::OnSiggen)
	ON_COMMAND(ID_SigDraw, &CDialogConvolutionView::OnSigdraw)
	ON_COMMAND(ID_Convolution, &CDialogConvolutionView::OnConvolution)
END_MESSAGE_MAP()

// CDialogConvolutionView 생성/소멸

CDialogConvolutionView::CDialogConvolutionView() noexcept : 
	m_SigType1("Impulse Train"), 
	m_SigType2("Uniform"), 
	m_SigFreq1(1), 
	m_SigFreq2(1), 
	m_SigVol1(DataVolume), 
	m_SigVol2(DataVolume), 
	m_ResultVolume(DataVolume), 
	m_ResultStart(SignalStart),
	m_SigLoc1(0),
	m_SigLoc2(0),
	m_SigWidth1(100),
	m_SigWidth2(100)
{
	m_OutputSig = new double[DataVolume];
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = 0.0;
		m_TransSig[i] = 0.0;
		m_OutputSig[i] = 0.0;
	}

}

CDialogConvolutionView::~CDialogConvolutionView()
{
}

BOOL CDialogConvolutionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDialogConvolutionView 그리기

void CDialogConvolutionView::OnDraw(CDC* pDC)
{
	CDialogConvolutionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawMatrix DM(RectStartX, RectStartY, RectEndX, RectEndY);		// Height = 600
	DM.SetDivide(4, 2);
	DM.StartDraw(pDC);

	CPoint CP;
	DrawSignal DS(DataVolume);
	DrawSignal CONV(m_ResultVolume);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 150;
	DS.setSignal(m_InputSig, DataVolume);
	DS.drawImpulse(pDC, CP, SignalStart, 255, 0, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 300;
	DS.setSignal(m_TransSig, DataVolume);
	DS.drawImpulse(pDC, CP, SignalStart, 0, 0, 255);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 450;
	if (m_OutputSig != NULL) {
		CONV.setSignal(m_OutputSig, m_ResultVolume);
		CONV.drawImpulse(pDC, CP, m_ResultStart, 255, 0, 255);
	}

}


// CDialogConvolutionView 인쇄

BOOL CDialogConvolutionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDialogConvolutionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDialogConvolutionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDialogConvolutionView 진단

#ifdef _DEBUG
void CDialogConvolutionView::AssertValid() const
{
	CView::AssertValid();
}

void CDialogConvolutionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDialogConvolutionDoc* CDialogConvolutionView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDialogConvolutionDoc)));
	return (CDialogConvolutionDoc*)m_pDocument;
}
#endif //_DEBUG


// CDialogConvolutionView 메시지 처리기


void CDialogConvolutionView::OnSiggen()
{
	CDialogSignal dlg;

	dlg.m_SigType1 = m_SigType1;	// 첫번째 신호 타입 Dialog로 전달 
	dlg.m_SigType2 = m_SigType2;	// 두번째 신호 타입 Dialog로 전달 
	dlg.m_SigFreq1 = m_SigFreq1;	// 첫번째 신호 주파수 Dialog로 전달 
	dlg.m_SigFreq2 = m_SigFreq2;	// 두번째 신호 주파수 Dialog로 전달 
	dlg.m_SigVol1 = m_SigVol1;		// 첫번째 신호 데이터 갯수 Dialog로 전달 
	dlg.m_SigVol2 = m_SigVol2;		// 두번째 신호 데이터 갯수 Dialog로 전달 
	dlg.m_SigLoc1 = m_SigLoc1;
	dlg.m_SigLoc2 = m_SigLoc2;
	dlg.m_SigWidth1 = m_SigWidth1;
	dlg.m_SigWidth2 = m_SigWidth2;


	if (dlg.DoModal() == IDOK) {
		m_SigType1 = dlg.m_SigType1;	// Dialog에서 선택한 첫번째 신호 타입 가져오기
		m_SigType2 = dlg.m_SigType2;	// Dialog에서 선택한 두번째 신호 타입 가져오기
		m_SigFreq1 = dlg.m_SigFreq1;	// Dialog에서 선택한 첫번째 주파수 가져오기
		m_SigFreq2 = dlg.m_SigFreq2;	// Dialog에서 선택한 두번째 주파수 가져오기
		m_SigVol1 = dlg.m_SigVol1;		// Dialog에서 선택한 첫번째 데이터 갯수 가져오기
		m_SigVol2 = dlg.m_SigVol2;		// Dialog에서 선택한 첫번째 데이터 갯수 가져오기
		m_SigLoc1 = dlg.m_SigLoc1;
		m_SigLoc2 = dlg.m_SigLoc2;
		m_SigWidth1 = dlg.m_SigWidth1;
		m_SigWidth2 = dlg.m_SigWidth2;
	}
}


void CDialogConvolutionView::OnSigdraw()
{
	GenSignal GS1(DataVolume), GS2(DataVolume);

	GS1.setStyle(m_SigType1);

	if (m_SigType1 == "Sin") {
		GS1.makeSin(m_SigFreq1, m_SigVol1, 0);		// makeSin(int frequency, int sampling, double phase);
	}
	else if (m_SigType1 == "Cos") {
		GS1.makeCos(m_SigFreq1, m_SigVol1, 0);		// makeSin(int frequency, int sampling, double phase);
	}
	else if (m_SigType1 == "Impulse") {
		GS1.makeImpulse(OriginX + SignalStart + m_SigLoc1);
	}
	else if (m_SigType1 == "Impulse Train") {
		GS1.makeImpulseTrain(64);
	}
	else if (m_SigType1 == "Uniform") {
		GS1.makeUniform();
	}
	else if (m_SigType1 == "Triangular") {
		GS1.makeTriangular(OriginX + SignalStart + m_SigLoc1, m_SigWidth1);
	}
	else if (m_SigType1 == "Rectangle") {
		GS1.makeRectangle(OriginX + SignalStart + m_SigLoc1, m_SigWidth1);
	}


	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = GS1.m_SigData[i];
	}

	GS2.setStyle(m_SigType2);

	if (m_SigType2 == "Sin") {
		GS2.makeSin(m_SigFreq2, m_SigVol2, 0);		// makeSin(int frequency, int sampling, double phase);
	}
	else if (m_SigType2 == "Cos") {
		GS2.makeCos(m_SigFreq2, m_SigVol2, 0);		// makeSin(int frequency, int sampling, double phase);
	}
	else if (m_SigType2 == "Impulse") {
		GS2.makeImpulse(OriginX + SignalStart + m_SigLoc2);
	}
	else if (m_SigType2 == "Impulse Train") {
		GS2.makeImpulseTrain(64);
	}
	else if (m_SigType2 == "Uniform") {
		GS2.makeUniform();
	}
	else if (m_SigType2 == "Triangular") {
		GS2.makeTriangular(OriginX + SignalStart + m_SigLoc2, m_SigWidth2);
	}
	else if (m_SigType2 == "Rectangle") {
		GS2.makeRectangle(OriginX + SignalStart + m_SigLoc2, m_SigWidth2);
	}

	for (int i = 0; i < DataVolume; i++) {
		m_TransSig[i] = GS2.m_SigData[i];
	}
	Invalidate();
}


void CDialogConvolutionView::OnConvolution()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SignalFunction SF;
	m_ResultVolume = SF.convolution(m_InputSig, DataVolume, SignalStart, m_TransSig, DataVolume, SignalStart, &m_ResultStart);

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
