
// OpenCvMFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "OpenCvMFC.h"
#include "OpenCvMFCDlg.h"
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


// COpenCvMFCDlg 대화 상자



COpenCvMFCDlg::COpenCvMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCVMFC_DIALOG, pParent)
	, m_Value(_T(""))
	, m_value2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCvMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Value, m_Value);
	DDX_Text(pDX, IDC_Value2, m_value2);
}

BEGIN_MESSAGE_MAP(COpenCvMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &COpenCvMFCDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Lenna, &COpenCvMFCDlg::OnBnClickedLenna)
	ON_BN_CLICKED(IDC_Change_Btn, &COpenCvMFCDlg::OnBnClickedChangeBtn)
	ON_BN_CLICKED(IDC_Resize_Btn, &COpenCvMFCDlg::OnBnClickedResizeBtn)
	ON_BN_CLICKED(IDC_Rotate_Btn, &COpenCvMFCDlg::OnBnClickedRotateBtn)
	ON_BN_CLICKED(IDC_Rotate_Btn2, &COpenCvMFCDlg::OnBnClickedRotateBtn2)
END_MESSAGE_MAP()


// COpenCvMFCDlg 메시지 처리기

BOOL COpenCvMFCDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COpenCvMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COpenCvMFCDlg::OnPaint()
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
HCURSOR COpenCvMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenCvMFCDlg::OnBnClickedOk()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();

		CT2CA pszString(path);
		std::string strPath(pszString);

		m_matImage = imread(strPath, IMREAD_UNCHANGED);

		CreateBitmapInfo(m_matImage.cols, m_matImage.rows, m_matImage.channels() * 8);

		DrawImage();
	}
}

void COpenCvMFCDlg::CreateBitmapInfo(int w, int h, int bpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
}
void COpenCvMFCDlg::DrawImage()
{
	CClientDC dc(GetDlgItem(IDC_PIC));

	CRect rect;
	GetDlgItem(IDC_PIC)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void COpenCvMFCDlg::OnBnClickedLenna()
{
	imshow("레나다", m_matImage2);
	waitKey(0);
}


void COpenCvMFCDlg::OnBnClickedChangeBtn()
{
	int data = GetDlgItemInt(IDC_Value);

	imshow("흑백레나다", m_grayImage + data);
}


void COpenCvMFCDlg::OnBnClickedResizeBtn()
{
	Mat resize_img;	
	int data = GetDlgItemInt(IDC_Value);
		if (data == 0)
	{
		MessageBox(_T("크기 변환 시 0이나 공백은 입력하면 안됩니다."), _T("Title"), MB_ICONERROR);
		data += 1;
	}

	resize(m_matImage2, resize_img, Size(data,data));

	imshow("크기조정 레나", resize_img);
}


void COpenCvMFCDlg::OnBnClickedRotateBtn()
{
	int data = GetDlgItemInt(IDC_Value);

	Mat rt(m_matImage2.rows, m_matImage2.rows, CV_8U);

	Point2f pc(m_matImage2.cols / 2.0, m_matImage2.rows / 2.0);

	Mat r = getRotationMatrix2D(pc, data, 1);

	warpAffine(m_matImage2, rt, r, rt.size());
	imshow("회전 레나", rt);
}

Mat rotate(Mat src, double angle)
{
	Mat dst;
	Point2f pt(src.cols / 2.0, src.rows / 2.0);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(src.cols, src.rows));
	return dst;
}


void COpenCvMFCDlg::OnBnClickedRotateBtn2()
{
	Mat img = imread("suhwa.png");
	int o = 0;
	int one = 1;
	int n = GetDlgItemInt(IDC_Value);  //픽셀 사이즈 
	int rot = GetDlgItemInt(IDC_Value2); //각도
	int p = (512 / n) * n;
	Mat output = img(Rect(0, 0, img.cols, img.rows)).clone();
	Mat outputROI;	
	Mat SplitImage;
	Rect r(Point(p, p), Point(img.rows, img.cols));


		for (int i = 0; i < img.cols / n; i++)
		{
			for (int j = 0; j < img.rows / n; j++)
			{
				Rect z(Point(j * n, i * n), Point((j + 1) * n, (i + 1) * n));
				SplitImage = rotate(img(z), rot);
				outputROI = output(z);
				SplitImage.copyTo(outputROI);
			}
		}
		if (img.rows % n > 0)
		{
			for (int i = 0; i < (p / n); i++)
			{
				Rect a(Point(p, o), Point(img.rows, one * n));
				Rect b(Point(o, p), Point(one * n, img.cols));
				rotate(output(a), rot).copyTo(output(Rect(a)));
				rotate(output(b), rot).copyTo(output(Rect(b)));
				rotate(output(r), rot).copyTo(output(Rect(r)));
				o += n;
				one += 1;
			}
		}
		imshow("회전 슈화", img);
		imshow("회전 슈화3", output);
		cout << output.size << endl;
	}
