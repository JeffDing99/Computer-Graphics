#pragma once


// bili_2 对话框

class bili_2 : public CDialog
{
	DECLARE_DYNAMIC(bili_2)

public:
	bili_2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~bili_2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit4();
	int Sx;
	afx_msg void OnEnChangeEdit3();
	int Sy;
	int Tx;
	afx_msg void OnBnClickedOk();
};
