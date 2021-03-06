#pragma warning(disable:4996)
// CalculatorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//五子棋棋盘起始位置和格子宽度
#define bY 20
#define bX 20
#define BREATH 30
#define BIG 13//棋子大小

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCalculatorDlg 对话框

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCalculatorDlg::CCalculatorDlg(Player * p1, Player * p2, ChessBoard * board, CWnd * pParent)
	: CDialogEx(IDD_CALCULATOR_DIALOG,pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->p1 = p1;
	this->p2 = p2;
	this->board = board;
	this->isP1 = true;
	this->isWin = false;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
//	ON_BN_CLICKED(IDM_ABOUTBOX, &CCalculatorDlg::OnBnClickedAboutbox)
//	ON_BN_CLICKED(IDCANCEL, &CCalculatorDlg::OnBnClickedCancel)
//	ON_EN_CHANGE(IDC_EDIT4, &CCalculatorDlg::OnEnChangeEdit4)
//	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CCalculatorDlg::OnBnClickedButtonClean)
ON_COMMAND(ID_32772, &CCalculatorDlg::On32772)
ON_COMMAND(AFX_TIMER_ID_VISIBILITY_TIMER, &CCalculatorDlg::OnTimerIdVisibilityTimer)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->m_Menu.LoadMenuW(IDR_MENU1);//添加菜单栏
	this->SetMenu(&this->m_Menu);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint()
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
		this->SetBackgroundColor(RGB(0, 245, 0));
		
	}
	
	CPaintDC dc(this);
	CPen pen,*initPen; 
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	initPen = dc.SelectObject(&pen);
	
	
	for (int i = 0; i < 15; i++)
	{
		dc.MoveTo(bX, bY + i * BREATH);
		dc.LineTo(bX + BREATH * 14, bY +i* BREATH);
	}
	for (int i = 0; i < 15; i++)
	{
		dc.MoveTo(bX+i* BREATH, bY);
		dc.LineTo(bX + BREATH * i, bY + 14 * BREATH);
	}
	dc.SelectObject(initPen);
	//this->SetBackgroundColor(RGB(0, 0, 255));
	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this->isWin)
		return;
	if (point.x<bX - 10 || point.x>bX+BREATH*14+10||
			point.y<bY-10||point.y>bY+BREATH*14+10)
		return;

	int x, y;
	int nx, ny;

	nx = (point.x - bX) / BREATH;
	int mod = (point.x - bX) % BREATH;
	if (mod <= BREATH / 2)
		x = point.x - mod;
	else
	{
		x = point.x + (BREATH -mod);
		nx++;
	}
	
	ny = (point.y - bY) / BREATH;
	mod = (point.y - bY) % BREATH;
	if (mod <= BREATH / 2)
		y = point.y - mod;
	else
	{
		ny++;
		y = point.y + (BREATH - mod);
	}
//	if (this->isP1)
//	{
		if (!this->p1->SetChess(nx, ny))
		{
			return;
		}
		else
		{
			CClientDC dc(this);
			CBrush brush(RGB(0,0,0)), *oldBrush;
			oldBrush = dc.SelectObject(&brush);
			dc.Ellipse(x - BIG, y + BIG, x + BIG, y - BIG);
			dc.SelectObject(oldBrush);

			this->isWin = this->board->Judge(nx, ny, this->p1);
			if (this->isWin)
			{
				::MessageBox(NULL, _T("黑子赢了!"), _T("提示"), 0);
			}
			//this->isP1 = !this->isP1;
		}


		int cx, cy;

		//this->p2->ComputerChoice(this->p1,nx,ny);
		if(!this->p2->SetChess(nx,ny))
		{
			::MessageBox(NULL, _T("棋盘已满，平局!"), _T("提示"), 0);
			return;
		}
		cx = nx * BREATH + bX;
		cy = ny * BREATH + bY;
		CClientDC dc(this);
		CBrush brush(RGB(255,255,255)), *oldBrush;
		oldBrush = dc.SelectObject(&brush);
		dc.Ellipse(cx - BIG, cy + BIG, cx + BIG, cy - BIG);
		dc.SelectObject(oldBrush);

		this->isWin = this->board->Judge(nx, ny, this->p2);
		if (this->isWin)
		{
			::MessageBox(NULL, _T("白子赢了!"), _T("提示"), 0);
		}


//	}
/*	else
	{
		if (!this->p2->SetChess(nx, ny))
		{
			return ;
		}
		else
		{
			CClientDC dc(this);
			CBrush brush(RGB(255, 255, 255)), *oldBrush;
			oldBrush = dc.SelectObject(&brush);
			dc.Ellipse(x - BIG, y + BIG, x + BIG, y - BIG);
			dc.SelectObject(oldBrush);

			this->isWin = this->board->Judge(nx, ny, this->p1);
			if (this->isWin)
			{
				::MessageBox(NULL, _T("白子赢了!"), _T("提示"), 0);
			}
			this->isP1 = !this->isP1;
		}
	}
	*/
}

void CCalculatorDlg::setFirst(boolean isP1)
{
	this->isP1 = isP1;
}





void CCalculatorDlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	::PostQuitMessage(0);
}


void CCalculatorDlg::OnTimerIdVisibilityTimer()
{
	// TODO: 在此添加命令处理程序代码
	this->OnPaint();
	this->board->CLeanChessBoard();
	this->isP1 = true;
	this->isWin = false;
}
