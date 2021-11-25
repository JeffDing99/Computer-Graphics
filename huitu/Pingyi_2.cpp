// Pingyi_2.cpp: 实现文件
//

#include "pch.h"
#include "huitu.h"
#include "Pingyi_2.h"
#include "afxdialogex.h"


// Pingyi_2 对话框

IMPLEMENT_DYNAMIC(Pingyi_2, CDialog)

Pingyi_2::Pingyi_2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
	, Tx(0)
	, Ty(0)
{

}

Pingyi_2::~Pingyi_2()
{
}

void Pingyi_2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Tx);
	DDX_Text(pDX, IDC_EDIT2, Ty);
}


BEGIN_MESSAGE_MAP(Pingyi_2, CDialog)
	ON_BN_CLICKED(IDOK, &Pingyi_2::OnBnClickedOk)
END_MESSAGE_MAP()


// Pingyi_2 消息处理程序


void Pingyi_2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialog::OnOK();
}
