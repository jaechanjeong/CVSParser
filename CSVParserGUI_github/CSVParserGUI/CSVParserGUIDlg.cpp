
// CSVParserGUIDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CSVParserGUI.h"
#include "CSVParserGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCSVParserGUIDlg 대화 상자



CCSVParserGUIDlg::CCSVParserGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSVPARSERGUI_DIALOG, pParent)
	, m_strDirName(_T(""))
	, m_strDirName2(_T(""))
	, m_cx(0)
	, m_cy(0)
	, m_nDisplayLen(401)
	, m_nDisplayLen1(15)
	, m_nDisplayXaxisStep(10)
	, m_nDisplayXaxisUnit(1)
	, m_strFileName(_T(""))
	, m_dRoiFreqMin(0)
	, m_dRoiFreqMax(0)
	, m_bPrepareAvgData(0)
	, m_bEnableDispDataSetA(TRUE)
	, m_bEnableDispDataSetB(TRUE)
	, m_bEnableDispDataSetC(TRUE)
	, m_bEnableDispDataSetD(FALSE)
	, m_bEnableSaveChart(FALSE)
	, m_strDefaultDir(_T("./RESULT/"))
	, m_dMaxMagnitudeDiff(0)
	, m_dMinMagnitudeDiff(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSVParserGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DIR_NAME, m_strDirName);
	DDX_Text(pDX, IDC_EDIT_DIR_NAME2, m_strDirName2);
	DDX_Control(pDX, IDC_CHART, m_chartView);

	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Control(pDX, IDC_COMBO_FILE_LIST, m_cbFileList);
	DDX_Text(pDX, IDC_EDIT_ROI_FREQ_MIN, m_dRoiFreqMin);
	DDX_Text(pDX, IDC_EDIT_ROI_FREQ_MAX, m_dRoiFreqMax);
	DDX_Control(pDX, IDC_COMBO_FILE_LIST2, m_cbFileList2);
	DDX_Check(pDX, IDC_CHECK_DATA_SET_A, m_bEnableDispDataSetA);
	DDX_Check(pDX, IDC_CHECK_DATA_SET_B, m_bEnableDispDataSetB);
	DDX_Check(pDX, IDC_CHECK_DATA_SET_C, m_bEnableDispDataSetC);
	DDX_Check(pDX, IDC_CHECK_DATA_SET_D, m_bEnableDispDataSetD);

	DDX_Check(pDX, IDC_CHECK_PREPARE_AVERAGE, m_bPrepareAvgData);
	DDX_Control(pDX, IDC_COMBO_WIN_SIZE, m_cbDialogSize);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_cbDeviceType);
	DDX_Control(pDX, IDC_COMBO_CHART_LINE_WIDTH, m_cbChartLineWidth);
}

BEGIN_MESSAGE_MAP(CCSVParserGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCSVParserGUIDlg::OnBnClickedButtonSelectFolder1)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_CONTROL(CVN_ViewPortChanged, IDC_CHART, OnViewPortChanged)
	ON_CONTROL(CVN_MouseMovePlotArea, IDC_CHART, OnMouseMovePlotArea)
	ON_BN_CLICKED(IDC_BUTTON_GET_FILE_LIST, &CCSVParserGUIDlg::OnBnClickedButtonSelectFolder2)
	ON_CBN_SELCHANGE(IDC_COMBO_FILE_LIST, &CCSVParserGUIDlg::OnCbnSelchangeComboFileList)
	ON_BN_CLICKED(IDC_BUTTON_SET_ROI_FREQ, &CCSVParserGUIDlg::OnBnClickedButtonSetRoiFreq)
	ON_CBN_SELCHANGE(IDC_COMBO_FILE_LIST2, &CCSVParserGUIDlg::OnCbnSelchangeComboFileList2)
	ON_STN_CLICKED(IDC_CHART, &CCSVParserGUIDlg::OnStnClickedChart)
	ON_BN_CLICKED(IDC_BUTTON_AVERAGE_SELECT_FOLDER1, &CCSVParserGUIDlg::OnBnClickedButtonAverageSelectFolder1)
	ON_BN_CLICKED(IDC_CHECK_DATA_SET_A, &CCSVParserGUIDlg::OnBnClickedCheckDataSetA)
	ON_BN_CLICKED(IDC_CHECK_DATA_SET_B, &CCSVParserGUIDlg::OnBnClickedCheckDataSetB)
	ON_BN_CLICKED(IDC_CHECK_DATA_SET_C, &CCSVParserGUIDlg::OnBnClickedCheckDataSetC)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_PREPARE_AVERAGE, &CCSVParserGUIDlg::OnBnClickedCheckPrepareAverage)
	ON_BN_CLICKED(IDC_CHECK_DATA_SET_D, &CCSVParserGUIDlg::OnBnClickedCheckDataSetD)
	ON_CBN_SELCHANGE(IDC_COMBO_WIN_SIZE, &CCSVParserGUIDlg::OnCbnSelchangeComboWinSize)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCSVParserGUIDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CCSVParserGUIDlg 메시지 처리기

