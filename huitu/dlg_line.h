#pragma once


// dlg_line 对话框

class dlg_line : public CDialog
{
	DECLARE_DYNAMIC(dlg_line)

public:
	dlg_line(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dlg_line();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	double x1;
	double x2;
	double y1;
	double y2;

	afx_msg void OnClickedButton1();
};
