#include "stdafx.h"
#include "HeadTop.h"
#include "Timeline.h"


using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;


/** Constructor
 * \param name The name of the headTop
 * \param filename The filename of the picture */
CHeadTop::CHeadTop(const std::wstring & name, const std::wstring & filename) :
	CImageDrawable(name, filename)
{
}


/** Destructor */
CHeadTop::~CHeadTop()
{
}


/**
 * Handles the drawing of the head and eyes
 * \param graphics The graphics to be drawn onto
 */
void CHeadTop::Draw(Gdiplus::Graphics * graphics)
{
	CImageDrawable::Draw(graphics);

	DrawEye(graphics, mLeftEye.X); // 30
	DrawEye(graphics, mRightEye.X); //80
}


/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
	// Make p relative to the image center
	p = p - GetCenter();

	// Rotate as needed and offset
	return RotatePoint(p, mPlacedR) + mPlacedPosition;
}


/**
 * Draws one eye and eyebrow
 * \param graphics the graphics to be drawn onto
 * \param x The x coordinate of the eye & eyebrow
 */
void CHeadTop::DrawEye(Gdiplus::Graphics *graphics, int x)
{
	int y = mRightEye.Y;

	Point p1 = TransformPoint(Point(x-10, y));
	Point p2 = TransformPoint(Point(x+10, y));

	Pen eyebrowPen(Color::Black, 2);
	graphics->DrawLine(&eyebrowPen, p1, p2);

	float wid = 15.0f;
	float hit = 20.0f;

	p1 = TransformPoint(Point(x, y + 15));	

	SolidBrush brush(Color::Black);
	auto state = graphics->Save();
	graphics->TranslateTransform(REAL(p1.X), REAL(p1.Y));
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);
	graphics->Restore(state);
}


/** brief Get a keyframe for an actor.
*/
void CHeadTop::GetKeyframe()
{
	CDrawable::GetKeyframe();
	if (mPositionChannel.IsValid())
		SetPosition(mPositionChannel.GetPosition());
}

/** Set the keyframe based on the current status.
*/
void CHeadTop::SetKeyframe()
{
	CDrawable::SetKeyframe();

	mPositionChannel.SetKeyframe(GetPosition());
}


/**
 * Deleting the keyframe at the current frame (if there is one)
 * Extends CDrawable::DeleteKeyframe so it looks in CHeadTop's PositionChannel
 */
void CHeadTop::DeleteKeyframe()
{
	CDrawable::DeleteKeyframe();
	mPositionChannel.DeleteKeyframe();
}


/**
 * Creates the association btwn the timeline and HeadTop's animationChannel
 * \param timeline The timeline to make the association with
 */
void CHeadTop::SetTimeline(CTimeline * timeline)
{
	CDrawable::SetTimeline(timeline);
	timeline->AddChannel(&mPositionChannel);
}
