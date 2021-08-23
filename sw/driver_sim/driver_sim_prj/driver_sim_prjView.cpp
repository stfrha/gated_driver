// driver_sim_prjView.cpp : implementation of the Cdriver_sim_prjView class
//

#include "stdafx.h"
#include "driver_sim_prj.h"

#include "driver_sim_prjDoc.h"
#include "driver_sim_prjView.h"
#include ".\driver_sim_prjview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SCREEN_OFFSET   CPoint(25, 25)
#define LED_DIAMETER    20


// Cdriver_sim_prjView

IMPLEMENT_DYNCREATE(Cdriver_sim_prjView, CScrollView)

BEGIN_MESSAGE_MAP(Cdriver_sim_prjView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
   ON_WM_TIMER()
END_MESSAGE_MAP()

// Cdriver_sim_prjView construction/destruction

Cdriver_sim_prjView::Cdriver_sim_prjView()
{
	// TODO: add construction code here

}

Cdriver_sim_prjView::~Cdriver_sim_prjView()
{
}

BOOL Cdriver_sim_prjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// Cdriver_sim_prjView drawing

void Cdriver_sim_prjView::OnDraw(CDC* pDC)
{
	Cdriver_sim_prjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
   CBrush* pTempBrush = NULL;
   CBrush OrigBrush;

   int x, y;
   unsigned char c;
   CBrush darkBrush;
   darkBrush.CreateSolidBrush(RGB(255,255,255));

   CBrush lightBrush;
   lightBrush.CreateSolidBrush(RGB(255,0,0));

   pTempBrush = (CBrush*)pDC->SelectObject(&darkBrush);
   // Save original brush.
   OrigBrush.FromHandle((HBRUSH)pTempBrush);

   for (y=0 ; y<59 ; y++) {
      c = pDoc->GetScreenByte(y);
      for (x=0 ; x<8 ; x++) {
         if (c & 1<<(7-x)) {
            pDC->SelectObject(&lightBrush);
         } else {
            pDC->SelectObject(&darkBrush);
         }
         pDC->Ellipse((CRect(SCREEN_OFFSET+CPoint(y*LED_DIAMETER,x*LED_DIAMETER),
         SCREEN_OFFSET+CPoint(y*LED_DIAMETER+LED_DIAMETER,x*LED_DIAMETER+LED_DIAMETER))));
      }
   }
   // Reselect original brush into device context.
   pDC->SelectObject(&OrigBrush);

}

void Cdriver_sim_prjView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// Cdriver_sim_prjView printing

BOOL Cdriver_sim_prjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cdriver_sim_prjView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cdriver_sim_prjView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Cdriver_sim_prjView diagnostics

#ifdef _DEBUG
void Cdriver_sim_prjView::AssertValid() const
{
	CScrollView::AssertValid();
}

void Cdriver_sim_prjView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

Cdriver_sim_prjDoc* Cdriver_sim_prjView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdriver_sim_prjDoc)));
	return (Cdriver_sim_prjDoc*)m_pDocument;
}
#endif //_DEBUG


// Cdriver_sim_prjView message handlers

void Cdriver_sim_prjView::OnTimer(UINT nIDEvent)
{
	Cdriver_sim_prjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

   if (!pDoc->NextScrollPos()) {
      KillTimer(m_timer);
      pDoc->NextMessage();
   }
}


