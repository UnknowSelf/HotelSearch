
// HotelSearchDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CHotelSearchDlg 对话框
class CHotelSearchDlg : public CDialogEx
{
// 构造
public:
	CHotelSearchDlg(CWnd* pParent = NULL);	// 标准构造函数
	//~CHotelSearchDlg();

// 对话框数据
	enum { IDD = IDD_HOTELSEARCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CEdit m_strFind;
	CString m_strFind;

	const char *path = "F:\\下载\\源码和资料\\kaifang.txt";		//查询的路径
	const char *respath = "F:\\下载\\源码和资料\\kaifangres.txt";	//查询结果的路径

	char **pp = NULL;
	int n = 10001574;
	afx_msg void OnBnClickedButtonSearch();

public:
	int GetFileColumn();
	void InitMem();		//

	CString m_label;
	CListBox m_list;
};
