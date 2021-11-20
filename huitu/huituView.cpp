
// huituView.cpp: ChuituView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "huitu.h"
#endif
#include "Resource.h"

#include "huituDoc.h"
#include "huituView.h"
#include "dlg_line.h"
#include "dlg_circle.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ChuituView

IMPLEMENT_DYNCREATE(ChuituView, CView)

BEGIN_MESSAGE_MAP(ChuituView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &ChuituView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(32771, &ChuituView::OnDDA)
	ON_COMMAND(MidPointLine, &ChuituView::OnMidpointline)
	ON_COMMAND(MidPointCircle, &ChuituView::OnMidpointcircle)
	ON_COMMAND(BresenhamCircle, &ChuituView::OnBresenhamcircle)
	
	ON_COMMAND(BresenhamEllipse, &ChuituView::OnBresenhamellipse)
	ON_COMMAND(BresenhamLine, &ChuituView::OnBresenhamline)
	ON_COMMAND(PolygonScan, &ChuituView::OnPolygonscan)
	ON_COMMAND(PolygonFloodfill4, &ChuituView::OnPolygonfloodfill4)
	ON_COMMAND(PolygonFloodfill8, &ChuituView::OnPolygonfloodfill8)
	ON_COMMAND(Clean, &ChuituView::OnClean)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(pingyi2, &ChuituView::Onpingyi2)
	ON_COMMAND(xuanzhaun2, &ChuituView::Onxuanzhaun2)
	ON_COMMAND(cuoqie2, &ChuituView::Oncuoqie2)
	ON_COMMAND(bili2, &ChuituView::Onbili2)
	ON_COMMAND(duichen2, &ChuituView::Onduichen2)
	ON_COMMAND(cs_line, &ChuituView::Oncs_line)
	ON_COMMAND(wa_duo, &ChuituView::Onwa_duo)
	ON_COMMAND(pingyi3, &ChuituView::Onpingyi3)
	ON_COMMAND(xuanzhuan3, &ChuituView::Onxuanzhuan3)
	ON_COMMAND(duichen3, &ChuituView::Onduichen3)
	ON_COMMAND(bili3, &ChuituView::Onbili3)
	ON_COMMAND(cuoqie3, &ChuituView::Oncuoqie3)
	ON_COMMAND(sanshitu, &ChuituView::Onsanshitu)
END_MESSAGE_MAP()

// ChuituView 构造/析构

ChuituView::ChuituView() noexcept
{
	// TODO: 在此处添加构造代码

}

ChuituView::~ChuituView()
{
}

BOOL ChuituView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// ChuituView 绘图

void ChuituView::OnDraw(CDC* /*pDC*/)
{
	ChuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// ChuituView 打印


void ChuituView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL ChuituView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void ChuituView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void ChuituView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void ChuituView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void ChuituView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// ChuituView 诊断

#ifdef _DEBUG
void ChuituView::AssertValid() const
{
	CView::AssertValid();
}

void ChuituView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

ChuituDoc* ChuituView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ChuituDoc)));
	return (ChuituDoc*)m_pDocument;
}
#endif //_DEBUG


// ChuituView 消息处理程序



//重定义坐标轴
void ChuituView::Axis(CDC * pDC, CRect rect)
{
	// TODO: 在此处添加实现代码.
	// 画坐标轴
	pDC->MoveTo(0, rect.Height() / 2);
	pDC->LineTo(rect.Width(), rect.Height() / 2);
	pDC->MoveTo(rect.Width() / 2, 0);
	pDC->LineTo(rect.Width() / 2, rect.Height());

	//移动坐标原点到客户区中心
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(1000, -1000);
}



// 清屏
void ChuituView::OnClean()
{
	//  清屏
	RedrawWindow();
	state = 0;

}

//起点赋值
void ChuituView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC * pDC = GetDC();
	CView::OnLButtonDown(nFlags, point);
	B_x = point.x;//将鼠标此时x位置付给变量m_B_x
	B_y = point.y;

}

//终点赋值
void ChuituView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
	E_x = point.x;
	E_y = point.y;
	int r = (int)sqrt((E_y - B_y) *(E_y - B_y) - (E_x - B_x) *(E_x - B_x));

	switch (state)
	{
	case 1:OnBresenhamline_1(B_x, B_y, E_x, E_y); break;
	case 2:Bresenhamcircle_1(B_x, B_y, r); break;

	}

}

void ChuituView::OnDDA()
{
	// TODO: 在此添加命令处理程序代码
	dlg_line dlg;
	dlg.DoModal();
	

	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	//重定义坐标轴
	Axis(pDC, rect);

	pDC->TextOut(450, 18, _T("DDA画线法成功了！"));//在屏幕（450，18）的位置显示一个白色底色的黑字：DDA画线法成功了！
	

	double dx, dy, e, x, y;
	dx = dlg.x2 - dlg.x1;
	dy = dlg.y2 - dlg.y1;
	e = (fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));
	dx /= e;
	dy /= e;
	x = dlg.x1;
	y = dlg.y1;

	for (int i = 1; i <= e; ++i) {
		pDC->SetPixel(int(x + 0.5), int(y + 0.5), RGB(255, 0, 0));
		x += dx;
		y += dy;
	}
	
	
}




