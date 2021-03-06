﻿
// GobangView.cpp: CGobangView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Gobang.h"
#endif

#include "GobangDoc.h"
#include "GobangView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGobangView

IMPLEMENT_DYNCREATE(CGobangView, CView)

BEGIN_MESSAGE_MAP(CGobangView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CGobangView 构造/析构

CGobangView::CGobangView() noexcept
{
	game = new Game(1);
	// TODO: 在此处添加构造代码

}

CGobangView::~CGobangView()
{
}

BOOL CGobangView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGobangView 绘图
void CGobangView::fill(int x, int y, int player,int end) {
	CPoint pt;
	pt.x = x;
	pt.y = y;
	CClientDC ClientDC(this);
	CBrush brush, * oldbrush;
	if (end == 1) {
		brush.CreateSolidBrush(RGB(200, 50, 50));
		oldbrush = ClientDC.SelectObject(&brush);
		ClientDC.Ellipse(pt.x - 25, pt.y - 25, pt.x + 25, pt.y + 25);
		ClientDC.SelectObject(oldbrush);
		return;
	}
	else {
		if (player > 0) {
			brush.CreateSolidBrush(RGB(0, 0, 0));
		}
		else {
			brush.CreateSolidBrush(RGB(200, 200, 200));
		}
		oldbrush = ClientDC.SelectObject(&brush);
		ClientDC.Ellipse(pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
		ClientDC.SelectObject(oldbrush);
	}


}
void CGobangView::OnDraw(CDC* pDC)
{
	CGobangDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//获得窗口的设备描述表
	HDC hdc;
	hdc = ::GetDC(m_hWnd);


	for (int i = 1; i <= 15; i++) {
		//移动到线条的起点位置
		MoveToEx(hdc, 20, i * 50, NULL);
		//划线，
		LineTo(hdc, 770, i * 50);
	}
	for (int i = 1; i <= 15; i++) {
		//移动到线条的起点位置
		MoveToEx(hdc, i * 50, 20, NULL);
		//划线，
		LineTo(hdc, i * 50, 770);
	}
	int maxi = 0, maxj = 0;	
	int max = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (game->checkerboard[i][j] > max) {
				maxi = i;
				maxj = j;
				max = game->checkerboard[i][j];
			}
		}
	}
	if (max != 0) {
		//fill((maxi + 1) * 50, (maxj + 1) * 50, game->checkerboard[maxi][maxj] * game->humanFirst,1);
	}
	int mini = 0, minj = 0;
	int min = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (game->checkerboard[i][j] < min) {
				mini = i;
				minj = j;
				min = game->checkerboard[i][j];
			}
		}
	}
	if (min != 0) {
		fill((mini + 1) * 50, (minj + 1) * 50, game->checkerboard[mini][minj] * game->humanFirst, 1);
	}





	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (game->checkerboard[i][j] * game->humanFirst != 0) {
				fill((i + 1) * 50, (j + 1) * 50, game->checkerboard[i][j] * game->humanFirst);
			}
		}
	}
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGobangView 打印

BOOL CGobangView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGobangView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGobangView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGobangView 诊断

#ifdef _DEBUG
void CGobangView::AssertValid() const
{
	CView::AssertValid();
}

void CGobangView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGobangDoc* CGobangView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGobangDoc)));
	return (CGobangDoc*)m_pDocument;
}
#endif //_DEBUG


// CGobangView 消息处理程序


void CGobangView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//game->humanPlay();
	// 0,0 50,50  
	int hunmanSuccess = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int beginx = (i + 1) * 50 - 25;
			int endx = (i + 1) * 50 + 25;
			int beginy = (j + 1) * 50 - 25;
			int endy = (j + 1) * 50 + 25;
			if (point.x > beginx && point.x <= endx && point.y > beginy && point.y <= endy) {
				hunmanSuccess=game->humanPlay(i, j);
			}
		}
	}
	if (hunmanSuccess) {
		game->aiPlay();
	}
	this->Invalidate(1);
	CView::OnLButtonDown(nFlags, point);
}
