
// MFCSnakeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCSnake.h"
#include "MFCSnakeDlg.h"
#include "afxdialogex.h"
#include "common.h"
#include "CRankDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCSnakeDlg 对话框



CMFCSnakeDlg::CMFCSnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSNAKE_DIALOG, pParent)
	, m_step(30)
	, m_point(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_step);
	DDX_Text(pDX, IDC_EDIT2, m_point);
}

BEGIN_MESSAGE_MAP(CMFCSnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCSnakeDlg 消息处理程序

BOOL CMFCSnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	SetTimer(SNAKE_TIMER, 1000/theApp.speed, NULL);
	food.generate_new_food(&snake);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CMFCSnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCSnakeDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(&rect);
	CBrush wall(RGB(156,102,31));
	dc.SelectObject(&wall);
	CRect rec1(0, 0, WALL_WIDTH + TOTAL_SIZE, WALL_WIDTH);
	CRect rec2(0, WALL_WIDTH, WALL_WIDTH, 2 * WALL_WIDTH + TOTAL_SIZE);
	CRect rec3(WALL_WIDTH, TOTAL_SIZE + WALL_WIDTH, 2 * WALL_WIDTH + TOTAL_SIZE, 2 * WALL_WIDTH + TOTAL_SIZE);
	CRect rec4(WALL_WIDTH + TOTAL_SIZE, 0, 2 * WALL_WIDTH + TOTAL_SIZE, WALL_WIDTH + TOTAL_SIZE);
	dc.FillRect(rec1, &wall);
	dc.FillRect(rec2, &wall);
	dc.FillRect(rec3, &wall);
	dc.FillRect(rec4, &wall);
	snake.display(&dc);
	food.display(&dc);
	CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCSnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCSnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent) {
	case SNAKE_TIMER:
		snake.move();
		if (snake.eat_food(&food)) {
			if (food.type == BIG) {
				for (int i = 0; i < 3; i++)
					snake.length_increase(&map);
				food.count = 0;
				food.step = 30;
				food.generate_new_food(&snake);
				m_point += 3 * theApp.speed;
			}
			else if (food.type == SMALL) {
				snake.length_increase(&map);
				food.generate_new_food(&snake);
				m_point += theApp.speed;
			}
			
		}
		if (snake.hit_itself() || snake.hit_wall(&map)) {
			KillTimer(SNAKE_TIMER);
			theApp.points = m_point;
			CRankDlg rank_dlg;
			INT_PTR ans = rank_dlg.DoModal();
			EndDialog(0);
		}
		if (food.type == BIG) {
			food.step--;
			if (food.step == 0) {
				food.count = 0;
				food.step = 30;
				food.generate_new_food(&snake);
			}
		}
		break;
	}
	m_step = food.step;
	UpdateData(false);
	Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CMFCSnakeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST) {
		snake.change_direction(pMsg->wParam);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}




HBRUSH CMFCSnakeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_3)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
