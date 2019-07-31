/**
 * \file AnimChannel.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Base class for animation channels
 */


#pragma once
#include <string>
#include <vector>
#include <memory>

class CTimeline;


/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class CAnimChannel
{
public:
	CAnimChannel();
	virtual ~CAnimChannel();

	/** \brief Copy constructor disabled */
	CAnimChannel(const CAnimChannel &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannel &) = delete;

	bool IsValid();
	void SetFrame(int currFrame);

	/** Get the animChannel name
	 * \returns AnimChannel name */
	std::wstring GetName() const { return mName; }

	/** Set the animChannel name
	 * \param name The new name of the channel */
	void SetName(std::wstring name) { mName = name; }

	/** Set the timeline
	 * \param timeline The timeline */
	void SetTimeline(CTimeline *timeline) { mTimeline = timeline; }

	/** Get the timeline
	 * \returns The timeline */
	CTimeline * GetTimeline() const { return mTimeline; }

	void DeleteKeyframe();

	/** Class that represents a keyframe */
	class Keyframe
	{
	public:
		/** \brief Default constructor disabled */
		Keyframe() = delete;
		/** \brief Copy constructor disabled */
		Keyframe(const Keyframe &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const Keyframe &) = delete;

		/** Get the Keyframe Frame
		 * \returns Keyframe Frame */
		int GetFrame() const { return mFrame; }

		/** Set the Keyframe Frame
		 * \param frame The new frame of the Keyframe */
		void SetFrame(int frame) { mFrame = frame; }

		/** Abstract function to create association btwn Keyframes and AnimChannels */
		virtual void UseAs1() = 0;

		/** Abstract function to create association btwn Keyframes and AnimChannels */
		virtual void UseAs2() = 0;

		/** Abstract function to create association btwn Keyframes and AnimChannels */
		virtual void UseOnly() = 0;

	protected:
		/** Constructor
		 * \param channel Channel we are associated with */
		Keyframe(CAnimChannel *channel) : mChannel(channel) {}

		int mFrame;	///< The frame the Keyframe is on

	private:
		/// The channel this keyframe is associated with
		CAnimChannel *mChannel;
	};

protected:
	void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);
	virtual void Tween(double t) = 0;	///< Abstract function for moving btwn keyframes

private:
	std::wstring mName;     ///< The channel name
	int mKeyframe1 = -1;    ///< The first keyframe
	int mKeyframe2 = -1;    ///< The second keyframe

	/// The timeline object
	CTimeline *mTimeline = nullptr;

	/// The collection of keyframes for this channel
	std::vector<std::shared_ptr<Keyframe>> mKeyframes;
};