void ChuituView::OnMidpointline()
{
	// TODO: 在此添加命令处理程序代码
	dlg_line dlg;
	dlg.DoModal();
	float x, y, xa, xb, ya, yb;
	xa = dlg.x1, ya = dlg.y1;
	xb = dlg.x2; yb = dlg.y2;
	float d, k;
	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	//重定义坐标轴
	Axis(pDC, rect);
	pDC->TextOut(450, 18, _T("中点画线法成功了！"));
	k = (yb - ya) / (xb - xa);
	y = ya, x = xa;
	d = 0.5 - k;
	for (x = xa; x <= xb; x++)
	{
		if (d < 0)
		{
			y = y + 1; d = d + 1 - k;
		}
		else
		{
			y = y; d = d - k;
		}
		pDC->SetPixel(x, y, RGB(0, 0, 255));
	}
}

void ChuituView::OnBresenhamline_1(int x0, int y0, int x1, int y1)
{
	// TODO: 在此处添加实现代码.
	CDC* pDC = GetDC();
	

	pDC->TextOut(450, 70, _T("请用鼠标划线！"));

	// TODO: 在此添加命令处理程序代码

	int color = 255;
	int x, y, e;
	int dx = x1 - x0;//x偏移量
	int dy = y1 - y0;//y偏移量
	int ux = dx > 0 ? 1 : -1;//x伸展方向
	int uy = dy > 0 ? 1 : -1;//y伸展方向
	int dx2 = abs(dx << 1);//x偏移量乘2
	int dy2 = abs(dy << 1);//y偏移量乘2
	if (abs(dx) > abs(dy))//以x为增量方向计算
	{
		int e = -dx; //e = -0.5 * 2 * dx,把e 用2 * dx* e替换
		int x = x0;//起点x坐标
		int y = y0;//起点y坐标
		while (x != x1 + ux)
		{
			//printf("%d,%d\n", x, y);
			pDC->SetPixel(x, y, color);
			e = e + dy2;//来自 2*e*dx= 2*e*dx + 2dy  （原来是 e = e + k）
			if (e > 0)//e是整数且大于0时表示要取右上的点（否则是右下的点） 
			{
				if (y != y1)
				{
					y += uy;
				}
				e = e - dx2;//2*e*dx = 2*e*dx - 2*dx  (原来是 e = e -1)
			}
			x += ux;
		}
	}
	else
	{//以y为增量方向计算
		int e = -dy; //e = -0.5 * 2 * dy,把e 用2 * dy* e替换
		int x = x0;//起点x坐标
		int y = y0;//起点y坐标
		while (y != y1 + uy)
		{
			//printf("%d,%d\n", x, y);
			pDC->SetPixel(x, y, color);
			e = e + dx2;//来自 2*e*dy= 2*e*dy + 2dy  （原来是 e = e + k）
			if (e > 0)//e是整数且大于0时表示要取右上的点（否则是右下的点） 
			{
				if (x != x1)
				{
					x += ux;
				}
				e = e - dy2;//2*e*dy = 2*e*dy - 2*dy  (原来是 e = e -1)
			}
			y += uy;
		}
	}
}

void ChuituView::OnBresenhamline()
{
	CDC* pDC = GetDC();
	state = 1;
	pDC->TextOut(450, 70, _T("请用鼠标划线！"));
}

