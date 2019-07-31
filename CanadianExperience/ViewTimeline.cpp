/**
 * \file ViewTimeline.cpp
 *
 * \author Geoffrey Witherington-Perkins
 */


#include "stdafx.h"
#include <sstream>
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"

#include "MainFrm.h"
#include "Timeline.h"
#include "Picture.h"
#include "Actor.h"

using namespace std;
using namespace Gdiplus;

IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 10;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;


/** Constructor */
CViewTimeline::CViewTimeline()
{
	mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
	assert(mPointer->GetLastStatus() == Ok);
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}


/**
 * Force an update of this window when the picture changes.
 */
void CViewTimeline::UpdateObserver()
{
	Invalidate();
	UpdateWindow();
}


/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
	// Get the timeline
	CTimeline *timeline = GetPicture()->GetTimeline();

	// Set the scroll system correctly
	CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight,
		WindowHeight);
	SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

	// Line used to draw the tick marks
	Gdiplus::Pen tickpen(Color::Black, 1);

	// Draw the timeline
	for (int tickNum = 0; tickNum < timeline->GetNumFrames(); tickNum++)
	{
		bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;
		
		// determining the tick placement coordinates
		int x1 = BorderLeft + TickSpacing * tickNum;
		int x2 = x1;
		int y1 = BorderTop;
		int y2 = BorderTop + TickShort;

		if (onSecond) 
		{
			// setting y2 if it's a long tick
			y2 = BorderTop + TickLong;

			// Convert the tick number to seconds in a string
			std::wstringstream str;
			str << tickNum / timeline->GetFrameRate();
			std::wstring wstr = str.str();

			RectF size;
			PointF origin(0.0f, 0.0f);
			Gdiplus::Font font(L"Times new roman", 12);
			graphics.MeasureString(wstr.c_str(), wstr.size(),
				&font, origin, &size);

			// Drawing the numbers under the long ticks now
			SolidBrush brush(Color(0, 0, 0));
			graphics.DrawString(wstr.c_str(),  // String to draw
				-1,         // String length, -1 means it figures it out 
				&font,      // The font to use
				PointF(x2 - size.Width / 2, y2),   // Where to draw
				&brush);    // The brush to draw the text with
		}

		// Drawing the ticks
		graphics.DrawLine(&tickpen, x1, y1, x2, y2);
	}

	auto pointerImage = mPointer.get();
	graphics.DrawImage(pointerImage, 
		BorderLeft + timeline->GetCurrentFrame() * TickSpacing - pointerImage->GetWidth() / 2,
		BorderTop);

	CRect rect;
	GetClientRect(&rect);
	int hit = rect.Height();
	int wid = rect.Width();
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle a press of the keyframe set button on the toolbar
*/
void CViewTimeline::OnEditSetkeyframe()
{
	for (auto actor : *GetPicture())
	{
		actor->SetKeyframe();
	}
}


/** Handle the Edit>Delete Keyframe menu option */
void CViewTimeline::OnEditDeletekeyframe()
{
	for (auto actor : *GetPicture())
	{
		actor->DeleteKeyframe();
	}
	GetPicture()->SetAnimationTime(GetPicture()->GetTimeline()->GetCurrentTime());
}


/**
 * Changes the pointer position when the pointer gets dragged around
 * \param nFlags The flags
 * \param point The coordinates of the mouse
 */
void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Convert mouse coordinates to logical coordinates
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	int x = point.x;

	// Get the timeline
	CTimeline *timeline = GetPicture()->GetTimeline();
	int pointerX = (int)(timeline->GetCurrentTime() *
		timeline->GetFrameRate() * TickSpacing + BorderLeft);

	mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
		x <= pointerX + (int)mPointer->GetWidth() / 2;

	__super::OnLButtonDown(nFlags, point);
}


/**
 * Moves the pointer around when dragging the pointer
 * \param nFlags The flags
 * \param point The coordinates of the mouse
 */
void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
{
	// Convert mouse coordinates to logical coordinates
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	if (mMovingPointer)
	{
		// If an item is being moved, we only continue to 
	// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			CTimeline *timeline = GetPicture()->GetTimeline();
			double pointerTime = (double(point.x) - BorderLeft) / timeline->GetFrameRate() / TickSpacing;

			// make sure it can't go above the duration or below 0
			pointerTime = min(pointerTime, timeline->GetDuration() - 1.0 / timeline->GetFrameRate());
			pointerTime = max(pointerTime, 0.0);

			GetPicture()->SetAnimationTime(pointerTime);
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mMovingPointer = false;
		}
	}

	__super::OnMouseMove(nFlags, point);
}



// Doxygen sometimes gets confused by these message 
// maps, since they look like functions. I've found
// it helps to move them to the end of the file.
BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

