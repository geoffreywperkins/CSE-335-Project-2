/**
 * \file ImageDrawable.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Class that implements an drawable image
 */

#pragma once
#include <memory>
#include "Drawable.h"



/**
 * Class that implements an drawable image
 */
class CImageDrawable :
	public CDrawable
{
public:
	CImageDrawable(const std::wstring & name, const std::wstring & filename);
	virtual ~CImageDrawable();

	/** \brief Default constructor disabled */
	CImageDrawable() = delete;
	/** \brief Copy constructor disabled */
	CImageDrawable(const CImageDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CImageDrawable &) = delete;

	virtual void Draw(Gdiplus::Graphics *graphics);
	bool HitTest(Gdiplus::Point pos);

	/** Set the rotation angle in radians
	 * \param center The new center */
	void SetCenter(Gdiplus::Point center) { mCenter = center; }

	/** Get the drawable parentz
	* \returns The drawable parent */
	Gdiplus::Point GetCenter() const { return mCenter; }

protected:
	/// The image for this drawable
	std::unique_ptr<Gdiplus::Bitmap> mImage;

private:
	/// The center for this drawable
	Gdiplus::Point mCenter = Gdiplus::Point(0, 0);
};