void ChuituView::OnMidpointcircle()
{
	// TODO: 在此添加命令处理程序代码
	dlg_circle dlg;
	dlg.DoModal();

	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	//重定义坐标轴
	Axis(pDC, rect);

	int r = dlg.circle_r;
	int x0 =dlg.circle_x, y0 = dlg.circle_y;
	double d;
	int x = 0;
	int y = r;
	d = 1 - r;
	int color = 255;
	//pDC->SetPixel(x, y, color);
	
	while (x < y)
	{

		pDC->SetPixel(x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(y + x0, x + y0, color);
		pDC->SetPixel(-y + x0, x + y0, color);
		pDC->SetPixel(-y + x0, -x + y0, color);
		pDC->SetPixel(y + x0, -x + y0, color);
		if (d < 0)
		{
			d += 2 * x;
			++x;
		}
		else
		{
			d += 2 * (x - y) + 5;
			++x;
			--y;
		}
		//pDC->SetPixel(x, y, 255);
	}
}


void ChuituView::Bresenhamcircle_1(int x0, int y0, int r)
{
	// TODO: 在此处添加实现代码.
	CDC *pDC = GetDC();
	
	int color = 255;
	int x = 0;
	int y = r;
	int d = 1 - r;

	
	while (x <= y)
	{
		pDC->SetPixel(x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(y + x0, x + y0, color);
		pDC->SetPixel(-y + x0, x + y0, color);
		pDC->SetPixel(-y + x0, -x + y0, color);
		pDC->SetPixel(y + x0, -x + y0, color);
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}
void ChuituView::OnBresenhamcircle()
{
	// TODO: 在此添加命令处理程序代码
	CDC *pDC = GetDC();
	pDC->TextOut(450, 70, _T("请用鼠标划线以确定远点坐标和半径！"));
	state = 2;
	
}




void ChuituView::OnBresenhamellipse()
{
	// TODO: 在此添加命令处理程序代码
	CRect rect;
	GetClientRect(&rect);
	CDC* pDC = GetDC();
	//重定义坐标轴
	Axis(pDC, rect);

	pDC->TextOut(400, 70, _T("这是一个长半轴为200,短半轴100的椭圆！"));
	int a = 200, b = 100, color = 255, x, y;
	float d1;
	float d2 = 0;
	x = 0; y = b;
	d1 = b * b + a * a*(-b + 0.25);
	pDC->SetPixel(x, y, color);
	pDC->SetPixel(-x, -y, color);
	pDC->SetPixel(-x, y, color);
	pDC->SetPixel(x, -y, color);
	while (b*b*(x + 1) < a*a*(y - 0.5))
	{
		if (d1 <= 0)
		{
			d1 += b * b*(2 * x + 3);
			x++;
		}
		else
		{
			d1 += b * b*(2 * x + 3) + a * a*(-2 * y + 2);
			x++;
			y--;
		}
		pDC->SetPixel(x, y, color);
		pDC->SetPixel(-x, -y, color);
		pDC->SetPixel(-x, y, color);
		pDC->SetPixel(x, -y, color);
	}
	d2 += b * b*(x + 0.5)*(x + 0.5) + a * a*(y - 1)*(y - 1) - a * a*b*b;
	while (y > 0)
	{
		if (d2 <= 0)
		{
			d2 += b * b*(2 * x + 2) + a * a*(-2 * y + 3);
			x++;
			y--;
		}
		else
		{
			d2 += a * a*(-2 * y + 3);
			y--;
		}
		pDC->SetPixel(x, y, color);
		pDC->SetPixel(-x, -y, color);
		pDC->SetPixel(-x, y, color);
		pDC->SetPixel(x, -y, color);
	}
}

//直线扫描
void ChuituView::OnPolygonscan()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();

	const int POINTNUM = 6;
	typedef struct XET
	{
		float x;
		float dx, ymax;
		XET* next;
	}
	AET, NET;
	struct point
	{
		float x;
		float y;
	}
	polypoint[POINTNUM] = { 250, 50, 550, 150, 550, 400, 250, 250, 100, 350, 100, 100 };

	int MaxY = 0;
	int i;
	for (i = 0; i < POINTNUM; i++)
		if (polypoint[i].y > MaxY)
			MaxY = polypoint[i].y;

	AET *pAET = new AET;
	pAET->next = NULL;


	NET *pNET[1024];
	for (i = 0; i <= MaxY; i++)
	{
		pNET[i] = new NET;
		pNET[i]->next = NULL;
	}
	for (i = 0; i <= MaxY; i++)
	{
		for (int j = 0; j < POINTNUM; j++)
			if (polypoint[j].y == i)
			{
				if (polypoint[(j - 1 + POINTNUM) % POINTNUM].y > polypoint[j].y)
				{
					NET *p = new NET;
					p->x = polypoint[j].x;
					p->ymax = polypoint[(j - 1 + POINTNUM) % POINTNUM].y;
					p->dx = (polypoint[(j - 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j - 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
				if (polypoint[(j + 1 + POINTNUM) % POINTNUM].y > polypoint[j].y)
				{
					NET *p = new NET;
					p->x = polypoint[j].x;
					p->ymax = polypoint[(j + 1 + POINTNUM) % POINTNUM].y;
					p->dx = (polypoint[(j + 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j + 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
			}
	}
	for (i = 0; i <= MaxY; i++)
	{
		NET *p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx;
			p = p->next;
		}

		AET *tq = pAET;
		p = pAET->next;
		tq->next = NULL;
		while (p)
		{
			while (tq->next && p->x >= tq->next->x)
				tq = tq->next;
			NET *s = p->next;
			p->next = tq->next;
			tq->next = p;
			p = s;
			tq = pAET;
		}
		AET *q = pAET;
		p = q->next;
		while (p)
		{
			if (p->ymax == i)
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}
		p = pNET[i]->next;
		q = pAET;
		while (p)
		{
			while (q->next && p->x >= q->next->x)
				q = q->next;
			NET *s = p->next;
			p->next = q->next;
			q->next = p;
			p = s;
			q = pAET;
		}
		p = pAET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				pDC->SetPixel(static_cast<int>(j), i, RGB(255, 0, 0));
			p = p->next->next;//考虑端点情况
		}
	}
}


//四领域
void ChuituView::OnPolygonfloodfill4()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc1(this);
	
	for (int i = 0; i <= 60; i++)
	{
		dc1.SetPixel(0, i, 200);
	}
	for (int i = 0; i <= 60; i++)
		dc1.SetPixel(i, 0, 200);
	for (int i = 0; i <= 60; i++)
		dc1.SetPixel(i, 60, 200);
	for (int i = 0; i <= 60; i++)
		dc1.SetPixel(60, i, 200);

	FloodFill4(20, 20, 200, 100);
}
void ChuituView::FloodFill4(int x, int y, int oldColor, int newColor)
{
	CClientDC dc(this);
	

	int color;
	color = dc.GetPixel(x, y);
	if ((color != oldColor) && color != newColor)
	{
		dc.SetPixel(x, y, newColor);
		FloodFill4(x, y + 1, oldColor, newColor);
		FloodFill4(x, y - 1, oldColor, newColor);
		FloodFill4(x - 1, y, oldColor, newColor);
		FloodFill4(x + 1, y, oldColor, newColor);

	}
}

//八领域
void ChuituView::OnPolygonfloodfill8()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc1(this);
	for (int i = 0; i <= 50; i++)
	{
		dc1.SetPixel(0, i, 200);
	}
	for (int i = 0; i <= 50; i++)
		dc1.SetPixel(i, 0, 200);
	for (int i = 0; i <= 50; i++)
		dc1.SetPixel(i, 50, 200);
	for (int i = 0; i <= 50; i++)
		dc1.SetPixel(50, i, 200);
	FloodFill8(6, 6, 200, 250);
}


void ChuituView::FloodFill8(int x, int y, int oldColor, int newColor)
{
	CClientDC dc(this);
	int color;
	color = dc.GetPixel(x, y);
	if ((color != oldColor) && color != newColor)
	{
		dc.SetPixel(x, y, newColor);
		FloodFill8(x, y + 1, oldColor, newColor);
		FloodFill8(x, y - 1, oldColor, newColor);
		FloodFill8(x - 1, y, oldColor, newColor);
		FloodFill8(x + 1, y, oldColor, newColor);
		FloodFill8(x + 1, y + 1, oldColor, newColor);
		FloodFill8(x - 1, y - 1, oldColor, newColor);
		FloodFill8(x + 1, y - 1, oldColor, newColor);
		FloodFill8(x - 1, y + 1, oldColor, newColor);
	}
}












/*
二维几何变换-五种基本变换
*/
//平移
void ChuituView::Onpingyi2()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//返回的是设备坐标，而SetViewportOrg需要的也是设备坐标，故此处不用转换
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	int Tx = 100, Ty = 200;//x平移100，y平移200
	int a[4][2] = { 0, 0, 100, 0, 100, 100, 0, 0 };//确定三角形的形状
	dc.TextOut(100, 0, (CString)"原图形");

	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0], a[i][1]);
		dc.LineTo(a[i + 1][0], a[i + 1][1]);
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	dc.SelectObject(&pen);
	dc.TextOut(100 + Tx, Ty, (CString)"平移后图形");
	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0] + Tx, a[i][1] + Ty);
		dc.LineTo(a[i + 1][0] + Tx, a[i + 1][1] + Ty);
	}
}

