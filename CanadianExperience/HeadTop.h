/**
 * \file HeadTop.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Class that describes the top of the head
 */

#pragma once
#include "ImageDrawable.h"
#include "AnimChannelPosition.h"


/**
 * Class that describes the top of the head
 * Draws eyes and eyebrows on top of the head image
 */
class CHeadTop :
	public CImageDrawable
{
public:
	CHeadTop(const std::wstring & name, const std::wstring & filename);
	virtual ~CHeadTop();

	/** \brief Default constructor disabled */
	CHeadTop() = delete;
	/** \brief Copy constructor disabled */
	CHeadTop(const CHeadTop &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CHeadTop &) = delete;
	
	/** Gets if the object is movable
	 * \returns true because headtop is movable */
	virtual bool IsMovable() override { return true; }
	void Draw(Gdiplus::Graphics *graphics) override;

	/** Sets the left eye position
	 * \param pos The new left eye position */
	void SetEyeLeft(Gdiplus::Point pos) { mLeftEye = pos; }

	/** Sets the right eye position
	 * \param pos The new right eye position */
	void SetEyeRight(Gdiplus::Point pos) { mRightEye = pos; }

	virtual void GetKeyframe() override;
	virtual void SetKeyframe() override;
	virtual void DeleteKeyframe() override;
	virtual void SetTimeline(CTimeline * timeline) override;

private:
	Gdiplus::Point TransformPoint(Gdiplus::Point p);

	void DrawEye(Gdiplus::Graphics * graphics, int x);

	/// Position of the right eye
	Gdiplus::Point mRightEye = Gdiplus::Point(0, 0);

	/// Position of the left eye
	Gdiplus::Point mLeftEye = Gdiplus::Point(0, 0);

	/// The animation channel for animating the angle of this drawable
	CAnimChannelPosition mPositionChannel;
};

