// dlg_line.cpp: 实现文件
//

#include "pch.h"
#include "huitu.h"
#include "dlg_line.h"
#include "afxdialogex.h"


// dlg_line 对话框

IMPLEMENT_DYNAMIC(dlg_line, CDialog)

dlg_line::dlg_line(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, x1(0)
	, x2(0)
	, y1(0)
	, y2(0)
{

}

dlg_line::~dlg_line()
{
}

void dlg_line::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITx1, x1);
	DDX_Text(pDX, IDC_EDITx2, x2);
	DDX_Text(pDX, IDC_EDITy1, y1);
	DDX_Text(pDX, IDC_EDITy2, y2);
}


BEGIN_MESSAGE_MAP(dlg_line, CDialog)
ON_BN_CLICKED(IDC_BUTTON1, &dlg_line::OnClickedButton1)
END_MESSAGE_MAP()


// dlg_line 消息处理程序


void dlg_line::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialog::EndDialog(0);
}
