/**
 * \file SpartyFactory.h
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
class CSpartyFactory :
	public CActorFactory
{
public:
	CSpartyFactory();
	virtual ~CSpartyFactory();

	std::shared_ptr<CActor> Create();
};

