
// ImageProcessingDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ImageProcessingDlg.h"
#include "afxdialogex.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CImageProcessingDlg 對話方塊



CImageProcessingDlg::CImageProcessingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGEPROCESSING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageProcessingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImageProcessingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageProcessingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CImageProcessingDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CImageProcessingDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CImageProcessingDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CImageProcessingDlg 訊息處理常式

BOOL CImageProcessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	/*
	FILE *stream;
	AllocConsole();
	freopen_s( &stream, "1.bmp", "r", stdout);
	*/

	//AllocConsole();



	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CImageProcessingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CImageProcessingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CImageProcessingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int GetBMP4Bytes(int index, char *buffer)
{
	int temp;

	temp = (int)buffer[index + 3];
	temp = (temp << 8) + (int)buffer[index + 2];
	temp = (temp << 8) + (int)buffer[index + 1];
	return temp = (temp << 8) + (int)buffer[index];
}

void CImageProcessingDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	FILE *f;

	fopen_s(&f, "1.bmp", "rb");
	if (!f)
	{
		::MessageBox(NULL, __T("Loading File Failed!"), __T("Error"), MB_OK);
		return;
	}

	//to get byte array
	char *buffer;
	fseek(f, 0, SEEK_END);
	int fileLength = ftell(f);
	rewind(f);

	buffer = (char *)malloc((fileLength + 1) * sizeof(char));
	fread(buffer, fileLength, 1, f);
	fclose(f);

	//to output the img info
	CString width, height, resolution, dpi;
	
	width.Format(_T("%d"), GetBMP4Bytes(18, buffer));
	height.Format(_T("%d"), GetBMP4Bytes(22, buffer));
	resolution.Format(_T("%s x %s"), width, height);
	dpi.Format(_T("%d"), (int)(GetBMP4Bytes(38, buffer) / 39.37));

	GetDlgItem(IDC_EDIT_WIDTH)->SetWindowTextW(width);
	GetDlgItem(IDC_EDIT_HEIGHT)->SetWindowTextW(height);
	GetDlgItem(IDC_EDIT_RESOLUTION)->SetWindowTextW(resolution);
	GetDlgItem(IDC_EDIT_DPI)->SetWindowTextW(dpi);
	

	//to display the img

	//to load the bmp
	Mat img = imread("1.bmp", CV_LOAD_IMAGE_COLOR);
	
	//to check if img is null
	if (!img.data)
	{
	::MessageBox(NULL, __T("Loading Image Failed!"), __T("Error"), MB_OK);
	return;
	}
	
	namedWindow("Display Window", WINDOW_AUTOSIZE);
	imshow("Display Window", img);

	waitKey(0);


	/*
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(L"YO");

	//cv

	
	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, IDB_BITMAP1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (hBitmap == NULL)
	{
		::MessageBox(NULL, __T("LoadImage Failed"), __T("Error"), MB_OK);
		return;
	}

	HDC hLocalDC;
	hLocalDC = ::CreateCompatibleDC(hWinDC);

	if (hLocalDC == NULL)
	{
		::MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
		return;
	}

	BITMAP qBitmap;
	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));

	if (!iReturn)
	{
		::MessageBox(NULL, __T("GetObject Failed"), __T("Error"), MB_OK);
	}

	
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BITMAP1);
	

	
	CDC *pDC = CDC::FromHandle(image.GetDC());

	pDC->Rectangle(0, 40, 100, 50);
	image.
	*/


	
}


void CImageProcessingDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	//to load the bmp
	Mat img0 = imread("1_2.png", CV_LOAD_IMAGE_COLOR);

	//to check if img is null
	if (!img0.data)
	{
		::MessageBox(NULL, __T("Loading Image Failed!"), __T("Error"), MB_OK);
		return;
	}

	namedWindow("Origin", WINDOW_AUTOSIZE);
	imshow("Origin", img0);
	
	int width = img0.cols, height = img0.rows;
	//cout << img0.ptr<Vec3b>(0)[0] << endl;
	
	for (int i = 0; i < height; ++i)
	{
		uchar *data = img0.ptr<uchar>(i);
		for (int j = 0; j < width; ++j)
		{
			int k = j * 3;
			//to get r into temp
			uchar temp = data[k];
			//to put g into 0
			data[k] = data[k + 1];
			//to put b into 1
			data[k + 1] = data[k + 2];
			//to put r into 2
			data[k + 2] = temp;
		}
	}

	namedWindow("Miscellaneous", WINDOW_AUTOSIZE);
	imshow("Miscellaneous", img0);

	waitKey(0);
}

Mat src0, src1;

void CImageProcessingDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

	//to load the bmp
	src0 = src0.empty() ? imread("1.bmp", CV_LOAD_IMAGE_COLOR) : src0;

	//to check if img is null
	if (src0.empty())
	{
		::MessageBox(NULL, __T("Loading Image Failed!"), __T("Error"), MB_OK);
		return;
	}

	namedWindow("Origin", WINDOW_AUTOSIZE);
	imshow("Origin", src0);

	if(src1.empty())
		flip(src0, src1, 1);

	namedWindow("Flip Vertical", WINDOW_AUTOSIZE);
	imshow("Flip Vertical", src1);
}

int sliderValue = 0;
double sliderMax = 100.0;

void OnBarChanged(int sliderValue, void*)
{
	double alpha = (double)sliderValue / sliderMax;
	double beta = 1.0 - alpha;
	Mat dst;

	addWeighted(src0, alpha, src1, beta, 0.0, dst);
	imshow("Blended Image", dst);
}

void CImageProcessingDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here

	//to load the bmp
	src0 = src0.empty() ? imread("1.bmp", CV_LOAD_IMAGE_COLOR) : src0;

	//to check if img is null
	if (src0.empty())
	{
		::MessageBox(NULL, __T("Loading Image Failed!"), __T("Error"), MB_OK);
		return;
	}

	if(src1.empty())
		flip(src0, src1, 1);

	namedWindow("Blended Image", WINDOW_AUTOSIZE);
	createTrackbar("Alpha Bar", "Blended Image", &sliderValue, sliderMax, OnBarChanged);
	OnBarChanged(sliderValue, 0);
}


void CImageProcessingDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here

	//sobel edge detection

}
