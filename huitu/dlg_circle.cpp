// dlg_circle.cpp: 实现文件
//

#include "pch.h"
#include "huitu.h"
#include "dlg_circle.h"
#include "afxdialogex.h"


// dlg_circle 对话框

IMPLEMENT_DYNAMIC(dlg_circle, CDialog)

dlg_circle::dlg_circle(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
	, circle_r(0)
	, circle_x(0)
	, circle_y(0)
{

}

dlg_circle::~dlg_circle()
{
}

void dlg_circle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITr, circle_r);
	DDX_Text(pDX, IDC_EDITx0, circle_x);
	DDX_Text(pDX, IDC_EDITy0, circle_y);
}


BEGIN_MESSAGE_MAP(dlg_circle, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &dlg_circle::OnClickedButton1)
END_MESSAGE_MAP()


// dlg_circle 消息处理程序


void dlg_circle::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialog::EndDialog(0);
}