//旋转
void ChuituView::Onxuanzhaun2()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//返回的是设备坐标，而SetViewportOrg需要的也是设备坐标，故此处不用转换
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	float o = 3.1415926 / 2; //旋转90度
	float c = cos(o);
	float s = sin(o);
	int Tx = 300;
	int a[4][2] = { 0, 0, 100, 0, 100, 100, 0, 0 };//确定三角形的形状
	dc.TextOut(100, 0, (CString)"原图形");

	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0], a[i][1]);
		dc.LineTo(a[i + 1][0], a[i + 1][1]);
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	dc.SelectObject(&pen);
	dc.TextOut(100 * c + Tx, 0, (CString)"旋转后图形");
	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0] * c - a[i][1] * s + Tx, a[i][0] * s + a[i][0] * c);
		dc.LineTo(a[i + 1][0] * c - a[i + 1][1] * s + Tx, a[i + 1][0] * s + a[i + 1][0] * c);
	}
}

//错切
void ChuituView::Oncuoqie2()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//返回的是设备坐标，而SetViewportOrg需要的也是设备坐标，故此处不用转换
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	int b = 2, c = 2;
	int Tx = 300;
	int a[4][2] = { 0, 0, 100, 0, 100, 100, 0, 0 };//确定三角形的形状
	dc.TextOut(100, 0, (CString)"原图形");

	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0], a[i][1]);
		dc.LineTo(a[i + 1][0], a[i + 1][1]);
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	dc.SelectObject(&pen);
	dc.TextOut(100 + Tx, 0, (CString)"错切后图形");
	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0] + c * a[i][1] + Tx, b * a[i][0] + a[i][1]);
		dc.LineTo(a[i + 1][0] + c * a[i + 1][1] + Tx, b * a[i + 1][0] + a[i + 1][1]);
	}
}


//比例
void ChuituView::Onbili2()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//返回的是设备坐标，而SetViewportOrg需要的也是设备坐标，故此处不用转换
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	int Tx = 300;
	int Sx = 3, Sy = 4; //放大缩小比例
	int a[4][2] = { 0, 0, 100, 0, 100, 100, 0, 0 };//确定三角形的形状
	dc.TextOut(100, 0, (CString)"原图形");

	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0], a[i][1]);
		dc.LineTo(a[i + 1][0], a[i + 1][1]);
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	dc.SelectObject(&pen);
	dc.TextOut(100 + Tx, 0, (CString)"比例变换后图形");
	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0] * Sx + Tx, a[i][1] * Sy);
		dc.LineTo(a[i + 1][0] * Sx + Tx, a[i + 1][1] * Sy);
	}
}

//对称
void ChuituView::Onduichen2()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//返回的是设备坐标，而SetViewportOrg需要的也是设备坐标，故此处不用转换
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	int a[4][2] = { 0, 0, 100, 0, 100, 100, 0, 0 };//确定三角形的形状
	dc.TextOut(100, 0, (CString)"原图形");

	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(a[i][0], a[i][1]);
		dc.LineTo(a[i + 1][0], a[i + 1][1]);
	}

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	dc.SelectObject(&pen);
	dc.TextOut(-100, -0, (CString)"对称后图形");
	for (int i = 0; i < 3; i++)
	{
		dc.MoveTo(-a[i][0], -a[i][1]);
		dc.LineTo(-a[i + 1][0], -a[i + 1][1]);
	}
}

//直线cohen-sutherland法
unsigned int ChuituView::EnCode(CPoint point)
{
	#define D0 1 //0001
	#define D1 2 //0010
	#define D2 4 //0100
	#define D3 8 //1000
	// TODO: 在此处添加实现代码.
	int C1 = 0;
	if (point.x < wxl)
		C1 = C1 | D0;
	if (point.x > wxr)
		C1 = C1 | D1;
	if (point.y < wyb)
		C1 = C1 | D2;
	if (point.y > wyt)
		C1 = C1 | D3;
	return C1;
}

