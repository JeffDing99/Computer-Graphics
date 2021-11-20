#pragma once


// dlg_circle 对话框

class dlg_circle : public CDialog
{
	DECLARE_DYNAMIC(dlg_circle)

public:
	dlg_circle(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dlg_circle();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditx1();
	// 圆半径
	int circle_r;
	// 圆心x
	int circle_x;
	// 圆心坐标y
	int circle_y;
	afx_msg void OnClickedButton1();
};
