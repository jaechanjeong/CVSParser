
// CSVParserGUIDlg.h: 헤더 파일
//

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "ChartViewer.h"

#pragma comment(lib, "chartdir60.lib")

using namespace std;


#define MAX_DATA_SET_COUNT 10000
#define WIDTH_CONTROL_PANEL 200		
#define MAX_TRACE_COUNT 10000 
enum {
	TIMER_CHART_UPDATE,
	TIMER_INIT,
	TIMER_FILELIST_UPDATE,
};


typedef struct {
	int idx;
	int len;
	CString filename;
	CString filepath;
	double freq[MAX_TRACE_COUNT];
	double real[MAX_TRACE_COUNT];
	double im[MAX_TRACE_COUNT];
	double mag[MAX_TRACE_COUNT];
}ResultFileFind, *pResultFileFind;

// CCSVParserGUIDlg 대화 상자
class CCSVParserGUIDlg : public CDialogEx
{
// 생성입니다.
public:
	CCSVParserGUIDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSVPARSERGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CChartViewer m_chartView;
	int m_extBgColor;
	afx_msg void OnMouseMovePlotArea();
	afx_msg void OnViewPortChanged();
	void drawChart(CChartViewer *viewer);
	void trackLineLegend(XYChart *c, int mouseX);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CString m_strDirName;
	CString m_strDirName2;
	CString m_strFileName;
	CString m_strFileName2;
	CComboBox m_cbFileList;
	CComboBox m_cbFileList2;
	int m_cx;
	int m_cy;
	afx_msg void OnSize(UINT nType, int cx, int cy);


#if 0 
	double m_labelX[MAX_TRACE_COUNT];
	double m_dataX[MAX_TRACE_COUNT];
	double m_dataA[MAX_TRACE_COUNT];
	double m_dataA_avg[MAX_TRACE_COUNT];

	double m_dataB[MAX_TRACE_COUNT];
	double m_dataC[MAX_TRACE_COUNT];
#else
	double *m_labelX;
	double *m_dataX;
	double *m_dataA;
	double *m_dataA_avg;

	double *m_dataB;
	double *m_dataC;


#endif
	int m_nDisplayLen;
	int m_nDisplayLen1;
	int m_nDisplayXaxisStep;
	int m_nDisplayXaxisUnit;

	double m_dMaxMagnitude[2];
	double m_dMinMagnitudeDiff;
	double m_dMaxMagnitudeDiff;
	double m_dRoiFreqMin;
	double m_dRoiFreqMax;

	BOOL m_bPrepareAvgData;

	vector <ResultFileFind> m_ResultFileFind[2];
	vector <ResultFileFind> m_ResultSave;

	vector <double> m_DataSet[MAX_DATA_SET_COUNT];

	void FindFile_ParsingCSV(CString strDirName, int idxDir);
	void FindFile_ParsingCSV_SignalHound(CString strDirName, int idxDir);

	void MinMaxCheck(vector <double> v, double &outMin, double &outMax);
	void CCSVParserGUIDlg::UpdateFileList1();
	void CCSVParserGUIDlg::UpdateFileList2();


	afx_msg void OnBnClickedButtonSelectFolder1();
	afx_msg void OnBnClickedButtonSelectFolder2();
	afx_msg void OnCbnSelchangeComboFileList();
	afx_msg void OnBnClickedButtonSetRoiFreq();
	afx_msg void OnCbnSelchangeComboFileList2();
	afx_msg void OnStnClickedChart();
	afx_msg void OnBnClickedButtonAverageSelectFolder1();
	afx_msg void OnBnClickedCheckDataSetA();
	afx_msg void OnBnClickedCheckDataSetB();
	afx_msg void OnBnClickedCheckDataSetC();
	BOOL m_bEnableDispDataSetA;
	BOOL m_bEnableDispDataSetB;
	BOOL m_bEnableDispDataSetC;
	BOOL m_bEnableDispDataSetD;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCheckPrepareAverage();
	afx_msg void OnBnClickedCheckDataSetD();
	CComboBox m_cbDialogSize;
	afx_msg void OnCbnSelchangeComboWinSize();

	void thread_save(void);
	BOOL			m_bThread_save;
	CWinThread		*m_pThread_save;

	BOOL	m_bEnableSaveChart ;

	afx_msg void OnBnClickedButtonSave();

	CString m_strDefaultDir;
	CStringA m_strSaveFilename;
	void SaveResultCSV(int i, CString strName);
	void SaveResultCSV_all();

	void GUIControl(int enable);
	
	CComboBox m_cbDeviceType;
	CComboBox m_cbChartLineWidth;

	void InitData();
};