void ChuituView::Oncs_line()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();
	ChuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// wxl为左侧裁剪边，wxr为右侧裁剪边，wyb为下侧裁剪边，wyt为上裁剪边。
	wxl = 200, wxr = 700, wyb = 200, wyt = 600;
	
	pDC->Rectangle(wxl, wyb, wxr, wyt);
	CPoint A(500, 400), B(800, 420);//全部保留
	CohenSutherland(A, B, pDC);
	CPoint C(1000, 500), D(900, 500);//完全去除
	CohenSutherland(C, D, pDC);
	CPoint E(350, 300), F(1200, 300);//直线需要剪切
	CohenSutherland(E, F, pDC);
	
}

void ChuituView::CohenSutherland(CPoint p1, CPoint p2, CDC * pdc)
{
		#define D0 1 //0001
		#define D1 2 //0010
		#define D2 4 //0100
		#define D3 8 //1000
	// TODO: 在此处添加实现代码.
	int code1, code2, code;

	CPoint p;
	code1 = EnCode(p1);
	code2 = EnCode(p2);
	while (code1 != 0 || code2 != 0)
	{
		if (code1 && code2 != 0)//全部位于外部
			return;
		if (code1 != 0)code = code1;//部分在外部
		else
			code = code2;
		if ((D0 & code) != 0)//Left 
		{
			p.x = wxl;
			p.y = p1.y + (p.x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		}
		else if ((D1 & code) != 0)//Right
		{
			p.x = wxr;
			p.y = p1.y + (p.x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		}
		else if ((D2 & code) != 0)//Bottom
		{
			p.y = wyb;
			p.x = p1.x + (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
		}
		else if ((D3 & code) != 0)//Top
		{
			p.y = wyt;
			p.x = p1.x + (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
		}
		if (code == code1)//p1在外部
		{
			p1.x = p.x; p1.y = p.y;
			code1 = EnCode(p);
		}
		else
		{
			p2.x = p.x; p2.y = p.y;
			code2 = EnCode(p);
		}
	}
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 123, 100));
	pdc->SelectObject(&pen);
	pdc->MoveTo(p1);
	pdc->LineTo(p2);

}


//多边形weiler-atherton法
void ChuituView::Onwa_duo()
{
	// TODO: 在此添加命令处理程序代码
	int x0, y0, x1, y1;
	CClientDC dc(this);
	int min_clip_x = 100, min_clip_y = 100, max_clip_x = 300, max_clip_y = 300;
	dc.MoveTo(min_clip_x, min_clip_y);
	dc.LineTo(min_clip_x, max_clip_y);
	dc.MoveTo(min_clip_x, max_clip_y);
	dc.LineTo(max_clip_x, max_clip_y);
	dc.MoveTo(max_clip_x, max_clip_y);
	dc.LineTo(max_clip_x, min_clip_y);
	dc.MoveTo(max_clip_x, min_clip_y);
	dc.LineTo(min_clip_x, min_clip_y);
	x0 = 120; y0 = 90; x1 = 310, y1 = 310;
	cut_line(x0, y0, x1, y1);

}

void ChuituView::cut_line(int x0, int x1, int y0, int y1)
{
	// TODO: 在此处添加实现代码.
	#define CLIP_CODE_C 0x0000  
	#define CLIP_CODE_N 0x0008  
	#define CLIP_CODE_S 0x0004  
	#define CLIP_CODE_E 0x0002  
	#define CLIP_CODE_W 0x0001  
	#define CLIP_CODE_NE 0x000a  
	#define CLIP_CODE_SE 0x0006  
	#define CLIP_CODE_NW 0x0009  
	#define CLIP_CODE_SW 0x0005  
	int min_clip_x = 100, min_clip_y = 100, max_clip_x = 300, max_clip_y = 300;
	int p0_code = 0, p1_code = 0;
	//确定各个顶点所在的位置代码  
	if (y0 < min_clip_y)
		p0_code |= CLIP_CODE_N;
	else if (y0 > max_clip_y)
		p0_code |= CLIP_CODE_S;
	if (x0 < min_clip_x)
		p0_code |= CLIP_CODE_W;
	else if (x0 > max_clip_x)
		p0_code |= CLIP_CODE_E;
	if (y1 < min_clip_y)
		p1_code |= CLIP_CODE_N;
	else if (y1 > max_clip_y)
		p1_code |= CLIP_CODE_S;
	if (x1 < min_clip_x)
		p1_code |= CLIP_CODE_W;
	else if (x1 > max_clip_x)
		p1_code |= CLIP_CODE_E;
	//先检测一些简单的情况  
	if (p0_code & p1_code) //有相同的位置代码，表示在裁剪区外部  
	{
		return;
	}
	else if (p0_code == 0 && p1_code == 0) //表示两个点都在裁剪区内，不需要裁剪  
	{
		CClientDC dc(this);
		dc.MoveTo(x0, y0);
		dc.LineTo(x1, y1);
		return;
	}
	else
	{
		int x2, y2;
		x2 = (x0 + x1) / 2;
		y2 = (y0 + y1) / 2;
		if (x0 - x2 > 1 || x2 - x0 > 1)
		{
			cut_line(x0, y0, x2, y2);
		}
		if (x1 - x2 > 1 || x2 - x1 > 1)
		{
			cut_line(x2, y2, x1, y1);
		}
	}
	return;

}


/*
三维几何变换-五种基本变换
*/
//平移
void ChuituView::Onpingyi3()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CPen pen1, pen2;
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen2.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));//粗度为2，由黑色变为蓝色
	int a[4][4] = { 100, 150, 0, 1, 50, 200, 0, 1, 150, 200, 0, 1, 100, 150, 0, 1 };
	dc.SelectObject(&pen1);
	dc.MoveTo(a[0][0], a[0][1]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(a[i][0], a[i][1]);
	}
	int b[4][4] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 100, 100, 0, 1 };
	int c[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			c[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	dc.SelectObject(&pen2);
	dc.MoveTo(c[0][0], c[0][1]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(c[i][0], c[i][1]);
	}
	pen1.DeleteObject();
	pen2.DeleteObject();
}

//旋转
void ChuituView::Onxuanzhuan3()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CPen pen1, pen2;
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen2.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));//粗度为2，由黑色变为蓝色
	int a[4][4] = { 100, 150, 0, 1, 50, 200, 0, 1, 150, 200, 0, 1, 100, 150, 0, 1 };
	dc.SelectObject(&pen1);
	dc.MoveTo(a[0][0], a[0][1]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(a[i][0], a[i][1]);
	}
	int t = 600;
	dc.SelectObject(&pen2);
	dc.MoveTo(a[0][0] * cos((t / 6) * 1.0) - a[0][1] * sin((t / 6) * 1.0),//一个点 
		a[0][0] * sin((t / 6) * 1.0) + a[0][1] * cos((t / 6) * 1.0));
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(a[i][0] * cos((t / 6) * 1.0) - a[i][1] * sin((t / 6) * 1.0),//一个点 
			a[i][0] * sin((t / 6) * 1.0) + a[i][1] * cos((t / 6) * 1.0));
	}
	pen1.DeleteObject();
	pen2.DeleteObject();
}

