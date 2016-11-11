
// ImageProcessingDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ImageProcessingDlg.h"
#include "afxdialogex.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>

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
	ON_BN_CLICKED(IDC_BUTTON5, &CImageProcessingDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CImageProcessingDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CImageProcessingDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CImageProcessingDlg::OnBnClickedButton8)
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
	
	imshow("Display Window", img);

	waitKey(0);
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

	imshow("Original Image", img0);
	
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

	imshow("Miscellaneous Image", img0);

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

	imshow("Original Image", src0);

	if(src1.empty())
		flip(src0, src1, 1);

	imshow("Flip Vertical Image", src1);
}

int sliderValue0 = 0;
double sliderMax = 100.0;

void OnBlendedBarChanged(int sliderValue, void*)
{
	double alpha = (double)sliderValue / sliderMax;
	double beta = 1.0 - alpha;
	Mat dst;

	//addWeighted(src0, src0 alpha, src1, src1 alpha, addtion value, output)
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
	createTrackbar("Alpha Bar", "Blended Image", &sliderValue0, sliderMax, OnBlendedBarChanged);
	OnBlendedBarChanged(sliderValue0, 0);
}

int colorMax = 255;
int angleMax = 180;
int sliderValue1 = 0;
Mat src2, gradX, gradY;
void OnThresholdBarChanged(int sliderValue, void*)
{
	Mat dst;

	//threshold(input, output, threshold, max, type)
	threshold(src2, dst, sliderValue, 255, THRESH_TOZERO);
	
	imshow("Sobel2 Image", dst);
}

double pi = atan(1) * 4;
void OnAngleBarChanged(int sliderValue, void*)
{
	int width = src2.cols, height = src2.rows;
	Mat dst(height, width, CV_8U);

	for (int i = 0; i < height; ++i)
	{
		short *dataX = gradX.ptr<short>(i), *dataY = gradY.ptr<short>(i);
		uchar *dataD = dst.ptr<uchar>(i), *dataSrc2 = src2.ptr<uchar>(i);
		for (int j = 0; j < width; ++j)
		{
			double d = atan2(dataY[j], dataX[j]) * 180 / pi - sliderValue;
			dataD[j] = (d < 20 && d >= -20) ? (uchar)dataSrc2[j] : (uchar)0;
		}
	}
	

	imshow("Sobel Image", dst);
}

void CImageProcessingDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here

	//sobel edge detection

	Mat img = imread("eye.jpg", CV_LOAD_IMAGE_COLOR);

	if (img.empty())
	{
		::MessageBox(NULL, __T("Loading Image Failed!"), __T("Error"), MB_OK);
		return;
	}

	imshow("Original Image", img);

	//to be converted to gray level
	cvtColor(img, img, CV_RGB2GRAY);
	//to do gaussian blur
	GaussianBlur(img, img, Size(3, 3), 0, 0);

	imshow("Smooth Image", img);

	Mat absGradX, absGradY;

	//Sobel(input, output, depth, dx, dy, filter size, scale, delta
	Sobel(img, gradX, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	//calculation => to get abs => converted to CV_8U
	//convertScaleAbs(input, output, multiplication factor, addtion factor)
	convertScaleAbs(gradX, absGradX);

	Sobel(img, gradY, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(gradY, absGradY);

	addWeighted(absGradX, 0.5, absGradY, 0.5, 0, src2);
	
	namedWindow("Sobel Image");
	createTrackbar("Angle Bar", "Sobel Image", &sliderValue0, angleMax, OnAngleBarChanged);
	OnAngleBarChanged(sliderValue0, 0);

	namedWindow("Sobel2 Image");
	createTrackbar("Threshold Bar", "Sobel2 Image", &sliderValue1, colorMax, OnThresholdBarChanged);
	OnThresholdBarChanged(sliderValue1, 0);
}

Point2f inputPoints[4];
Mat src3;
int pointCount = 0;
void OnMouse(int event, int x, int y, int flags, void* param)
{
	if (event == (int)EVENT_FLAG_LBUTTON)
	{
		inputPoints[pointCount] = Point2f(x, y);
		if (++pointCount >= 4)
		{
			//to end
			Point2f afterPoints[4];
			afterPoints[0] = Point2f(20, 20);
			afterPoints[1] = Point2f(20, 450);
			afterPoints[2] = Point2f(450, 450);
			afterPoints[3] = Point2f(450, 20);

			Mat perspectiveTransform = getPerspectiveTransform(inputPoints, afterPoints), img;
			
			warpPerspective(src3, img, perspectiveTransform, img.size());

			imshow("New Qrcode", img);
			pointCount = 0;
		}
	}
}

void CImageProcessingDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler concode here
	src3 = imread("QR.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Original Qrcode", WINDOW_AUTOSIZE);
	setMouseCallback("Original Qrcode", OnMouse, NULL);
	imshow("Original Qrcode", src3);
}

