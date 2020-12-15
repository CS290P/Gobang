
// GobangView.h: CGobangView 类的接口
//

#pragma once
#include "Game.h"
class CGobangView : public CView
{
protected: // 仅从序列化创建
	CGobangView() noexcept;
	DECLARE_DYNCREATE(CGobangView)

// 特性
public:
	CGobangDoc* GetDocument() const;
	void fill(int x, int y,int player);
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
	virtual ~CGobangView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	Game* game;
};

#ifndef _DEBUG  // GobangView.cpp 中的调试版本
inline CGobangDoc* CGobangView::GetDocument() const
   { return reinterpret_cast<CGobangDoc*>(m_pDocument); }
#endif