//对称
void ChuituView::Onduichen3()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CPen pen1, pen2;
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen2.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));//粗度为2，由黑色变为蓝色
	int a[4][4] = { 100, 150, 0, 1, 50, 200, 0, 1, 150, 200, 0, 1, 100, 150, 0, 1 };
	dc.SelectObject(&pen1);
	dc.MoveTo(a[0][0], a[0][1]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(a[i][0], a[i][1]);
	}
	int b[4][4] = { 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };  //沿y=x对称
	int c[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			c[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	dc.SelectObject(&pen2);
	dc.MoveTo(c[0][0], c[0][1]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(c[i][0], c[i][1]);
	}
	pen1.DeleteObject();
	pen2.DeleteObject();

}


//比例
void ChuituView::Onbili3()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CPen pen1, pen2;
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen2.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));//粗度为2，由黑色变为蓝色
	int a[4][4] = { 100, 150, 0, 1, 50, 200, 0, 1, 150, 200, 0, 1, 100, 150, 0, 1 };
	dc.SelectObject(&pen1);
	dc.MoveTo(a[0][0], a[0][1]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(a[i][0], a[i][1]);
	}
	int b[4][4] = { 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1 };
	int c[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			c[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	dc.SelectObject(&pen2);
	dc.MoveTo(c[0][0], c[0][1]);
	for (int i = 0; i < 4; i++)
	{
		dc.LineTo(c[i][0], c[i][1]);
	}
	pen1.DeleteObject();
	pen2.DeleteObject();
}

//错切
void ChuituView::Oncuoqie3()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CPen pen1, pen2;
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen2.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));//粗度为2，由黑色变为蓝色
	int a[4][4] = { 100, 150, 0, 1, 50, 200, 0, 1, 150, 200, 0, 1, 100, 150, 0, 1 };
	dc.SelectObject(&pen1);
	dc.MoveTo(a[0][0], a[0][1]);
	for (int i = 0; i < 4; i++) {
		dc.LineTo(a[i][0], a[i][1]);
	}
	int b[4][4] = { 1, 2, 0, 0, 1.5, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	int c[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	dc.SelectObject(&pen2);
	dc.MoveTo(c[0][0], c[0][1]);
	for (int i = 0; i < 4; i++) {
		dc.LineTo(c[i][0], c[i][1]);
	}
	pen1.DeleteObject();
	pen2.DeleteObject();
}

//三视图
void ChuituView::Onsanshitu()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();
	int a[10][4] = { {0,0,0,1},{0,0,2,1},{1,0,2,1},{1,0,0,1},{0,1,0,1},{0,1,1,1},{0,1,2,1},{1,1,2,1},{1,2,1,1},{1,2,0,1} };
	int T1[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,0,0},{0,0,0,1} };
	int T2[4][4] = { {0,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	int Ry[4][4] = { {0,0,-1,0},{0,1,0,0},{1,0,0,0},{0,0,0,0} };
	int Tw[4][4] = { {0,0,0,0},{0,1,0,0},{1,0,0,0},{2,0,0,1} };
	int Mx[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{100,0,0,1} };
	int t[4][4], b[10][4], c[10][4], d[10][4];
	int i, j, k, temp;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			temp = 0;
			for (k = 0; k < 4; k++)
			{
				temp = temp + T2[i][k] * Mx[k][j];
			}
			t[i][j] = temp;

		}
	}
	int Th[4][4] = { {1,0,0,0},{0,0,0,0},{0,-1,0,0},{0,5,0,1} };
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 4; j++)
		{
			temp = 0;
			for (k = 0; k < 4; k++)
			{
				temp = temp + a[i][k] * T1[k][j];
			}
			b[i][j] = temp;

		}
	}
	CPen pen1(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* p1, *p2;
	p1 = pDC->SelectObject(&pen1);
	//1-2
	pDC->MoveTo(b[0][0] * 50 * 2, b[0][1] * 50 * 2);
	pDC->LineTo(b[1][0] * 50 * 2, b[1][1] * 50 * 2);
	//1-4
	pDC->MoveTo(b[0][0] * 50 * 2, b[0][1] * 50 * 2);
	pDC->LineTo(b[3][0] * 50 * 2, b[3][1] * 50 * 2);
	//1-5
	pDC->MoveTo(b[0][0] * 50 * 2, b[0][1] * 50 * 2);
	pDC->LineTo(b[4][0] * 50 * 2, b[4][1] * 50 * 2);
	//2-3
	pDC->MoveTo(b[1][0] * 50 * 2, b[1][1] * 50 * 2);
	pDC->LineTo(b[2][0] * 50 * 2, b[2][1] * 50 * 2);
	//2-7
	pDC->MoveTo(b[1][0] * 50 * 2, b[1][1] * 50 * 2);
	pDC->LineTo(b[6][0] * 50 * 2, b[6][1] * 50 * 2);
	//3-4
	pDC->MoveTo(b[2][0] * 50 * 2, b[2][1] * 50 * 2);
	pDC->LineTo(b[3][0] * 50 * 2, b[3][1] * 50 * 2);
	//3-8
	pDC->MoveTo(b[2][0] * 50 * 2, b[2][1] * 50 * 2);
	pDC->LineTo(b[7][0] * 50 * 2, b[7][1] * 50 * 2);
	//4-10
	pDC->MoveTo(b[3][0] * 50 * 2, b[3][1] * 50 * 2);
	pDC->LineTo(b[9][0] * 50 * 2, b[9][1] * 50 * 2);
	//5-6
	pDC->MoveTo(b[4][0] * 50 * 2, b[4][1] * 50 * 2);
	pDC->LineTo(b[5][0] * 50 * 2, b[5][1] * 50 * 2);
	//5-10
	pDC->MoveTo(b[4][0] * 50 * 2, b[4][1] * 50 * 2);
	pDC->LineTo(b[9][0] * 50 * 2, b[9][1] * 50 * 2);
	//6-7
	pDC->MoveTo(b[5][0] * 50 * 2, b[5][1] * 50 * 2);
	pDC->LineTo(b[6][0] * 50 * 2, b[6][1] * 50 * 2);
	//6-8
	pDC->MoveTo(b[5][0] * 50 * 2, b[5][1] * 50 * 2);
	pDC->LineTo(b[7][0] * 50 * 2, b[7][1] * 50 * 2);
	//6-9
	pDC->MoveTo(b[5][0] * 50 * 2, b[5][1] * 50 * 2);
	pDC->LineTo(b[8][0] * 50 * 2, b[8][1] * 50 * 2);
	//7-8
	pDC->MoveTo(b[6][0] * 50 * 2, b[6][1] * 50 * 2);
	pDC->LineTo(b[7][0] * 50 * 2, b[7][1] * 50 * 2);
	//8-9
	pDC->MoveTo(b[7][0] * 50 * 2, b[7][1] * 50 * 2);
	pDC->LineTo(b[8][0] * 50 * 2, b[8][1] * 50 * 2);
	//9-10
	pDC->MoveTo(b[8][0] * 50 * 2, b[8][1] * 50 * 2);
	pDC->LineTo(b[9][0] * 50 * 2, b[9][1] * 50 * 2);
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 4; j++)
		{
			temp = 0;
			for (k = 0; k < 4; k++)
			{
				temp = temp + a[i][k] * Tw[k][j];
			}
			c[i][j] = temp;

		}
	}
	CPen pen2(PS_SOLID, 1, RGB(128, 128, 0));
	p2 = pDC->SelectObject(&pen2);
	//1-2
	pDC->MoveTo(c[0][0] * 50 * 2, c[0][1] * 50 * 2);
	pDC->LineTo(c[1][0] * 50 * 2, c[1][1] * 50 * 2);
	//1-4
	pDC->MoveTo(c[0][0] * 50 * 2, c[0][1] * 50 * 2);
	pDC->LineTo(c[3][0] * 50 * 2, c[3][1] * 50 * 2);
	//1-5
	pDC->MoveTo(c[0][0] * 50 * 2, c[0][1] * 50 * 2);
	pDC->LineTo(c[4][0] * 50 * 2, c[4][1] * 50 * 2);
	//2-3
	pDC->MoveTo(c[1][0] * 50 * 2, c[1][1] * 50 * 2);
	pDC->LineTo(c[2][0] * 50 * 2, c[2][1] * 50 * 2);
	//2-7
	pDC->MoveTo(c[1][0] * 50 * 2, c[1][1] * 50 * 2);
	pDC->LineTo(c[6][0] * 50 * 2, c[6][1] * 50 * 2);
	//3-4
	pDC->MoveTo(c[2][0] * 50 * 2, c[2][1] * 50 * 2);
	pDC->LineTo(c[3][0] * 50 * 2, c[3][1] * 50 * 2);
	//3-8
	pDC->MoveTo(c[2][0] * 50 * 2, c[2][1] * 50 * 2);
	pDC->LineTo(c[7][0] * 50 * 2, c[7][1] * 50 * 2);
	//4-10
	pDC->MoveTo(c[3][0] * 50 * 2, c[3][1] * 50 * 2);
	pDC->LineTo(c[9][0] * 50 * 2, c[9][1] * 50 * 2);
	//5-10
	pDC->MoveTo(c[4][0] * 50 * 2, c[4][1] * 50 * 2);
	pDC->LineTo(c[9][0] * 50 * 2, c[9][1] * 50 * 2);
	//5-6
	CPen pen3(PS_DASH, 1, RGB(128, 128, 0));
	p2 = pDC->SelectObject(&pen3);
	pDC->MoveTo(c[4][0] * 50 * 2, c[4][1] * 50 * 2);
	pDC->LineTo(c[5][0] * 50 * 2, c[5][1] * 50 * 2);
	//6-7
	pDC->MoveTo(c[5][0] * 50 * 2, c[5][1] * 50 * 2);
	pDC->LineTo(c[6][0] * 50 * 2, c[6][1] * 50 * 2);
	//6-8
	pDC->MoveTo(c[5][0] * 50 * 2, c[5][1] * 50 * 2);
	pDC->LineTo(c[7][0] * 50 * 2, c[7][1] * 50 * 2);
	//6-9
	pDC->MoveTo(c[5][0] * 50 * 2, c[5][1] * 50 * 2);
	pDC->LineTo(c[8][0] * 50 * 2, c[8][1] * 50 * 2);
	//7-8
	pDC->MoveTo(c[6][0] * 50 * 2, c[6][1] * 50 * 2);
	pDC->LineTo(c[7][0] * 50 * 2, c[7][1] * 50 * 2);
	CPen pen4(PS_SOLID, 1, RGB(128, 128, 0));
	p2 = pDC->SelectObject(&pen4);
	//8-9
	pDC->MoveTo(c[7][0] * 50 * 2, c[7][1] * 50 * 2);
	pDC->LineTo(c[8][0] * 50 * 2, c[8][1] * 50 * 2);
	//9-10
	pDC->MoveTo(c[8][0] * 50 * 2, c[8][1] * 50 * 2);
	pDC->LineTo(c[9][0] * 50 * 2, c[9][1] * 50 * 2);
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 4; j++)
		{
			temp = 0;
			for (k = 0; k < 4; k++)
			{
				temp = temp + a[i][k] * Th[k][j];
			}
			d[i][j] = temp;

		}
	}
	CPen pen5(PS_SOLID, 1, RGB(0, 0, 255));
	p1 = pDC->SelectObject(&pen5);
	//1-2
	pDC->MoveTo(d[0][0] * 50 * 2, d[0][1] * 50 * 2);
	pDC->LineTo(d[1][0] * 50 * 2, d[1][1] * 50 * 2);
	//1-4
	pDC->MoveTo(d[0][0] * 50 * 2, d[0][1] * 50 * 2);
	pDC->LineTo(d[3][0] * 50 * 2, d[3][1] * 50 * 2);
	//1-5
	pDC->MoveTo(d[0][0] * 50 * 2, d[0][1] * 50 * 2);
	pDC->LineTo(d[4][0] * 50 * 2, d[4][1] * 50 * 2);
	//2-3
	pDC->MoveTo(d[1][0] * 50 * 2, d[1][1] * 50 * 2);
	pDC->LineTo(d[2][0] * 50 * 2, d[2][1] * 50 * 2);
	//2-7
	pDC->MoveTo(d[1][0] * 50 * 2, d[1][1] * 50 * 2);
	pDC->LineTo(d[6][0] * 50 * 2, d[6][1] * 50 * 2);
	//3-4
	pDC->MoveTo(d[2][0] * 50 * 2, d[2][1] * 50 * 2);
	pDC->LineTo(d[3][0] * 50 * 2, d[3][1] * 50 * 2);
	//3-8
	pDC->MoveTo(d[2][0] * 50 * 2, d[2][1] * 50 * 2);
	pDC->LineTo(d[7][0] * 50 * 2, d[7][1] * 50 * 2);
	//4-10
	pDC->MoveTo(d[3][0] * 50 * 2, d[3][1] * 50 * 2);
	pDC->LineTo(d[9][0] * 50 * 2, d[9][1] * 50 * 2);
	//5-6
	pDC->MoveTo(d[4][0] * 50 * 2, d[4][1] * 50 * 2);
	pDC->LineTo(d[5][0] * 50 * 2, d[5][1] * 50 * 2);
	//5-10
	pDC->MoveTo(d[4][0] * 50 * 2, d[4][1] * 50 * 2);
	pDC->LineTo(d[9][0] * 50 * 2, d[9][1] * 50 * 2);
	//6-7
	pDC->MoveTo(d[5][0] * 50 * 2, d[5][1] * 50 * 2);
	pDC->LineTo(d[6][0] * 50 * 2, d[6][1] * 50 * 2);
	//6-8
	pDC->MoveTo(d[5][0] * 50 * 2, d[5][1] * 50 * 2);
	pDC->LineTo(d[7][0] * 50 * 2, d[7][1] * 50 * 2);
	//6-9
	pDC->MoveTo(d[5][0] * 50 * 2, d[5][1] * 50 * 2);
	pDC->LineTo(d[8][0] * 50 * 2, d[8][1] * 50 * 2);
	//7-8
	pDC->MoveTo(d[6][0] * 50 * 2, d[6][1] * 50 * 2);
	pDC->LineTo(d[7][0] * 50 * 2, d[7][1] * 50 * 2);
	//8-9
	pDC->MoveTo(d[7][0] * 50 * 2, d[7][1] * 50 * 2);
	pDC->LineTo(d[8][0] * 50 * 2, d[8][1] * 50 * 2);
	//9-10
	pDC->MoveTo(d[8][0] * 50 * 2, d[8][1] * 50 * 2);
	pDC->LineTo(d[9][0] * 50 * 2, d[9][1] * 50 * 2);

}






