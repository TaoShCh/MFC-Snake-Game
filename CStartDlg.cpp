// CStartDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSnake.h"
#include "CStartDlg.h"
#include "afxdialogex.h"
#include "MFCSnakeDlg.h"


// CStartDlg 对话框

IMPLEMENT_DYNAMIC(CStartDlg, CDialogEx)

CStartDlg::CStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_name(_T(""))
	, m_speed(5)
{

}

CStartDlg::~CStartDlg()
{
}

void CStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_speed);
}


BEGIN_MESSAGE_MAP(CStartDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStartDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CStartDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CStartDlg::OnEnChangeEdit2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CStartDlg::OnDeltaposSpin1)
END_MESSAGE_MAP()


// CStartDlg 消息处理程序


void CStartDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CMFCSnakeDlg game_dlg;
	theApp.speed = m_speed;
	theApp.name = m_name;
	UpdateData(false);
	INT_PTR ans = game_dlg.DoModal();
	CDialogEx::OnOK();
}


void CStartDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void CStartDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CStartDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (pNMUpDown->iDelta == 1) // 如果此值为-1 , 说明点击了Spin的往下的箭头
	{
		if (m_speed > 1) {
			m_speed--;
		}
	}
	else if (pNMUpDown->iDelta == -1) // 如果此值为1, 说明点击了Spin的往上的箭头
	{
		if (m_speed < 20) {
			m_speed++;
		}
	}
	UpdateData(false);
	*pResult = 0;
}
