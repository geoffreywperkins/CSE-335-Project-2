/**
 * \file SpartyFactory.cpp
 *
 * \author Geoffrey Witherington-Perkins
 */

#include "stdafx.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"

using namespace std;
using namespace Gdiplus;


/** Constructor */
CSpartyFactory::CSpartyFactory()
{
}


/** Destructor */
CSpartyFactory::~CSpartyFactory()
{
}


/** This is a concrete factory method that creates our Harold actor.
* \returns Pointer to an actor object.
*/
std::shared_ptr<CActor> CSpartyFactory::Create()
{
	shared_ptr<CActor> actor = make_shared<CActor>(L"Harold");

	auto shirt = make_shared<CImageDrawable>(L"Torso", L"images/sparty_torso.png");
	shirt->SetCenter(Point(44, 138));
	shirt->SetPosition(Point(0, -114));
	actor->SetRoot(shirt);

	auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/sparty_lleg.png");
	lleg->SetCenter(Point(11, 9));
	lleg->SetPosition(Point(27, 0));
	shirt->AddChild(lleg);

	auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/sparty_rleg.png");
	rleg->SetCenter(Point(39, 9));
	rleg->SetPosition(Point(0, 0));
	shirt->AddChild(rleg);

	auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/sparty_lhead.png");
	headb->SetCenter(Point(44, 31));
	headb->SetPosition(Point(20, -100));
	shirt->AddChild(headb);

	auto headt = make_shared<CHeadTop>(L"Head Top", L"images/sparty_head.png");
	headt->SetCenter(Point(55, 109));
	headt->SetPosition(Point(14, -60));
	headt->SetEyeLeft(Point(30, 100));
	headt->SetEyeRight(Point(78, 100));
	headb->AddChild(headt);

	auto rarm = make_shared<CImageDrawable>(L"Right Arm", L"images/sparty_rarm.png");
	rarm->SetCenter(Point(100, 20));
	rarm->SetPosition(Point(-10, -120));
	shirt->AddChild(rarm);

	auto larm = make_shared<CImageDrawable>(L"Right Arm", L"images/sparty_larm.png");
	larm->SetCenter(Point(30, 10));
	larm->SetPosition(Point(90, -130));
	shirt->AddChild(larm);


	actor->AddDrawable(rleg);
	actor->AddDrawable(lleg);
	actor->AddDrawable(shirt);
	actor->AddDrawable(larm);
	actor->AddDrawable(rarm);
	actor->AddDrawable(headb);
	actor->AddDrawable(headt);

	return actor;
}