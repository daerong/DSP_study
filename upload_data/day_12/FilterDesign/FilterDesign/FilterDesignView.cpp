
// FilterDesignView.cpp: CFilterDesignView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FilterDesign.h"
#endif

#include "FilterDesignDoc.h"
#include "FilterDesignView.h"

#include "Dialog_Input_Freq.h"
#include "Dialog_Input_Locate.h"
#include "Dialog_Input_Term.h"
#include "Dialog_Input_Shape.h"
#include "Dialog_Input_Gaussian.h"
#include "Dialog_Trans_LPF.h"
#include "Dialog_Trans_Butterworth.h"
#include "Dialog_Trans_Chebyshev.h"

#include "DrawMatrix.h"
#include "DrawSignal.h"
#include "GenSignal.h"
#include "FilterGen.h"
#include "SignalFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFilterDesignView

IMPLEMENT_DYNCREATE(CFilterDesignView, CView)

BEGIN_MESSAGE_MAP(CFilterDesignView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Gen_Sine, &CFilterDesignView::OnGenSine)
	ON_COMMAND(ID_Gen_Cosine, &CFilterDesignView::OnGenCosine)
	ON_COMMAND(ID_Gen_Impulse, &CFilterDesignView::OnGenImpulse)
	ON_COMMAND(ID_Gen_ImpulseTrain, &CFilterDesignView::OnGenImpulsetrain)
	ON_COMMAND(ID_Gen_Triangle, &CFilterDesignView::OnGenTriangle)
	ON_COMMAND(ID_Gen_Rectangle, &CFilterDesignView::OnGenRectangle)
	ON_COMMAND(ID_Gen_Uniform, &CFilterDesignView::OnGenUniform)
	ON_COMMAND(ID_Gen_White, &CFilterDesignView::OnGenWhite)
	ON_COMMAND(ID_INPUT_CLEAR, &CFilterDesignView::OnInputClear)
	ON_COMMAND(ID_Gen_Gaussian, &CFilterDesignView::OnGenGaussian)
	ON_COMMAND(ID_Gen_LPF, &CFilterDesignView::OnGenLpf)
	ON_COMMAND(ID_Gen_Butterworth, &CFilterDesignView::OnGenButterworth)
	ON_COMMAND(ID_Gen_Chebyshev, &CFilterDesignView::OnGenChebyshev)
	ON_COMMAND(ID_CONVOLUTION, &CFilterDesignView::OnConvolution)
END_MESSAGE_MAP()

// CFilterDesignView 생성/소멸

CFilterDesignView::CFilterDesignView() noexcept :
	inputFreq(1),
	inputLocate(0),
	inputTerm(2),
	inputWidth(100),
	filterFreq(1),
	filterDegree(2),
	m_ResultVolume(DataVolume),
	m_ResultStart(SignalStart)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_OutputSig = new double[DataVolume];
	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] = 0.0;
		m_InputFreq[i] = 0.0;
		m_TransSig[i] = 0.0;
		m_TransFreq[i] = 0.0;
		m_OutputSig[i] = 0.0;
		m_OutputFreq[i] = 0.0;
	}
}

CFilterDesignView::~CFilterDesignView()
{
}

BOOL CFilterDesignView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CFilterDesignView 그리기

void CFilterDesignView::OnDraw(CDC* pDC)
{
	CFilterDesignDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawMatrix DM(RectStartX, RectStartY, RectEndX, RectEndY);		// Height = 600
	DM.SetDivide(4, 2);
	DM.StartDraw(pDC);
	DM.SetOutline(RectStartX + RectEndX, RectStartY, RectEndX + RectEndX, RectEndY);
	DM.SetDivide(4, 2);
	DM.StartDraw(pDC);

	CPoint CP;
	DrawSignal DS(DataVolume);
	DrawSignal CONV(m_ResultVolume);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 150;
	DS.setSignal(m_InputSig, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 255, 0, 0);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 300;
	DS.setSignal(m_TransSig, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 255);

	CP.x = OriginX + RectStartX;
	CP.y = RectStartY + 450;
	if (m_OutputSig != NULL) {
		//CONV.setSignal(m_OutputSig, m_ResultVolume);
		CONV.setSignal(m_OutputSig, m_ResultVolume);
		CONV.drawImpulseNormalize(pDC, CP, m_ResultStart, 0, 0, 0);
	}

	CP.x = OriginX + RectStartX + RectEndX;
	CP.y = RectStartY + 150;
	DS.setSignal(m_InputFreq, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 255, 0, 0);

	CP.x = OriginX + RectStartX + RectEndX;
	CP.y = RectStartY + 300;
	DS.setSignal(m_TransFreq, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 255);

	CP.x = OriginX + RectStartX + RectEndX;
	CP.y = RectStartY + 450;
	DS.setSignal(m_OutputFreq, DataVolume);
	DS.drawImpulseNormalize(pDC, CP, SignalStart, 0, 0, 0);
}