void OnMouseByMyself(int event, int x, int y, int flags, void* param)
{
	if (event == (int)EVENT_FLAG_LBUTTON)
	{
		inputPoints[pointCount] = Point2f(x, y);
		if (++pointCount >= 4)
		{
			//to end
			Point2f afterPoints[4];
			afterPoints[0] = Point2f(20, 20);
			afterPoints[1] = Point2f(20, 450);
			afterPoints[2] = Point2f(450, 450);
			afterPoints[3] = Point2f(450, 20);

			/*
			Mat A(8, 8, CV_32F), b(8, 1, CV_32F), x(8, 1, CV_32F);

			int i;
			for (i = 0; i < 4; ++i)
			{
				float *dataA =A.ptr<float>(i), *dataB = b.ptr<float>(i);
				dataA[0] = inputPoints[i].x;
				dataA[1] = inputPoints[i].y;
				dataA[2] = 1;
				dataA[3] = 0;
				dataA[4] = 0;
				dataA[5] = 0;
				dataA[6] = -(inputPoints[i].x * afterPoints[i].x);
				dataA[7] = -(inputPoints[i].y * afterPoints[i].x);
				dataB[0] = afterPoints[i].x;
			}

			for (i = 0; i < 4; ++i)
			{
				float *dataA = A.ptr<float>(i + 4), *dataB = b.ptr<float>(i + 4);
				dataA[0] = 0;
				dataA[1] = 0;
				dataA[2] = 0;
				dataA[3] = inputPoints[i].x;
				dataA[4] = inputPoints[i].y;
				dataA[5] = 1;
				dataA[6] = -(inputPoints[i].x * afterPoints[i].y);
				dataA[7] = -(inputPoints[i].y * afterPoints[i].y);
				dataB[0] = inputPoints[i].y;
			}

			solve(A, b, x, CV_LU);
			::MessageBox(NULL, __T("YO"), __T("Error"), MB_OK);

			Mat perspectiveTransform(3, 3, CV_32F);
			for (int i = 0; i < 2; ++i)
			{
				//float *dataP = perspectiveTransform.ptr<float>(i);
				for (int j = 0; j < 3; ++j)
				{
					//float *dataX = x.ptr<float>(i * 3 + j);
					//dataP[j] = dataX[0];
					perspectiveTransform.at<float>(i, j) = x.at<float>(i * 3 + j, 0);
				}
			}
			perspectiveTransform.at<float>(2, 0) = x.at<float>(6, 0);
			perspectiveTransform.at<float>(2, 1) = x.at<float>(7, 0);
			perspectiveTransform.at<float>(2, 2) = 1;
			*/

			Mat perspectiveTransform = getPerspectiveTransform(afterPoints, inputPoints);

			int height = src3.rows, width = src3.cols, channel = src3.channels();
			Mat img(height, width, src3.type());

			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					Mat x(3, 1, CV_64F), r(3, 1, CV_64F);
					x.at<double>(0, 0) = j;
					x.at<double>(1, 0) = i;
					x.at<double>(2, 0) = 1;

					r = perspectiveTransform * x;

					double x0 = r.at<double>(0, 0) / r.at<double>(2, 0);
					double y0 = r.at<double>(1, 0) / r.at<double>(2, 0);

					//to get upper x0 y0 and lower x0 y0
					int x0Up = ceil(x0);
					int y0Up = ceil(y0);
					int x0Down = floor(x0);
					int y0Down = floor(y0);

					uchar *dataI = img.ptr<uchar>(i);
					if (x0Up >= 0 && x0Down >= 0 && x0Up < height && x0Down < height && y0Up >= 0 && y0Down >= 0 && y0Up < width && y0Down < width)
					{
						uchar *dataSUp = src3.ptr<uchar>(y0Up), *dataSDown = src3.ptr<uchar>(y0Down);
						for (int k = 0; k < 3; ++k)
							dataI[j * 3 + k] = (dataSUp[x0Up * 3 + k] + dataSDown[x0Down * 3 + k]) / 2;
					}
					else
					{
						for (int k = 0; k < 3; ++k)
							dataI[j * 3 + k] = 0;
					}


					/*
					if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
						for (int k = 0; k < 3; ++k)
							img.at<uchar>(y0, x0 * 3 + k) = src3.at<uchar>(i, j * 3 + k);
					*/
					//::MessageBox(NULL, __T("YO3"), __T("Error"), MB_OK);
				}
			}

			imshow("New Qrcode", img);
			pointCount = 0;
		}
	}
}

void CImageProcessingDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here

	//type: CV_8UC3
	src3 = imread("QR.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Original Qrcode", WINDOW_AUTOSIZE);
	setMouseCallback("Original Qrcode", OnMouseByMyself, NULL);
	imshow("Original Qrcode", src3);
}


void CImageProcessingDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	Mat img = imread("shoes.jpg", CV_LOAD_IMAGE_GRAYSCALE), rImg, gImg, lImg;

	resize(img, rImg, Size(img.cols / 3, img.rows / 3));

	threshold(rImg, gImg, 0, 255, THRESH_TOZERO | THRESH_OTSU);

	imshow("Resize Image", rImg);

	namedWindow("Global Threshold Image", WINDOW_AUTOSIZE);
	imshow("Global Threshold Image", gImg);

	adaptiveThreshold(rImg, lImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 133, -40);
	imshow("Local Threshold Image", lImg);

	GaussianBlur(lImg, lImg, Size(3, 3), 0, 0);
	imshow("Gaussian Smooth Image", lImg);

	medianBlur(lImg, lImg, 5);
	imshow("Median Filter Image", lImg);
}
