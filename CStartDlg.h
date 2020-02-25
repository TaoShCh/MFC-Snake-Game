#pragma once


// CStartDlg 对话框

class CStartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartDlg)

public:
	CStartDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStartDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	CString m_name;
	int m_speed;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
};
