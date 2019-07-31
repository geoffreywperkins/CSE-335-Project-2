/**
 * \file PictureFactory.cpp
 *
 * \author Geoffrey Witherington-Perkins
 */

#include "stdafx.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"

using namespace std;
using namespace Gdiplus;


/** Constructor */
CPictureFactory::CPictureFactory()
{
}


/** Destructor */
CPictureFactory::~CPictureFactory()
{
}


/** Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
	shared_ptr<CPicture> picture = make_shared<CPicture>();

	// Create the background and add it
	auto background = make_shared<CActor>(L"Background");
	background->SetClickable(false);
	background->SetPosition(Point(-100, 0));
	auto backgroundI =
		make_shared<CImageDrawable>(L"Background", L"images/Background.png");
	background->AddDrawable(backgroundI);
	background->SetRoot(backgroundI);
	picture->AddActor(background);

	// Create and add Harold
	CHaroldFactory factory1;
	auto harold = factory1.Create();

	// Create and add Sparty
	CSpartyFactory factory2;
	auto sparty = factory2.Create();

	// This is where Harold will start out.
	harold->SetPosition(Point(400, 500));

	picture->AddActor(harold);

	// This is where Sparty will start out.
	sparty->SetPosition(Point(800, 500));

	picture->AddActor(sparty);


	return picture;
}