BOOL CCSVParserGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_labelX = new double [ MAX_TRACE_COUNT];
	m_dataX = new double[MAX_TRACE_COUNT];
	m_dataA = new double[MAX_TRACE_COUNT];
	m_dataA_avg = new double[MAX_TRACE_COUNT];
	m_dataB = new double[MAX_TRACE_COUNT];
	m_dataC = new double[MAX_TRACE_COUNT];


	InitData();

	m_cbDialogSize.AddString(L"Size x 1");
	m_cbDialogSize.AddString(L"Size x 2");
	m_cbDialogSize.AddString(L"Size x 3");
	m_cbDialogSize.SetCurSel(1);

	m_cbDeviceType.AddString(L"Device: R&S");
	m_cbDeviceType.AddString(L"Device: S.H.");
	m_cbDeviceType.SetCurSel(0);

	m_cbChartLineWidth.AddString(L"Chart Line Width : 1");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 2");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 3");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 4");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 5");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 6");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 7");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 8");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 9");
	m_cbChartLineWidth.AddString(L"Chart Line Width : 10");
	m_cbChartLineWidth.SetCurSel(4);


	SetTimer(TIMER_INIT, 100, NULL);
	SetTimer(TIMER_CHART_UPDATE, 30, NULL);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCSVParserGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCSVParserGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCSVParserGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCSVParserGUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case TIMER_CHART_UPDATE:
		if (m_cx == 0 || m_cy == 0)
		{
			;
		}

		m_chartView.updateViewPort(true, false);
		break;
	case TIMER_FILELIST_UPDATE:
		KillTimer(nIDEvent);
		UpdateFileList2();
		break;
	case TIMER_INIT:
		KillTimer(nIDEvent);
		OnCbnSelchangeComboWinSize();
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CCSVParserGUIDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	m_cx = cx;
	m_cy = cy;



	if (m_chartView.GetSafeHwnd() != NULL) 
	{
		CRect rect1;
		m_chartView.GetWindowRect(rect1);
		ScreenToClient(rect1);
#if 0 
		CRect rect2;
		rect2 = rect1;
		rect2.left = rect1.right + 10;
		m_chartView_result.MoveWindow(rect2);

		CRect rect3;
		rect3 = rect1;
		rect3.top = rect1.bottom + 10;
		m_chartView_result2.MoveWindow(rect3);
#endif 

	}
}

void CCSVParserGUIDlg::OnViewPortChanged()
{
	drawChart(&m_chartView);
}

void CCSVParserGUIDlg::OnMouseMovePlotArea()
{
	if (!m_bThread_save)
		trackLineLegend((XYChart *)m_chartView.getChart(), m_chartView.getPlotAreaMouseX());
	m_chartView.updateDisplay();
}

void CCSVParserGUIDlg::InitData()
{
	for (int i = 0; i < MAX_TRACE_COUNT; i++)
	{
		m_dataA[i] = Chart::NoValue;
		m_dataB[i] = Chart::NoValue;
		m_dataC[i] = Chart::NoValue;
		m_dataX[i] = i;
		m_labelX[i] = i;
		m_dataA_avg[i] = 0;
	}
	m_nDisplayLen = 401;
	m_nDisplayLen1 = 15;

}

void CCSVParserGUIDlg::trackLineLegend(XYChart *c, int mouseX)
{
	DrawArea *d = c->initDynamicLayer();
	PlotArea *plotArea = c->getPlotArea();
	double xValue = c->getNearestXValue(mouseX);
	int xCoor = c->getXCoor(xValue);
	d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, d->dashLineColor(0x000000, 0x0101));
	vector<string> legendEntries;
	for (int i = 0; i < c->getLayerCount(); ++i) {
		Layer *layer = c->getLayerByZ(i);
		int xIndex = layer->getXIndexOf(xValue);
		for (int j = 0; j < layer->getDataSetCount(); ++j) {
			DataSet *dataSet = layer->getDataSetByZ(j);
			const char *dataName = dataSet->getDataName();
			int color = dataSet->getDataColor();
			if (dataName && *dataName && (color != Chart::Transparent)) {
				double dataValue = dataSet->getValue(xIndex);
				ostringstream legendEntry;
				legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
					((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
					<< "<*/*>";
				legendEntries.push_back(legendEntry.str());
				int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());
				if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY())) {
					d->circle(xCoor, yCoor, 4, 4, color, color);
				}
			}
		}
	}
	ostringstream legendText;
	legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>["
		<< c->xAxis()->getFormattedLabel(xValue) << "]<*/*>";
	for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
		legendText << "        " << legendEntries[i];
	TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
	t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x000000, Chart::BottomLeft);
	t->destroy();
}



#if 1
void CCSVParserGUIDlg::drawChart(CChartViewer *viewer)
{
	double w = (double)(m_cx - WIDTH_CONTROL_PANEL); // *2 / 3;
	double h = (double)m_cy - 130; // 150; 
	double w1 = w - 100;
	double h1 = h - 100;

	XYChart *c = new XYChart((int)w, (int)h, 0xf4f4f4, 0x000000, 1);
	//c->setRoundedFrame(m_extBgColor);  20200317 memory leaking point 

	c->setPlotArea(55 + 10, 55 - 15, (int)w1, (int)h1, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);
	c->setClipping();

	c->getLegend()->setFontSize(8);

	c->yAxis()->setTitle("Trace(db)", "arialbd.ttf", 10);
	c->xAxis()->setTitle("Frequency(GHz)", "arialbd.ttf", 10);

	c->xAxis()->setWidth(2);
	c->yAxis()->setWidth(2);

#if 1
	double minValue = 0;
	double maxValue = m_dMaxMagnitude[0] > m_dMaxMagnitude[1] ? m_dMaxMagnitude[0] : m_dMaxMagnitude[1];
	if(!m_bPrepareAvgData)
	{
		double dMax=0, dMin=0;

		dMax = maxValue> m_dMaxMagnitudeDiff ? maxValue : m_dMaxMagnitudeDiff;
		dMin = minValue< m_dMinMagnitudeDiff ? minValue : m_dMinMagnitudeDiff;
		c->yAxis()->setLinearScale((double)dMin, (double)dMax);
	}
	else
	{
		if(m_bEnableDispDataSetC)
			c->yAxis()->setLinearScale((double)m_dMinMagnitudeDiff, (double)m_dMaxMagnitudeDiff);
		else
			c->yAxis()->setLinearScale((double)0, (double)maxValue);

		//c->yAxis()->setAutoScale();
	}
#else
	
#endif

	if (1)
	{
		LineLayer *layer = c->addLineLayer();

		layer->setXData(DoubleArray(m_dataX, m_nDisplayLen));
		c->xAxis()->setLabels(DoubleArray(m_labelX, m_nDisplayLen));
		c->xAxis()->setLabelStep((int)m_nDisplayLen / m_nDisplayXaxisStep);

		if (m_bEnableDispDataSetA) layer->addDataSet(DoubleArray(m_dataA, m_nDisplayLen), 0x4033ff33, "Set1"); //c->dashLineColor(0x8033ff33, DotLine)
		if (m_bEnableDispDataSetB) layer->addDataSet(DoubleArray(m_dataB, m_nDisplayLen), 0x403333ff, "Set2"); // c->dashLineColor(0x803333ff, DotLine)
		if (m_bEnableDispDataSetC) layer->addDataSet(DoubleArray(m_dataC, m_nDisplayLen), 0x40cc3333, "Set2-Set1_avg");
		if (m_bEnableDispDataSetD) layer->addDataSet(DoubleArray(m_dataA_avg, m_nDisplayLen), 0x40cc33cc, "Set1 - avg");

		layer->setLineWidth(m_cbChartLineWidth.GetCurSel()+1);


		//c->xAxis()->addMark((double)this->m_cablibPeakIdx, c->dashLineColor(0xff0000, DotLine));
		//c->xAxis()->addMark((double)this->m_dataPeakIdx, 0xff0000);


#if 0 
		//c->yAxis()->addMark(m_dRawSignalMin, 0x0000ff);
		c->xAxis()->addMark(m_nIdxTageretFreqSpanLower, 0x0000ff);

		c->xAxis()->addMark(m_nIdxTageretFreqSpanUpper, 0x0000ff);

		c->xAxis()->addZone(m_nIdxTageretFreqSpanLower, m_nIdxTageretFreqSpanUpper, 0xc03333ff);



		double dTargetFreqX = (double)m_nIdxTageretFreq;
		double dTargetFreqY = m_dataA[m_nIdxTageretFreq];
		c->addScatterLayer(DoubleArray(&dTargetFreqX, 1), DoubleArray(&dTargetFreqY, 1), "ROI Center Freq", Chart::SquareSymbol, 10, 0x80ff3333, 0x80ff3333);
#endif

		if(!m_bThread_save)
		{
			trackLineLegend(c, viewer->isMouseOnPlotArea() ? viewer->getPlotAreaMouseX() :
				c->getPlotArea()->getRightX());
		}
	}



	if (m_bEnableSaveChart)
	{

		printf("m_bEnableSaveChart true\n");
		printf("m_strSaveFilename : %s \n", m_strSaveFilename.GetBuffer());
		m_bEnableSaveChart = FALSE;
		m_strSaveFilename.AppendFormat(".png");

		char buf[1024];
		memset(buf, 0, sizeof(buf) * sizeof(char));
		memcpy(buf, m_strSaveFilename.GetBuffer(), m_strSaveFilename.GetLength());
		c->makeChart(buf);
	}


	delete viewer->getChart();
	viewer->setChart(c);
}
#endif 

