/**
 * \file HaroldFactory.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Factory class that builds the Harold character
 */

#pragma once
#include <memory>
#include "ActorFactory.h"

class CActor;

/**
 * Factory class that builds the Harold character
 */
class CHaroldFactory :
	public CActorFactory
{
public:
	CHaroldFactory();
	virtual ~CHaroldFactory();

	std::shared_ptr<CActor> Create();
};

