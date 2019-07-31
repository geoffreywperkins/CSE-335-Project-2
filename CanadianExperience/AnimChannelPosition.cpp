/**
 * \file AnimChannelPosition.cpp
 *
 * \author Geoffrey Witherington-Perkins
 */

#include "stdafx.h"
#include <memory>
#include "AnimChannelPosition.h"

using namespace std;

CAnimChannelPosition::CAnimChannelPosition()
{
}


CAnimChannelPosition::~CAnimChannelPosition()
{
}

/**
* Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param position Position for the keyframe.
*/
void CAnimChannelPosition::SetKeyframe(Gdiplus::Point position)
{
	// Create a keyframe of the appropriate type
	// Telling it this channel and the Position
	shared_ptr<KeyframePosition> keyframe =
		make_shared<KeyframePosition>(this, position);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}


/**
 * Compute an Position that is an interpolation between two keyframes
 *
 * This function is called after Use1 and Use2, so we have pointers to
 * to valid keyframes of the type KeyframePosition. This function does the
 * tweening.
 * \param t A t value. t=0 means keyframe1, t=1 means keyframe2. Other values
 * interpolate between.
 */
void CAnimChannelPosition::Tween(double t)
{
	Gdiplus::Point a = mKeyframe1->GetPosition();
	Gdiplus::Point b = mKeyframe2->GetPosition();

	mPosition = Gdiplus::Point(int(a.X + t * (b.X - a.X)), int(a.Y + t * (b.Y - a.Y)));;
}