#include <math.h>

void CCSVParserGUIDlg::OnBnClickedButtonSelectFolder1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int cnt = 0, cnt2 = 0;

	wchar_t path[256];
	wchar_t file[256];
	CFileDialog dlg(TRUE, _T("csv"), _T("*.csv"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("ini FILE (*.csv)|*.csv|ALL FILE (*.*)|*.*|"));

	GetCurrentDirectory(sizeof(path), path);
	if (dlg.DoModal() == IDOK)
	{
		InitData();


		SetCurrentDirectory(path);
		wcscpy_s(file, dlg.GetPathName());
		//UpdateData(FALSE);

		//CString pathName = dlg.GetPathName();
		
		m_strFileName = dlg.GetFileName();

		m_strDirName = dlg.GetFolderPath();
		
		switch(m_cbDeviceType.GetCurSel())
		{
		case 0 :  // R&S 
			FindFile_ParsingCSV(m_strDirName, 0);
			break; 
		case 1:
			FindFile_ParsingCSV_SignalHound(m_strDirName, 0);
			break;
		default : 
			FindFile_ParsingCSV(m_strDirName, 0);
			break;
		}
		

		//m_bPrepareAvgData = TRUE;
		UpdateData(FALSE);


		UpdateFileList1();

	}
}


void CCSVParserGUIDlg::OnBnClickedButtonSelectFolder2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int cnt = 0, cnt2 = 0;

	wchar_t path[256];
	wchar_t file[256];
	CFileDialog dlg(TRUE, _T("csv"), _T("*.csv"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("ini FILE (*.csv)|*.csv|ALL FILE (*.*)|*.*|"));

	GetCurrentDirectory(sizeof(path), path);
	if (dlg.DoModal() == IDOK)
	{
		SetCurrentDirectory(path);
		wcscpy_s(file, dlg.GetPathName());
		//UpdateData(FALSE);

		//CString pathName = dlg.GetPathName();

		m_strFileName2 = dlg.GetFileName();

		m_strDirName2 = dlg.GetFolderPath();

		switch (m_cbDeviceType.GetCurSel())
		{
		case 0:  // R&S 
			FindFile_ParsingCSV(m_strDirName2, 1);
			break;
		case 1:
			FindFile_ParsingCSV_SignalHound(m_strDirName2, 1);
			break;
		default:
			FindFile_ParsingCSV(m_strDirName2, 1);
			break;
		}

		UpdateData(FALSE);

		UpdateFileList2();

	}

}


