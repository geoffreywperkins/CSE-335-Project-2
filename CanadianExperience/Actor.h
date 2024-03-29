/**
 * \file Actor.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Class for actors in our drawings.
 */

#pragma once
#include <string>
#include <vector>
#include "Drawable.h"
#include "AnimChannelPosition.h"

class CPicture;


 /**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class CActor
{
public:
	CActor(const std::wstring &name);

	/** Default constructor disabled */
	CActor() = delete;
	/** Copy constructor disabled */
	CActor(const CActor &) = delete;
	/** Assignment operator disabled */
	void operator=(const CActor &) = delete;

	virtual ~CActor();

	void SetRoot(std::shared_ptr<CDrawable> root);
	void Draw(Gdiplus::Graphics *graphics);
	std::shared_ptr<CDrawable> HitTest(Gdiplus::Point pos);
	void AddDrawable(std::shared_ptr<CDrawable> drawable);

	void SetKeyframe();
	void GetKeyframe();
	void DeleteKeyframe();

	/** Get the actor name
	 * \returns Actor name */
	std::wstring GetName() const { return mName; }

	/** The actor position
	* \returns The actor position as a point */
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** The actor position
	* \param pos The new actor position */
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** Actor is enabled
	* \returns enabled status */
	bool IsEnabled() const { return mEnabled; }

	/** Set Actor Enabled
	* \param enabled New enabled status */
	void SetEnabled(bool enabled) { mEnabled = enabled; }

	/** Actor is clickable
	* \returns true if actor is clickable */
	bool IsClickable() const { return mClickable; }

	/** Actor clickable
	* \param clickable New clickable status */
	void SetClickable(bool clickable) { mClickable = clickable; }

	/** Get the actor picture
	 * \returns Actor picture */
	CPicture * GetPicture() { return mPicture; }

	/** Sets the actor picture
	* \param picture The new actor picture */
	void SetPicture(CPicture * picture);

	/** Get the actor position channel
	 * \returns Actor position channel */
	CAnimChannelPosition *GetPositionChannel() { return &mPositionChannel; }

private:
	/// Name of the drawable
	std::wstring mName;

	/// True if drawable is enabled
	bool mEnabled = true;

	/// The position of the drawable
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

	/// True if drawable is clickable
	bool mClickable = true;

	/// The root drawable
	std::shared_ptr<CDrawable> mRoot;

	/// The drawables in drawing order
	std::vector<std::shared_ptr<CDrawable>> mDrawablesInOrder;

	/// The picture this actor is a part of
	CPicture *mPicture = nullptr;

	/// The animation channel for animating the angle of this drawable
	CAnimChannelPosition mPositionChannel;
};