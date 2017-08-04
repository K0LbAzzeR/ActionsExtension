// Copyright 2015-2016 Piperift. All Rights Reserved.

#include "AIExtensionPrivatePCH.h"
#include "FactionAgentInterface.h"



//----------------------------------------------------------------------//
// UGenericTeamAgentInterface
//----------------------------------------------------------------------//
UFactionAgentInterface::UFactionAgentInterface(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{}

FFaction IFactionAgentInterface::GetFaction() const
{
    return EventGetFaction();
}

void IFactionAgentInterface::SetFaction(const FFaction & Faction)
{
    EventSetFaction(Faction);
}
