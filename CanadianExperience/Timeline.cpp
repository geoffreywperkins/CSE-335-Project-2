/**
 * \file Timeline.cpp
 *
 * \author Geoffrey Witherington-Perkins
 */

#include "stdafx.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"


CTimeline::CTimeline()
{
}


CTimeline::~CTimeline()
{
}


/**
 * Creates the association between Channel and Timeline
 * \param channel The channel being added to the timeline
 */
void CTimeline::AddChannel(CAnimChannel * channel)
{
	channel->SetTimeline(this);
	mChannels.push_back(channel);
}


/** Sets the current time
 *
 * Ensures all of the channels are
 * valid for that point in time.
 *
 * \param t The current time
 */
void CTimeline::SetCurrentTime(double t)
{
	// Set the time
	mCurrentTime = t;

	for (auto channel : mChannels)
	{
		channel->SetFrame(GetCurrentFrame());
	}
}
