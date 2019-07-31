/**
 * \file ActorFactory.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Abstract base class for actor factories.
 */

#pragma once
#include <memory>

class CActor;


/**
 * Abstract base class for actor factories.
 */
class CActorFactory
{
public:
	CActorFactory();
	virtual ~CActorFactory();

	/** Creates an actor. Pure virtual
	 * \returns an actor */
	virtual std::shared_ptr<CActor> Create() = 0;
};

