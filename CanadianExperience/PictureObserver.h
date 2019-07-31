/**
 * \file PictureObserver.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Observer base class for a picture.
 */

#pragma once

#include <memory>

class CPicture;


/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class CPictureObserver
{
public:
	virtual ~CPictureObserver();

	/// This function is called to update any observers
	virtual void UpdateObserver() = 0;

	/** Get the picture
	 * \returns The picture */
	std::shared_ptr<CPicture> GetPicture() { return mPicture; }

	/** Set the picture
	 * \param picture The new picture */
	void SetPicture(std::shared_ptr<CPicture> picture);

protected:
	CPictureObserver();

private:
	/// Picture we are observing
	std::shared_ptr<CPicture> mPicture;
};