void CCSVParserGUIDlg::FindFile_ParsingCSV(CString strDirName, int idxDir)
{
	m_dMaxMagnitude[idxDir] = 0;
	m_ResultFileFind[idxDir].clear();
	
	if(idxDir==0)
		m_cbFileList.ResetContent();
	else
		m_cbFileList2.ResetContent();
	WIN32_FIND_DATA FindFileData;
	CString strPath = strDirName + CString(L"\\*.csv");

	HANDLE hFind = FindFirstFileW(strPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Invalid File Handle. GetLastError reports %d\n", GetLastError());
	}
	else
	{
		while (true)
		{
			std::wcout << FindFileData.cFileName << std::endl;
			ResultFileFind tmp;

			tmp.filename = FindFileData.cFileName;
			tmp.filepath = strDirName;

			if (idxDir == 0)
			{
				m_cbFileList.AddString(tmp.filename);
				m_cbFileList.SetCurSel(m_cbFileList.GetCount() - 1);
			}
			else
			{
				m_cbFileList2.AddString(tmp.filename);
				m_cbFileList2.SetCurSel(m_cbFileList2.GetCount() - 1);
			}

			CStdioFile cf;
			int iret = cf.Open((tmp.filepath + CString(L"\\") + tmp.filename).operator LPCTSTR(), CFile::modeRead);
			if (iret == 0)
			{
				printf("Open Failed:%d__\r\n", GetLastError());
				return;
			}
			int cnt = 0;
			int cnt2 = 0;
			CString sData = _T("");
			while (cf.ReadString(sData))
			{
				if (cnt > 2) // header sz 
				{
					int idx = 0;
					double freq = 0, real = 0, im = 0;
					CString szSub;
					int i = 0;

					while (FALSE != AfxExtractSubString(szSub, sData, i++, ';'))
					{
						_wtof(szSub);
						switch (i)
						{
						case 1: freq = _wtof(szSub); break;
						case 2: real = _wtof(szSub); break;
						case 3: im = _wtof(szSub); break;
						}
					}
					tmp.freq[cnt2] = freq / 1e9;
					tmp.mag[cnt2] = (double)sqrtf(powf((float)real, 2) + powf((float)im, 2));
					tmp.real[cnt2] = real;
					tmp.im[cnt2] = im;

					if (tmp.mag[cnt2] > m_dMaxMagnitude[idxDir])
					{
						m_dMaxMagnitude[idxDir] = tmp.mag[cnt2];
					}
					cnt2++;
				}
				cnt++;
			}
			tmp.len = cnt2;

			printf("length : %d \n", tmp.len);
			m_dRoiFreqMin = tmp.freq[0];
			m_dRoiFreqMax = tmp.freq[cnt2 - 1];
			m_ResultFileFind[idxDir].push_back(tmp);

			if (FindNextFileW(hFind, &FindFileData) == false)
				break;
		}
		FindClose(hFind);
	}
}


void CCSVParserGUIDlg::FindFile_ParsingCSV_SignalHound(CString strDirName, int idxDir)
{
	m_dMaxMagnitude[idxDir] = 0;
	m_ResultFileFind[idxDir].clear();

	if (idxDir == 0)
		m_cbFileList.ResetContent();
	else
		m_cbFileList2.ResetContent();
	WIN32_FIND_DATA FindFileData;
	CString strPath = strDirName + CString(L"\\*.csv");

	HANDLE hFind = FindFirstFileW(strPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Invalid File Handle. GetLastError reports %d\n", GetLastError());
	}
	else
	{
		while (true)
		{
			std::wcout << FindFileData.cFileName << std::endl;
			ResultFileFind tmp;

			tmp.filename = FindFileData.cFileName;
			tmp.filepath = strDirName;

			if (idxDir == 0)
			{
				m_cbFileList.AddString(tmp.filename);
				m_cbFileList.SetCurSel(m_cbFileList.GetCount() - 1);
			}
			else
			{
				m_cbFileList2.AddString(tmp.filename);
				m_cbFileList2.SetCurSel(m_cbFileList2.GetCount() - 1);
			}

			CStdioFile cf;
			int iret = cf.Open((tmp.filepath + CString(L"\\") + tmp.filename).operator LPCTSTR(), CFile::modeRead);
			if (iret == 0)
			{
				printf("Open Failed:%d__\r\n", GetLastError());
				return;
			}
			int cnt = 0;
			int cnt2 = 0;
			CString sData = _T("");
			while (cf.ReadString(sData))
			{
#if 0 
				if (cnt > 2) // header sz 
#else
				//signal hound 는 헤더 부분이 없음 .
#endif 
				{
					int idx = 0;
					double freq = 0, real = 0, im = 0, mag = 0;
					CString szSub;
					int i = 0;

					//while (FALSE != AfxExtractSubString(szSub, sData, i++, ';')) 
					while (FALSE != AfxExtractSubString(szSub, sData, i++, ',')) //Signal hound 구분자가 , 임. 
					{
						_wtof(szSub);
						switch (i)
						{
						case 1: freq = _wtof(szSub); break;
						case 2: mag = abs(_wtof(szSub)); break;
						//case 3: im   = _wtof(szSub); break;
						}
					}
					tmp.freq[cnt2] = freq * 1e6 / 1e9;
					tmp.mag[cnt2] = mag; // (double)sqrtf(powf((float)real, 2) + powf((float)im, 2));
					//tmp.real[cnt2] = real;
					//tmp.im[cnt2] = im;

					if (tmp.mag[cnt2] > m_dMaxMagnitude[idxDir])
					{
						m_dMaxMagnitude[idxDir] = tmp.mag[cnt2];
					}
					cnt2++;
				}
				cnt++;
			}
			tmp.len = cnt2;

			printf("length : %d \n", tmp.len);
			m_dRoiFreqMin = tmp.freq[0];
			m_dRoiFreqMax = tmp.freq[cnt2 - 1];
			m_ResultFileFind[idxDir].push_back(tmp);

			if (FindNextFileW(hFind, &FindFileData) == false)
				break;
		}
		FindClose(hFind);
	}
}


void CCSVParserGUIDlg::UpdateFileList1()
{
	if (m_cbFileList.GetCount() > 0)
	{
		int idx = m_cbFileList.GetCurSel();
		ResultFileFind tmp;

		tmp = m_ResultFileFind[0][idx];

		int cnt = 0;
		int i = 0;

		for (i = 0; i < tmp.len; i++)
		{
			bool bUpdateData = 0;
			if ((m_dRoiFreqMin <= tmp.freq[i]) && (m_dRoiFreqMax >= tmp.freq[i]))
				bUpdateData = 1;

			if (bUpdateData)
			{
				m_labelX[cnt] = tmp.freq[i];
				m_dataA[cnt] = tmp.mag[i];
				cnt++;
			}
		}
		m_nDisplayLen = cnt;
		printf("%s:Length : %d\n", __FUNCTION__, m_nDisplayLen);
	}
}

