/**
 * \file AnimChannelPosition.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Animation channel for Positions.
 */

#pragma once
#include "AnimChannel.h"


/**
 * Animation channel for Positions.
 */
class CAnimChannelPosition :
	public CAnimChannel
{
public:
	CAnimChannelPosition();
	virtual ~CAnimChannelPosition();

	/** \brief Copy constructor disabled */
	CAnimChannelPosition(const CAnimChannelPosition &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannelPosition &) = delete;

	void SetKeyframe(Gdiplus::Point position);

	/** Get the animChannel Position
	 * \returns The animChannel Position */
	Gdiplus::Point GetPosition() const { return mPosition; }


	/**
	 * Class for positional movement animations
	 */
	class KeyframePosition : public Keyframe
	{
	public:
		/** Constructor
		 * \param channel The channel we are for
		 * \param position The Position for the keyframe */
		KeyframePosition(CAnimChannelPosition *channel, Gdiplus::Point position) :
			Keyframe(channel), mChannel(channel), mPosition(position) {}

		/** \brief Default constructor disabled */
		KeyframePosition() = delete;
		/** \brief Copy constructor disabled */
		KeyframePosition(const KeyframePosition &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const KeyframePosition &) = delete;

		/** Get the position of the Keyframe
		 * \returns The KeyframeAngle's position */
		Gdiplus::Point GetPosition() const { return mPosition; }

		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** Use this keyframe as the Position */
		virtual void UseOnly() override { mChannel->mPosition = mPosition; }

	private:
		Gdiplus::Point mPosition;	///< The position at this Keyframe

		/// The channel this keyframe is associated with
		CAnimChannelPosition *mChannel;
	};


protected:
	virtual void Tween(double t);

private:
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);	///< The position at this keyframe

	/// The first Position keyframe
	KeyframePosition *mKeyframe1 = nullptr;

	/// The second Position keyframe
	KeyframePosition *mKeyframe2 = nullptr;
};


