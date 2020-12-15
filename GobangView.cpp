
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

void CGobangView::OnDraw(CDC* /*pDC*/)
{
	CGobangDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	//获得窗口的设备描述表
	HDC hdc;
	hdc = ::GetDC(m_hWnd);

	//移动到线条的起点位置
	MoveToEx(hdc, 10, 10, NULL);

	//划线，
	LineTo(hdc, 800,rand()%800);


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
	this->Invalidate(1);
	CView::OnLButtonDown(nFlags, point);
}
