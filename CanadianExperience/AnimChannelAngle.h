/**
 * \file AnimChannelAngle.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Animation channel for angles.
 */

#pragma once
#include "AnimChannel.h"


/**
 * Animation channel for angles.
 */
class CAnimChannelAngle :
	public CAnimChannel
{
public:
	CAnimChannelAngle();
	virtual ~CAnimChannelAngle();

	/** \brief Copy constructor disabled */
	CAnimChannelAngle(const CAnimChannelAngle &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannelAngle &) = delete;

	void SetKeyframe(double angle);

	/** Get the animChannel angle
	 * \returns The animChannel angle */
	double GetAngle() const { return mAngle; }


	/**
	 * Class for rotational movement animations
	 */
	class KeyframeAngle : public Keyframe
	{
	public:
		/** Constructor
		 * \param channel The channel we are for
		 * \param angle The angle for the keyframe */
		KeyframeAngle(CAnimChannelAngle *channel, double angle) :
			Keyframe(channel), mChannel(channel), mAngle(angle) {}

		/** \brief Default constructor disabled */
		KeyframeAngle() = delete;
		/** \brief Copy constructor disabled */
		KeyframeAngle(const KeyframeAngle &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const KeyframeAngle &) = delete;

		/** Get the angle of the Keyframe
		 * \returns The KeyframeAngle's angle */
		double GetAngle() const { return mAngle; }

		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mAngle = mAngle; }

	private:
		double mAngle;	///< The angle of the keyframe

		/// The channel this keyframe is associated with
		CAnimChannelAngle *mChannel;
	};


protected:
	virtual void Tween(double t);

private:
	double mAngle = 0;	///< The angle of the channel at the current time

	/// The first angle keyframe
	KeyframeAngle *mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframeAngle *mKeyframe2 = nullptr;
};

