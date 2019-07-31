/**
 * \file Drawable.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Abstract base class for drawable elements of our picture
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "AnimChannelAngle.h"

class CActor;
class CTimeline;


/**
 * Abstract base class for drawable elements of our picture
 */
class CDrawable
{
public:
	virtual ~CDrawable();

	/** Default constructor disabled */
	CDrawable() = delete;
	/** Copy constructor disabled */
	CDrawable(const CDrawable &) = delete;
	/** Assignment operator disabled */
	void operator=(const CDrawable &) = delete;

	void SetActor(CActor *actor);
	virtual void SetTimeline(CTimeline * timeline);
	virtual void DeleteKeyframe();


	/** Draws the drawable
	 * \param graphics The graphics to be drawn on */
	virtual void Draw(Gdiplus::Graphics *graphics) = 0;

	void Place(Gdiplus::Point offset, double rotate);

	void AddChild(std::shared_ptr<CDrawable> child);

	/** Tests if pos is on top of the image
	 * \param pos The position to be tested 
	 * \returns true if hit, false if not */
	virtual bool HitTest(Gdiplus::Point pos) = 0;

	/** Gets movable state of drawable
	 * \returns true if independently movable*/
	virtual bool IsMovable() { return false; }
	void Move(Gdiplus::Point delta);

	/** Set the drawable position
	 * \param pos The new drawable position*/
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** Get the drawable position
	 * \returns The drawable position*/
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** Set the rotation angle in radians
	 * \param r The new rotation angle in radians*/
	void SetRotation(double r) { mRotation = r; }

	/** Get the rotation angle in radians
	 * \returns The rotation angle in radians*/
	double GetRotation() const { return mRotation; }

	/** Get the drawable name
	 * \returns The drawable name */
	std::wstring GetName() const { return mName; }

	/** Set the rotation angle in radians
	 * \param parent The new rotation angle in radians*/
	void SetParent(CDrawable * parent) { mParent = parent; }

	/** Get the drawable parent
	 * \returns The drawable parent */
	CDrawable * GetParent() const { return mParent; }

	/** The angle animation channel
	 * \returns Pointer to animation channel */
	CAnimChannelAngle *GetAngleChannel() { return &mChannel; }

	virtual void SetKeyframe();
	virtual void GetKeyframe();


protected:
	CDrawable(const std::wstring &name);
	Gdiplus::Point RotatePoint(Gdiplus::Point point, double angle);

	/// The actual postion in the drawing
	Gdiplus::Point mPlacedPosition = Gdiplus::Point(0, 0);

	/// The actual rotation in the drawing
	double mPlacedR = 0;

private:
	/// The drawable name
	std::wstring mName;

	/// The position of this drawable relative to its parent
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

	/// The rotation of this drawable relative to its parent
	double mRotation = 0;

	/// The actor using this drawable
	CActor *mActor = nullptr;

	/// The parent of this drawable
	CDrawable *mParent = nullptr;

	/// The children of this drawable
	std::vector<std::shared_ptr<CDrawable>> mChildren;

	/// The animation channel for animating the angle of this drawable
	CAnimChannelAngle mChannel;
};