void CCSVParserGUIDlg::UpdateFileList2()
{
	if (m_cbFileList2.GetCount() > 0)
	{
		int idx = m_cbFileList2.GetCurSel();
		ResultFileFind tmp;

		tmp = m_ResultFileFind[1][idx];

		int cnt = 0;
		int i = 0;

		for (i = 0; i < tmp.len; i++)
		{
			bool bUpdateData = 0;
			if ((m_dRoiFreqMin <= tmp.freq[i]) && (m_dRoiFreqMax >= tmp.freq[i]))
				bUpdateData = 1;

			if (bUpdateData)
			{
				m_labelX[cnt] = tmp.freq[i];
				m_dataB[cnt] = tmp.mag[i];
				if (m_bPrepareAvgData)
				{
					m_dataC[cnt] = m_dataB[cnt] - m_dataA_avg[cnt];
				}
				cnt++;
			}
		}
		m_nDisplayLen = cnt;
		printf("%s:Length : %d\n", __FUNCTION__, m_nDisplayLen);

	}
}
void CCSVParserGUIDlg::OnCbnSelchangeComboFileList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	UpdateFileList1();
}

void CCSVParserGUIDlg::OnCbnSelchangeComboFileList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateFileList2();

}


void CCSVParserGUIDlg::OnBnClickedButtonSetRoiFreq()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	OnCbnSelchangeComboFileList();
	OnCbnSelchangeComboFileList2();

	if (m_bPrepareAvgData)
	{
		OnBnClickedButtonAverageSelectFolder1();
		OnCbnSelchangeComboFileList();
		OnCbnSelchangeComboFileList2();

	}
}




void CCSVParserGUIDlg::OnStnClickedChart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCSVParserGUIDlg::OnBnClickedButtonAverageSelectFolder1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	for (int j = 0; j < m_cbFileList2.GetCount(); j++)
	{
		m_DataSet[j].clear();
	}

	memset(m_dataA_avg, 0, sizeof(double)*MAX_TRACE_COUNT);

	if(m_cbFileList.GetCount() > 0) 
	{

		m_bPrepareAvgData = TRUE;
		for (int j = 0 ; j < m_cbFileList.GetCount() ; j ++)
		{
			int idx = j;
			ResultFileFind tmp;

			tmp = m_ResultFileFind[0][idx];

			int cnt = 0;
			int i = 0;

			for (i = 0; i < tmp.len; i++)
			{
				bool bUpdateData = 0;
				if ((m_dRoiFreqMin <= tmp.freq[i]) && (m_dRoiFreqMax >= tmp.freq[i]))
					bUpdateData = 1;

				if (bUpdateData)
				{
					//m_labelX[cnt] = tmp.freq[i];
					m_dataA_avg[cnt] += tmp.mag[i];
					cnt++;
				}
			}
			m_nDisplayLen = cnt;
		}

		for (int i = 0; i < m_nDisplayLen; i++)
		{
			m_dataA_avg[i] /= m_cbFileList.GetCount();
		}

		for (int j = 0; j < m_cbFileList2.GetCount(); j++)
		{
			//m_DataSet[j].push_back()
			int idx = j;
			ResultFileFind tmp;

			tmp = m_ResultFileFind[1][idx];  //DATA SET _ B (sample)

			int cnt = 0;
			int i = 0;
			for (i = 0; i < tmp.len; i++)
			{
				bool bUpdateData = 0;
				if ((m_dRoiFreqMin <= tmp.freq[i]) && (m_dRoiFreqMax >= tmp.freq[i]))
					bUpdateData = 1;


				if (bUpdateData)
				{
					//m_labelX[cnt] = tmp.freq[i];
					m_DataSet[j].push_back(tmp.mag[i] - m_dataA_avg[cnt]);
					cnt++;
				}
			}
		}

		m_dMinMagnitudeDiff =  9999999999999999999.;
		m_dMaxMagnitudeDiff = -9999999999999999999.;

		double outMax=0, outMin=0;
		for (int j = 0; j < m_cbFileList2.GetCount(); j++)
		{
			MinMaxCheck(m_DataSet[j], outMin, outMax);

			m_dMinMagnitudeDiff = m_dMinMagnitudeDiff > outMin ? outMin : m_dMinMagnitudeDiff;
			m_dMaxMagnitudeDiff = m_dMaxMagnitudeDiff < outMax ? outMax : m_dMaxMagnitudeDiff;
		}
	}

	UpdateData(FALSE);


	SetTimer(TIMER_FILELIST_UPDATE, 30, NULL);

}


void CCSVParserGUIDlg::MinMaxCheck(vector <double> v, double &outMin, double &outMax)
{
	sort(v.begin(), v.end());

	outMin = v[0];

	outMax = v[v.size() - 1];

	//printf("outMax : %2.2f %2.2f \n", v[v.size() - 1], v[v.size()]);
	//v.clear();
}


void CCSVParserGUIDlg::OnBnClickedCheckDataSetA()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void CCSVParserGUIDlg::OnBnClickedCheckDataSetB()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void CCSVParserGUIDlg::OnBnClickedCheckDataSetC()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void CCSVParserGUIDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	delete [] m_labelX ;
	delete [] m_dataX ;
	delete [] m_dataA ;
	delete [] m_dataA_avg ;
	delete [] m_dataB ;
	delete [] m_dataC ;

}


void CCSVParserGUIDlg::OnBnClickedCheckPrepareAverage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void CCSVParserGUIDlg::OnBnClickedCheckDataSetD()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

}


void CCSVParserGUIDlg::OnCbnSelchangeComboWinSize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int x=0 , y=0;
	static bool bInit = 0;

	int flag;
	if (!bInit)
	{
		x = 100;
		y = 100;
		flag = SWP_SHOWWINDOW ;

	}
	else
	{
		flag = SWP_SHOWWINDOW | SWP_NOMOVE;
	}

	

	CRect rect;

	GetClientRect(&rect);

	switch (m_cbDialogSize.GetCurSel())
	{
	case 0:
		//SetWindowPos(NULL, 0, 0, rect.Width() + 10, rect.Height(), SWP_SHOWWINDOW | SWP_NOMOVE);
		SetWindowPos(NULL, x, y, 1024, 768, flag);
		break; 
	case 1:
		//SetWindowPos(NULL, 0, 0, rect.Width() + 10, rect.Height(), SWP_SHOWWINDOW | SWP_NOMOVE);
		SetWindowPos(NULL, x, y, 1280, 720, flag);
		break;
	case 2:
		//SetWindowPos(NULL, 0, 0, rect.Width() + 10, rect.Height(), SWP_SHOWWINDOW | SWP_NOMOVE);
		SetWindowPos(NULL, x, y, 1920, 1080, flag);
		break;

	}

	bInit = 1;

}


