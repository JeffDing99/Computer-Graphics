
// huituView.h: ChuituView 类的接口
//

#pragma once


class ChuituView : public CView
{
protected: // 仅从序列化创建
	ChuituView() noexcept;
	DECLARE_DYNCREATE(ChuituView)

// 特性
public:
	ChuituDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~ChuituView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDDA();	
	
	afx_msg void OnMidpointline();
	
	afx_msg void OnMidpointcircle();
	afx_msg void OnBresenhamcircle();
	//afx_msg void OnMidpointellipse();
	afx_msg void OnBresenhamellipse();
	afx_msg void OnBresenhamline();
	afx_msg void OnPolygonscan();
	afx_msg void OnPolygonfloodfill4();
	void FloodFill4(int x, int y, int oldColor, int newColor);
	void FloodFill8(int x, int y, int oldColor, int newColor);
	afx_msg void OnPolygonfloodfill8();
	
	void Axis(CDC * pDC, CRect rect);
	afx_msg void OnClean();
	// 起点坐标x
	int B_x;
	// 起点坐标y
	int B_y;
	// 终点坐标x
	int E_x;
	// 终点坐标y
	int E_y;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void OnBresenhamline_1(int x0, int y0, int x1, int y1);
	// 判断状态1是Bresenhamline
	int state;
	void Bresenhamcircle_1(int x, int y, int r);
	afx_msg void Onpingyi2();
	afx_msg void Onxuanzhaun2();
	afx_msg void Oncuoqie2();
	afx_msg void Onbili2();
	afx_msg void Onduichen2();
	afx_msg void Oncs_line();
	afx_msg void Onwa_duo();
	afx_msg void Onpingyi3();
	afx_msg void Onxuanzhuan3();
	afx_msg void Onduichen3();
	afx_msg void Onbili3();
	afx_msg void Oncuoqie3();
	afx_msg void Onsanshitu();
	void cut_line(int x0, int x1, int y0, int y1);
	void CohenSutherland(CPoint p1, CPoint p2, CDC * pdc);
	// wxl为左侧裁剪边，wxr为右侧裁剪边，wyb为下侧裁剪边，wyt为上裁剪边。
	int wxl, wxr, wyb, wyt;
	unsigned int EnCode(CPoint point);
};

#ifndef _DEBUG  // huituView.cpp 中的调试版本
inline ChuituDoc* ChuituView::GetDocument() const
   { return reinterpret_cast<ChuituDoc*>(m_pDocument); }
#endif

