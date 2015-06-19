
// HotelSearchDlg.cpp : 实现文件
//
#define _CRT_SERCURE_NO_WARNINGS
#include "stdafx.h"
#include "HotelSearch.h"
#include "HotelSearchDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHotelSearchDlg 对话框



CHotelSearchDlg::CHotelSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHotelSearchDlg::IDD, pParent)
	, m_strFind(_T(""))
	, m_label(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHotelSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_FIND, m_strFind);
	DDX_Text(pDX, IDC_EDIT_FIND, m_strFind);
	DDX_Text(pDX, IDC_STATIC_LABEL, m_label);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CHotelSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CHotelSearchDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CHotelSearchDlg 消息处理程序

BOOL CHotelSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	InitMem();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHotelSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHotelSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHotelSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CHotelSearchDlg::GetFileColumn()
{
	int i = 0;
	FILE *pfr;
	pfr = fopen(path, "r");//读取文件
	if (pfr == NULL)
	{
		printf("文件操作失败");
		return -1;
	}
	else
	{
		while (!feof(pfr))
		{
			char str[256] = { 0 };
			fgets(str, 256, pfr);//读取一行
			i++;

		}
		fclose(pfr);
		return i;
	}
}

void CHotelSearchDlg::InitMem()
{
	//m_label = _T("正在加载内存");
	//int n = GetFileColumn();
	pp = (char **)malloc(n*(sizeof(char *)));//二级指针指向一个动态指针数组
	memset(pp, 0, n*sizeof(char *));//内存清零

	FILE *pfr;
	pfr = fopen(path, "r");//读取文件
	if (pfr == NULL)
	{
		AfxMessageBox(_T("文件操作失败"));
		return ;
	}
	else
	{
		for (int i = 0; i < n - 1; i++)
		{
			char str[256] = { 0 };
			fgets(str, 256, pfr);//读取一行
			int length = strlen(str);//获取长度
			pp[i] = (char *)malloc(length + 1);//分配内存
			if (pp[i] != NULL)
			{
				strcpy(pp[i], str);//拷贝内容
			}
		}
		fclose(pfr);
	}
	//AfxMessageBox(_T("内存加载完成"));
	m_label = _T("内存加载完成");
	UpdateData(FALSE);
}

void CHotelSearchDlg::OnBnClickedButtonSearch()
{
	// TODO:  在此添加控件通知处理程序代码
	//InitMem();
	//int n = GetFileColumn();
	UpdateData(TRUE);
	FILE *fpw = fopen(respath, "w");
	if (fpw == NULL)
	{
		AfxMessageBox(_T("文件操作失败"));
		return;
	}
	char findstr[20] = { 0 };

	//m_strFind = GetDlgItemText(IDC_EDIT_FIND);
	strcpy(findstr, (LPSTR)(LPCTSTR)m_strFind);

	for (int i = 0; i < n - 1; i++)
	{

		char *p = strstr(pp[i], findstr);
		if (p != NULL)
		{
			m_list.AddString((LPCTSTR)p);
			//AfxMessageBox((LPCTSTR)p);
			fputs(p, fpw);
		}
	}
	fclose(fpw);
}

