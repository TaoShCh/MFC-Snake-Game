// CRankDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSnake.h"
#include "CRankDlg.h"
#include "afxdialogex.h"
#include <direct.h>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
// CRankDlg 对话框

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, ranklist(_T(""))
{
}

void CRankDlg::init_list() {
	char dir[200];
	_getcwd(dir, 200);
	char filename[200];
	char tmp[12] = "\\rank.txt";
	strcpy_s(filename, dir);
	strcat_s(filename, tmp);
	ifstream infile(filename);
	string players[11];
	int points[11];
	int count = 0;
	if (infile) {
		while (infile >> players[count] >> points[count]) {
			count++;
		}
	}
	players[count] = CT2A(theApp.name);
	points[count] = theApp.points;
	int id = count;
	for (int i = count; i > 0; i--) {
		if (points[i] > points[i - 1]) {
			swap(players[i], players[i - 1]);
			swap(points[i], points[i - 1]);
			id = i - 1;
		}
		else break;
	}
	infile.close();
	ofstream outfile(filename);
	for (int i = 0; i < min(10, count + 1); i++) {
		CString tmp;
		tmp.Format(_T("%d. "), i + 1);
		ranklist += tmp;
		tmp = players[i].c_str();
		ranklist += tmp;
		tmp.Format(_T(" %d\r\n"), points[i]);
		ranklist += tmp;
		outfile << players[i] << endl << points[i] << endl;
		//cout << i + 1 << ". " << players[i] << " " << points[i] << endl;
	}
	outfile.close();
	UpdateData(false);
}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ranklist);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)
END_MESSAGE_MAP()


// CRankDlg 消息处理程序

CFont myfont;
BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	init_list();
	myfont.CreatePointFont(120, (LPCTSTR)"Arial");
	CEdit* m_edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	m_edit->SetFont(&myfont);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
