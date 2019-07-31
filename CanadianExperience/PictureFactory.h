/**
 * \file PictureFactory.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * A factory class that builds our picture.
 */

#pragma once
#include <memory>
#include "Picture.h"


/**
 * A factory class that builds our picture.
 */
class CPictureFactory
{
public:
	/** \brief Copy constructor disabled */
	CPictureFactory(const CPictureFactory &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPictureFactory &) = delete;


	CPictureFactory();
	virtual ~CPictureFactory();
	std::shared_ptr<CPicture> Create();
};

