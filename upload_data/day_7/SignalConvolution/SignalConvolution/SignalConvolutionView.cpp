
// SignalConvolutionView.cpp: CSignalConvolutionView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SignalConvolution.h"
#endif

#include "SignalConvolutionDoc.h"
#include "SignalConvolutionView.h"
#include "DrawMatrix.h"
#include "GenSignal.h"
#include "DrawSignal.h"
#include "SignalFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSignalConvolutionView

IMPLEMENT_DYNCREATE(CSignalConvolutionView, CView)

BEGIN_MESSAGE_MAP(CSignalConvolutionView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_INPUT_SIG_SIN, &CSignalConvolutionView::OnInputSigSin)
	ON_COMMAND(ID_INPUT_SIG_COS, &CSignalConvolutionView::OnInputSigCos)
	ON_COMMAND(ID_INPUT_SIG_IMPULSE, &CSignalConvolutionView::OnInputSigImpulse)
	ON_COMMAND(ID_TRANS_SIG_SIN, &CSignalConvolutionView::OnTransSigSin)
	ON_COMMAND(ID_TRANS_SIG_COS, &CSignalConvolutionView::OnTransSigCos)
	ON_COMMAND(ID_TRANS_SIG_IMPULSE, &CSignalConvolutionView::OnTransSigImpulse)
	ON_COMMAND(ID_INPUT_SIG_IMPULSE_TRAIN, &CSignalConvolutionView::OnInputSigImpulseTrain)
	ON_COMMAND(ID_TRANS_SIG_IMPULSE_TRAIN, &CSignalConvolutionView::OnTransSigImpulseTrain)
	ON_COMMAND(ID_INPUT_SIG_UNIFORM, &CSignalConvolutionView::OnInputSigUniform)
	ON_COMMAND(ID_TRANS_SIG_UNIFORM, &CSignalConvolutionView::OnTransSigUniform)
	ON_COMMAND(ID_START_CONVOLUTION, &CSignalConvolutionView::OnStartConvolution)
END_MESSAGE_MAP()

// CSignalConvolutionView 생성/소멸

CSignalConvolutionView::CSignalConvolutionView() noexcept : m_ResultVolume(512)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_OutputSig = new double[DataVolume];
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = 0.0;
		m_TransSig[i] = 0.0;
		m_OutputSig[i] = 0.0;
	}
}

CSignalConvolutionView::~CSignalConvolutionView()
{
	delete m_OutputSig;
}

BOOL CSignalConvolutionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSignalConvolutionView 그리기

void CSignalConvolutionView::OnDraw(CDC* pDC)
{
	CSignalConvolutionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawMatrix DM(RectStartX, RectStartY, RectEndX, RectEndY);		// Height = 600
	DM.SetDivide(4, 1);
	DM.StartDraw(pDC);

	CPoint CP;
	DrawSignal DS(DataVolume);
	DrawSignal CONV(m_ResultVolume);

	CP.x = RectStartX;
	CP.y = RectStartY + 150;
	DS.setSignal(m_InputSig);
	DS.drawImpulse(pDC, CP, 255, 0, 0);

	CP.x = RectStartX;
	CP.y = RectStartY + 300;
	DS.setSignal(m_TransSig);
	DS.drawImpulse(pDC, CP, 0, 0, 255);

	CP.x = RectStartX;
	CP.y = RectStartY + 450;
	if (m_OutputSig != NULL) {
		CONV.setSignal(m_OutputSig);
		CONV.drawImpulse(pDC, CP, 255, 0, 255);
	}
	
	CString CHECK_s;
	CHECK_s.Format(_T("%lf"), m_InputSig[0]);

	pDC->TextOut(30, 30, CHECK_s);
}


// CSignalConvolutionView 인쇄

BOOL CSignalConvolutionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSignalConvolutionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSignalConvolutionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSignalConvolutionView 진단

#ifdef _DEBUG
void CSignalConvolutionView::AssertValid() const
{
	CView::AssertValid();
}

void CSignalConvolutionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSignalConvolutionDoc* CSignalConvolutionView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSignalConvolutionDoc)));
	return (CSignalConvolutionDoc*)m_pDocument;
}
#endif //_DEBUG


// CSignalConvolutionView 메시지 처리기

void CSignalConvolutionView::OnInputSigSin()
{
	GenSignal GS(DataVolume);
	GS.setStyle("sin");
	GS.makeSin(4600, 1, 0);		// makeSin(int frequency, int sampling, double phase);
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnTransSigSin()
{
	GenSignal GS(DataVolume);
	GS.setStyle("sin");
	GS.makeSin(4600, 1, 0);
	for (int i = 0; i < DataVolume; i++) {
		m_TransSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnInputSigCos()
{
	GenSignal GS(DataVolume);
	GS.setStyle("cos");
	GS.makeCos(4600, 1, 0);
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnTransSigCos()
{
	GenSignal GS(DataVolume);
	GS.setStyle("cos");
	GS.makeCos(4600, 1, 0);
	for (int i = 0; i < DataVolume; i++) {
		m_TransSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnInputSigImpulse()
{
	GenSignal GS(DataVolume);
	GS.setStyle("impulse");
	GS.makeImpulse();
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnTransSigImpulse()
{
	GenSignal GS(DataVolume);
	GS.setStyle("impulse");
	GS.makeImpulse();
	for (int i = 0; i < DataVolume; i++) {
		m_TransSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnInputSigImpulseTrain()
{
	GenSignal GS(DataVolume);
	GS.setStyle("impulse train");
	GS.makeImpulseTrain(10);
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnTransSigImpulseTrain()
{
	GenSignal GS(DataVolume);
	GS.setStyle("impulse train");
	GS.makeImpulseTrain(10);
	for (int i = 0; i < DataVolume; i++) {
		m_TransSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnInputSigUniform()
{
	GenSignal GS(DataVolume);
	GS.setStyle("uniform");
	GS.makeUniform();
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}
void CSignalConvolutionView::OnTransSigUniform()
{
	GenSignal GS(DataVolume);
	GS.setStyle("uniform");
	GS.makeUniform();
	for (int i = 0; i < DataVolume; i++) {
		m_TransSig[i] = GS.m_SigData[i];
	}

	delete m_OutputSig;
	m_OutputSig = NULL;

	Invalidate();
}

void CSignalConvolutionView::OnStartConvolution()
{
	SignalFunction SF;
	m_ResultVolume = SF.convolution(m_InputSig, DataVolume, m_TransSig, DataVolume);

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