void _thread_save(CCSVParserGUIDlg* ptr)
{
	ptr->thread_save();
}


void CCSVParserGUIDlg::SaveResultCSV(int idx, CString strName)
{

	CStdioFile	sFile;
	CString      wstr;
	int ret = 0;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	printf("UTC\n");

	//pDlg->m_pChartMarker->OnBnClickedButtonMeasurementSingle();

	int nSaveLoopCnt = 1;

	printf("%ls%04d-%02d-%02d %02d:%02d:%02d\n", m_strDefaultDir.GetBuffer(), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);

	CreateDirectory(m_strDefaultDir, NULL);

	//for (int idx = 0; idx < nSaveLoopCnt; idx++)

	int ch = 0;
	CString str = m_strDefaultDir;
	//str.Format(_T("c:\\log\\%04d-%02d-%02d %02d:%02d:%02d.csv"), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);
	str.AppendFormat(_T("result_%04d-%02d-%02d_%02d-%02d-%02d_%03d_%s.csv"), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, idx, strName);


	TCHAR buffer[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, buffer);

	CString strDefaultMsg;
	CString strDstLoc;
	strDefaultMsg.Format(_T("File saved on below location.\n\n"));
	strDstLoc.Format(_T("%s"), buffer);
	strDefaultMsg = strDefaultMsg + strDstLoc + str;

	m_strSaveFilename = CStringA(str);

	CStringA strA = CStringA(str);
	printf("strA : %s \n", strA.GetBuffer());
	printf("m_strSaveFilename : %s \n", m_strSaveFilename.GetBuffer());

	
#if 0
	ret = sFile.Open(str, CFile::modeCreate | CFile::modeWrite);

	if (ret = NULL)
	{
		printf("Cannot create file to save experimental results\n");
		return;
	}
#endif

	if (1)
	{
		//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
		ResultFileFind tmp;
		wstr.Empty();
		for (int i = 0; i < m_nDisplayLen; i++)
		{
			wstr.AppendFormat(L"%.4f, %.4f,", m_labelX[i], m_dataC[i]);

			tmp.mag[i] = m_dataC[i];
			tmp.freq[i] = m_labelX[i];
			
			wstr.AppendFormat(L"\n");
		}
		//sFile.WriteString(wstr);
		tmp.filename = strName;
		m_ResultSave.push_back(tmp);

		printf("%s : length %d \n", __FUNCTION__, m_nDisplayLen);
	}

#if 0 
	sFile.Close();
#endif 
}

void CCSVParserGUIDlg::SaveResultCSV_all()
{

	CStdioFile	sFile;
	CString      wstr;
	int ret = 0;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	printf("UTC\n");

	//pDlg->m_pChartMarker->OnBnClickedButtonMeasurementSingle();

	int nSaveLoopCnt = 1;

	printf("%ls%04d-%02d-%02d %02d:%02d:%02d\n", m_strDefaultDir.GetBuffer(), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);

	CreateDirectory(m_strDefaultDir, NULL);

	//for (int idx = 0; idx < nSaveLoopCnt; idx++)

	int ch = 0;
	CString str = m_strDefaultDir;
	//str.Format(_T("c:\\log\\%04d-%02d-%02d %02d:%02d:%02d.csv"), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);
	str.AppendFormat(_T("result_%04d-%02d-%02d_%02d-%02d-%02d_%03d_all.csv"), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);


	TCHAR buffer[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, buffer);

	CString strDefaultMsg;
	CString strDstLoc;
	strDefaultMsg.Format(_T("File saved on below location.\n\n"));
	strDstLoc.Format(_T("%s"), buffer);
	strDefaultMsg = strDefaultMsg + strDstLoc + str;

	m_strSaveFilename = CStringA(str);

	CStringA strA = CStringA(str);
	printf("strA : %s \n", strA.GetBuffer());
	printf("m_strSaveFilename : %s \n", m_strSaveFilename.GetBuffer());

	if (1)
	{
		ret = sFile.Open(str, CFile::modeCreate | CFile::modeWrite);

		if (ret = NULL)
		{
			printf("Cannot create file to save experimental results\n");
			return;
		}

		ResultFileFind tmp1;
		ResultFileFind tmp2;

		printf("%s : legnth : %d \n", __FUNCTION__, m_nDisplayLen);



		tmp1 = m_ResultSave[0];
		wstr.AppendFormat(L"freq, ");
		for (int i = 0; i < m_cbFileList2.GetCount(); i++)
		{
			tmp2 = m_ResultSave[i];
			wstr.AppendFormat(L"%s, ", tmp2.filename);
		}
		wstr.AppendFormat(L"\n");
		sFile.WriteString(wstr);


		wstr.Empty();
		for (int j = 0; j < m_nDisplayLen; j++)
		{
			wstr.AppendFormat(L"%f, ", tmp1.freq[j]);
			for (int i = 0; i < m_cbFileList2.GetCount(); i++)
			{
				tmp2 = m_ResultSave[i];
				wstr.AppendFormat(L"%f, ", tmp2.mag[j]);
			}
			wstr.AppendFormat(L"\n");
			sFile.WriteString(wstr);
			wstr.Empty();

		}
		sFile.Close();

	}

}

void CCSVParserGUIDlg::thread_save(void)
{
	CString str;
	do {
		
		for (int i = 0; i < m_cbFileList2.GetCount(); i++)
		{
			m_cbFileList2.SetCurSel(i);
			UpdateFileList2();
			m_cbFileList2.GetLBText(i, str);
			SaveResultCSV(i, str);
			m_bEnableSaveChart = TRUE;
			Sleep(200);
		}

		SaveResultCSV_all();

		m_bThread_save = FALSE;

		

		GUIControl(TRUE);


		m_bEnableDispDataSetA = TRUE;
		m_bEnableDispDataSetB = TRUE;
		m_bEnableDispDataSetC = TRUE;
		m_bEnableDispDataSetD = FALSE;

		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_A))->SetCheck(m_bEnableDispDataSetA);
		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_B))->SetCheck(m_bEnableDispDataSetB);
		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_C))->SetCheck(m_bEnableDispDataSetC);
		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_D))->SetCheck(m_bEnableDispDataSetD);


	} while (m_bThread_save);
}