// CFilterDesignView 인쇄

BOOL CFilterDesignView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFilterDesignView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFilterDesignView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CFilterDesignView 진단

#ifdef _DEBUG
void CFilterDesignView::AssertValid() const
{
	CView::AssertValid();
}

void CFilterDesignView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFilterDesignDoc* CFilterDesignView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFilterDesignDoc)));
	return (CFilterDesignDoc*)m_pDocument;
}
#endif //_DEBUG


// CFilterDesignView 메시지 처리기


void CFilterDesignView::OnGenSine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Dialog_Input_Freq DIF;

	if (DIF.DoModal() == IDOK) {
		inputFreq = DIF.m_editFreq;

		GenSignal GS(DataVolume);
		GS.makeSin(inputFreq, DataVolume, 0);		// makeSin(int frequency, int sampling, double phase)
	
		for (int i = 0; i < DataVolume; i++) {
			m_InputSig[i] += GS.m_SigData[i];
		}
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnGenCosine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Dialog_Input_Freq DIF;

	if (DIF.DoModal() == IDOK) {
		inputFreq = DIF.m_editFreq;

		GenSignal GS(DataVolume);
		GS.makeCos(inputFreq, DataVolume, 0);		// makeSin(int frequency, int sampling, double phase)
	
		for (int i = 0; i < DataVolume; i++) {
			m_InputSig[i] += GS.m_SigData[i];
		}
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnGenImpulse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Input_Locate DIL;

	if (DIL.DoModal() == IDOK) {
		inputLocate = DIL.m_editLocate;

		GenSignal GS(DataVolume);
		GS.makeImpulse(OriginX + SignalStart + inputLocate);

		for (int i = 0; i < DataVolume; i++) {
			m_InputSig[i] += GS.m_SigData[i];
		}
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnGenImpulsetrain()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Input_Term DIT;

	if (DIT.DoModal() == IDOK) {
		inputTerm = DIT.m_editTerm;

		GenSignal GS(DataVolume);
		GS.makeImpulseTrain(inputTerm);

		for (int i = 0; i < DataVolume; i++) {
			m_InputSig[i] += GS.m_SigData[i];
		}
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnGenTriangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Input_Shape DIS;


	if (DIS.DoModal() == IDOK) {
		inputLocate = DIS.m_editLocate;
		inputWidth = DIS.m_editWidth;

		GenSignal GS(DataVolume);
		GS.makeTriangular(OriginX + SignalStart + inputLocate, inputWidth);

		for (int i = 0; i < DataVolume; i++) {
			m_InputSig[i] += GS.m_SigData[i];
		}
	}

	InputFourier();

	Invalidate();

}


void CFilterDesignView::OnGenRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Input_Shape DIS;


	if (DIS.DoModal() == IDOK) {
		inputLocate = DIS.m_editLocate;
		inputWidth = DIS.m_editWidth;

		GenSignal GS(DataVolume);
		GS.makeRectangle(OriginX + SignalStart + inputLocate, inputWidth);

		for (int i = 0; i < DataVolume; i++) {
			m_InputSig[i] += GS.m_SigData[i];
		}
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnGenUniform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	GenSignal GS(DataVolume);
	GS.makeUniform();

	for (int i = 0; i < DataVolume; i++) {
		m_InputSig[i] += GS.m_SigData[i];
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnGenWhite()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	int RandNo;
	for (int n = 0; n < DataVolume; n++)
	{
		RandNo = rand() % 100 - 50; //0-99까지 Randon 숫자 발생 -> -50~-50까지로 변경
		m_WhiteNoise[n] = double(RandNo) / 50; //+1 ~ -1로 조정
	}
	for (int n = 0; n < DataVolume; n++)
	{
		m_InputSig[n] += m_WhiteNoise[n] / 10;
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnInputClear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for (int n = 0; n < DataVolume; n++) {
		m_InputSig[n] = 0.0;
	}

	for (int n = 0; n < DataVolume; n++)
	{
		m_InputFreq[n] = 0.0;
	}

	Invalidate();
}


void CFilterDesignView::InputFourier()
{
	// TODO: 여기에 구현 코드 추가.

	SignalFunction SF(DataVolume);
	SF.fourierTranseform(m_InputSig, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_InputFreq[n] = SF.m_SigResult[n];
	}
}

void CFilterDesignView::TransFourier()
{
	// TODO: 여기에 구현 코드 추가.

	SignalFunction SF(DataVolume);
	SF.fourierTranseform(m_TransFreq, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_TransSig[n] = SF.m_SigResult[n];
	}
}

void CFilterDesignView::OnGenGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Input_Gaussian DIG;

	if (DIG.DoModal() == IDOK) {
		inputLocate = DIG.m_editMean;
		inputWidth = DIG.m_editSigma;

		GenSignal GS(DataVolume);
		GS.makeGaussian(OriginX + SignalStart + inputLocate, inputWidth);

		for (int i = 0; i < DataVolume; i++) {
			m_InputSig[i] += GS.m_SigData[i];
		}
	}

	InputFourier();

	Invalidate();
}


void CFilterDesignView::OnGenLpf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Trans_LPF DTL;

	if (DTL.DoModal() == IDOK) {
		filterFreq = DTL.m_editFreq;

		FilterGen FG(DataVolume);
		FG.makeLPF(filterFreq, OriginX + SignalStart);

		for (int i = 0; i < DataVolume; i++) {
			m_TransFreq[i] = FG.m_FreqData[i];
		}
	}

	TransFourier();

	Invalidate();
}


void CFilterDesignView::OnGenButterworth()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Trans_Butterworth DTB;

	if (DTB.DoModal() == IDOK) {
		filterFreq = DTB.m_editFreq;
		filterDegree = DTB.m_editDegree;

		FilterGen FG(DataVolume);
		FG.makeButterworth(filterFreq, filterDegree, OriginX + SignalStart);

		for (int i = 0; i < DataVolume; i++) {
			m_TransFreq[i] = FG.m_FreqData[i];
		}
	}

	TransFourier();

	Invalidate();
}


void CFilterDesignView::OnGenChebyshev()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Dialog_Trans_Chebyshev DTC;


	if (DTC.DoModal() == IDOK) {
		filterFreq = DTC.m_editFreq;
		filterDegree = DTC.m_editDegree;

		FilterGen FG(DataVolume);
		FG.makeChebyshev(filterFreq, filterDegree, OriginX + SignalStart);

		for (int i = 0; i < DataVolume; i++) {
			m_TransFreq[i] = FG.m_FreqData[i];
		}
	}

	TransFourier();

	Invalidate();
}


void CFilterDesignView::OnConvolution()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SignalFunction SF;
	m_ResultVolume = SF.convolution(m_InputSig, DataVolume, SignalStart, 
		m_TransSig, DataVolume, SignalStart, &m_ResultStart);

	delete m_OutputSig;
	m_OutputSig = NULL;

	m_OutputSig = new double[m_ResultVolume];
	for (int i = 0; i < m_ResultVolume; i++) {
		m_OutputSig[i] = SF.m_SigResult[i];
	}

	SF.setVolume(DataVolume);
	SF.fourierTranseform(m_OutputSig, DataVolume);

	for (int n = 0; n < DataVolume; n++) {
		m_OutputFreq[n] = SF.m_SigResult[n];
	}

	Invalidate();
}
