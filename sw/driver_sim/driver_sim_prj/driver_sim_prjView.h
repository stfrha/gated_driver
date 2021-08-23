// driver_sim_prjView.h : interface of the Cdriver_sim_prjView class
//


#pragma once


class Cdriver_sim_prjView : public CScrollView
{
protected: // create from serialization only
	Cdriver_sim_prjView();
	DECLARE_DYNCREATE(Cdriver_sim_prjView)

// Attributes
public:
	Cdriver_sim_prjDoc* GetDocument() const;

// Operations
public:
   void  StartScroll( void );
   UINT  m_timer;

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cdriver_sim_prjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnTimer(UINT nIDEvent);
};

#ifndef _DEBUG  // debug version in driver_sim_prjView.cpp
inline Cdriver_sim_prjDoc* Cdriver_sim_prjView::GetDocument() const
   { return reinterpret_cast<Cdriver_sim_prjDoc*>(m_pDocument); }
#endif

