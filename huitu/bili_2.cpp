// bili_2.cpp: 实现文件
//

#include "pch.h"
#include "huitu.h"
#include "bili_2.h"
#include "afxdialogex.h"


// bili_2 对话框

IMPLEMENT_DYNAMIC(bili_2, CDialog)

bili_2::bili_2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG4, pParent)
	, Sx(0)
	, Sy(0)
	, Tx(0)
{

}

bili_2::~bili_2()
{
}

void bili_2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Sx);
	DDX_Text(pDX, IDC_EDIT3, Sy);
	DDX_Text(pDX, IDC_EDIT4, Tx);
}


BEGIN_MESSAGE_MAP(bili_2, CDialog)
	ON_EN_CHANGE(IDC_EDIT4, &bili_2::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT3, &bili_2::OnEnChangeEdit3)
	ON_BN_CLICKED(IDOK, &bili_2::OnBnClickedOk)
END_MESSAGE_MAP()


// bili_2 消息处理程序


void bili_2::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void bili_2::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void bili_2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialog::OnOK();
}