void CCSVParserGUIDlg::GUIControl(int enable)
{
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_GET_FILE_LIST)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_AVERAGE_SELECT_FOLDER1)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_SET_ROI_FREQ)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_WIN_SIZE)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(enable);
}

void CCSVParserGUIDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (!m_bThread_save)
	{
		m_ResultSave.clear();

		GUIControl(FALSE);

		m_bEnableDispDataSetA = FALSE;
		m_bEnableDispDataSetB = FALSE;
		m_bEnableDispDataSetC = TRUE;
		m_bEnableDispDataSetD = FALSE;

		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_A))->SetCheck(m_bEnableDispDataSetA);
		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_B))->SetCheck(m_bEnableDispDataSetB);
		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_C))->SetCheck(m_bEnableDispDataSetC);
		((CButton*)GetDlgItem(IDC_CHECK_DATA_SET_D))->SetCheck(m_bEnableDispDataSetD);

		m_bThread_save = TRUE;
		m_pThread_save = AfxBeginThread((AFX_THREADPROC)_thread_save, this);	// start thread

	}
}

/*
	printf("%s %d \n", __FUNCTION__, __LINE__);
	GuiStageControlEnable(0);
	GuiScanControlEnable(FALSE);
	GuiSpectrometerControlEnable(0);


	m_bEnableTimeSerise = FALSE;
	((CButton*)GetDlgItem(IDC_CHECK_TIME_SERISE))->SetCheck(FALSE);

	for (int nIdxResult = 0; nIdxResult < m_nScanModeIteration; nIdxResult++)
	{

		if (m_Result[nIdxResult].size() > 0)
		{
			m_cbSelectScanResult.SetCurSel(nIdxResult);

			int w = (int)m_Result[nIdxResult][0].w;
			int h = (int)m_Result[nIdxResult][0].h;
			double *data_f1 = new double[w*h];
			double *data_f1_2f2 = new double[w*h];
			double *data_harmonics[MAX_HARMONIC_PEAKS];
			double *data_f1_phase = new double[w*h];
			double *data_distance = new double[w*h];

			printf("w x h : %d  %d   \n", w, h);


			if (m_bEnableScanModeCont)
			{
				printf("w : %d ori  \n", w);
				//w = w - round((double)w * 0.01); //  라인 단위로 계산시 매번 width가 변할 수 있음 . 1% 정도 clipping 처리함 .
				//w = w - round((double)w * 0.01); //  len_adc 로 보정하여 문제 없음.
				printf("w : %d modified \n", w);

				for (int i = 0; i < MAX_HARMONIC_PEAKS; i++)
				{
					data_harmonics[i] = new double[w*h];
				}

				for (int i = 0; i < MAX_HARMONIC_PEAKS; i++)
				{
					for (int j = 0; j < w * h; j++)
					{
						data_harmonics[i][j] = -1;
					}
				}
			}

			memset(data_distance, 0, sizeof(double)*(w*h));


			printf("m_Result[nIdxResult].size() : %d \n", (int)m_Result[nIdxResult].size());
			printf("w * h = (%d x %d) = %d \n", w, h, w*h);

			int HF = m_Result[nIdxResult][0].HF;
			int LF = m_Result[nIdxResult][0].LF;

			for (int i = 0; i < m_Result[nIdxResult].size(); i++)
			{
				Result2DScan result = m_Result[nIdxResult][i];

				//printf("idx(%2.2f %2.2f) real(%2.2f %2.2f) f1(%2.2f) f1_2f2(%2.2f)\n", result.x, result.y, result.x_real, result.y_real, result.data_f1, result.data_f1_2f2);

				if (result.x >= w) continue;

				int idx = (int)(result.y * w + result.x); //xxxxxxxxxxx
				int idx_wt_offset = (int)(result.y * w + (result.x + m_nDistanceOffset_x));

				data_f1[idx] = result.data_f1;
				data_f1_2f2[idx] = result.data_f1_2f2;
				data_f1_phase[idx] = result.data_f1_phase;

				if (m_nDistanceOffset_x == 0)
				{
					data_distance[idx_wt_offset] = result.data_distance;

				}
				else
				{
					if ((result.x + m_nDistanceOffset_x) >= 0 && (result.x + m_nDistanceOffset_x) < w)
					{
						data_distance[idx_wt_offset] = result.data_distance;
					}
				}

				data_harmonics[0][idx] = result.data_f1;
				data_harmonics[1][idx] = result.data_f1_1f2;
				data_harmonics[2][idx] = result.data_f1_2f2;
				data_harmonics[3][idx] = result.data_f1_3f2;
				data_harmonics[4][idx] = result.data_f1_4f2;
				data_harmonics[5][idx] = result.data_f1_5f2;

			}

			CStdioFile	sFile;
			CString      wstr;
			int ret = 0;
			SYSTEMTIME systime;
			GetLocalTime(&systime);
			printf("UTC\n");

			//pDlg->m_pChartMarker->OnBnClickedButtonMeasurementSingle();

			int nSaveLoopCnt = 1;

			printf("%ls%04d-%02d-%02d %02d:%02d:%02d\n", m_strDefaultDir.GetBuffer(), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);

			CreateDirectory(m_strDefaultDir, NULL);

			//for (int idx = 0; idx < nSaveLoopCnt; idx++)

			int ch = 0;
			CString str = m_strDefaultDir;
			//str.Format(_T("c:\\log\\%04d-%02d-%02d %02d:%02d:%02d.csv"), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);
			str.AppendFormat(_T("result_%04d-%02d-%02d_%02d-%02d-%02d_(%04d)_HF%d_LF%d.csv"), systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, nIdxResult, HF, LF);


			TCHAR buffer[MAX_PATH];
			::GetCurrentDirectory(MAX_PATH, buffer);

			CString strDefaultMsg;
			CString strDstLoc;
			strDefaultMsg.Format(_T("File saved on below location.\n\n"));
			strDstLoc.Format(_T("%s"), buffer);
			strDefaultMsg = strDefaultMsg + strDstLoc + str;
			if (m_nScanModeIteration == 1)
			{
				AfxMessageBox(strDefaultMsg);
			}

			m_strSaveFilename = CStringA(str);

			CStringA strA = CStringA(str);
			printf("strA : %s \n", strA.GetBuffer());
			printf("m_strSaveFilename : %s \n", m_strSaveFilename.GetBuffer());

			ret = sFile.Open(str, CFile::modeCreate | CFile::modeWrite);

			if (ret = NULL)
			{
				printf("Cannot create file to save experimental results\n");
				return;
			}

			if (!m_bEnableScanModeCont)
			{
				//기존 코드 삭제하지 않기 위해서 조건문으로 처리함.
				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);
				wstr.Format(L"f1, amplitude image \n");
				sFile.WriteString(wstr);
				wstr.Format(L"width, %d, height, %d\n", (int)w, (int)h);
				sFile.WriteString(wstr);
				wstr.Format(L"HF, %d, LF, %d\n", (int)HF, (int)LF);
				sFile.WriteString(wstr);
				wstr.Format(L"Analsys count at  point, %d\n", (int)m_nAnalysisCountAtPoint);
				sFile.WriteString(wstr);
				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);



				//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				wstr.Empty();
				for (int y = 0; y < h; y++)
				{
					for (int x = 0; x < w; x++)
					{
						wstr.AppendFormat(L"%.4f,", data_f1[y*w + x]);
					}
					wstr.AppendFormat(L"\n");
				}
				sFile.WriteString(wstr);

				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);
				wstr.Format(L"f1 + 2f2, amplitude image \n");
				sFile.WriteString(wstr);
				wstr.Format(L"width, %d, height, %d\n", (int)w, (int)h);
				sFile.WriteString(wstr);
				wstr.Format(L"HF, %d, LF, %d\n", (int)HF, (int)LF);
				sFile.WriteString(wstr);
				wstr.Format(L"Analsys count at  point, %d\n", (int)m_nAnalysisCountAtPoint);
				sFile.WriteString(wstr);
				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);


				//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				wstr.Empty();
				for (int y = 0; y < h; y++)
				{
					for (int x = 0; x < w; x++)
					{
						wstr.AppendFormat(L"%.4f,", data_f1_2f2[y*w + x]);
					}
					wstr.AppendFormat(L"\n");
				}
				sFile.WriteString(wstr);

			}
			else
			{
				for (int i = 0; i < MAX_HARMONIC_PEAKS; i++)
				{
					wstr.Format(L"---------------------------------------------------------\n");
					sFile.WriteString(wstr);
					wstr.Format(L"f1+%dxf2, amplitude image \n", i);
					sFile.WriteString(wstr);
					wstr.Format(L"width, %d, height, %d\n", (int)w, (int)h);
					sFile.WriteString(wstr);
					wstr.Format(L"HF, %d, LF, %d\n", (int)HF, (int)LF);
					sFile.WriteString(wstr);
					wstr.Format(L"Analsys count at  point, %d\n", (int)m_nAnalysisCountAtPoint);
					sFile.WriteString(wstr);
					wstr.Format(L"---------------------------------------------------------\n");
					sFile.WriteString(wstr);



					//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
					wstr.Empty();
					for (int y = 0; y < h; y++)
					{
						for (int x = 0; x < w; x++)
						{
							wstr.AppendFormat(L"%.4f,", data_harmonics[i][y*w + x]);
						}
						wstr.AppendFormat(L"\n");
					}
					sFile.WriteString(wstr);
				}
			}


			if (!m_bEnableScanModeCont && m_bEnablePhase)
			{
				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);
				wstr.Format(L"f1 phase image \n");
				sFile.WriteString(wstr);
				wstr.Format(L"width, %d, height, %d\n", (int)w, (int)h);
				sFile.WriteString(wstr);
				wstr.Format(L"HF, %d, LF, %d\n", (int)HF, (int)LF);
				sFile.WriteString(wstr);
				wstr.Format(L"Analsys count at  point, %d\n", (int)m_nAnalysisCountAtPoint);
				sFile.WriteString(wstr);
				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);


				//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				wstr.Empty();
				for (int y = 0; y < h; y++)
				{
					for (int x = 0; x < w; x++)
					{
						wstr.AppendFormat(L"%.4f,", data_f1_phase[y*w + x]);
					}
					wstr.AppendFormat(L"\n");
				}
				sFile.WriteString(wstr);



			}



			if (m_bEnableDistance) //if (!m_bEnableScanModeCont && m_bEnableDistance)
			{
				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);
				wstr.Format(L"Distance image \n");
				sFile.WriteString(wstr);
				wstr.Format(L"width, %d, height, %d\n", (int)w, (int)h);
				sFile.WriteString(wstr);
				wstr.Format(L"HF, %d, LF, %d\n", (int)HF, (int)LF);
				sFile.WriteString(wstr);
				wstr.Format(L"Analsys count at  point, %d\n", (int)m_nAnalysisCountAtPoint);
				sFile.WriteString(wstr);
				wstr.Format(L"---------------------------------------------------------\n");
				sFile.WriteString(wstr);


				//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
				wstr.Empty();
				for (int y = 0; y < h; y++)
				{
					for (int x = 0; x < w; x++)
					{
						wstr.AppendFormat(L"%.4f,", data_distance[y*w + x]);
					}
					wstr.AppendFormat(L"\n");
				}
				sFile.WriteString(wstr);
			}

			sFile.Close();

			m_bEnableSaveChart = TRUE;
			Sleep(200);


			delete[] data_f1;
			delete[] data_f1_2f2;

			if (m_bEnableScanModeCont)
			{
				for (int i = 0; i < MAX_HARMONIC_PEAKS; i++)
				{
					delete[] data_harmonics[i];
				}
			}
		}
	}


	GuiStageControlEnable(TRUE);
	GuiScanControlEnable(TRUE);
	GuiSpectrometerControlEnable(TRUE);
	m_bThread_save = FALSE;
	///xxxxxxx
	printf("%s %d terminated \n", __FUNCTION__, __LINE__);

*/
