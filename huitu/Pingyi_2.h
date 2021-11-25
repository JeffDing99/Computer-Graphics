#pragma once


// Pingyi_2 对话框

class Pingyi_2 : public CDialog
{
	DECLARE_DYNAMIC(Pingyi_2)

public:
	Pingyi_2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Pingyi_2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int Tx;
	int Ty;
	afx_msg void OnBnClickedOk();
};
