// Fill out your copyright notice in the Description page of Project Settings.

#include "AIExtensionPrivatePCH.h"

#include "Task.h"
#include "TaskManagerComponent.h"

#include "TaskOwnerInterface.h"


// This function does not need to be modified.
UTaskOwnerInterface::UTaskOwnerInterface(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

const bool ITaskOwnerInterface::AddChildren(UTask* NewChildren)
{
    if (UTaskManagerComponent* comp = GetTaskOwnerComponent()) {
        return comp->AddChildren(NewChildren);
    }
    return false;
}

const bool ITaskOwnerInterface::RemoveChildren(UTask* Children)
{
    if (UTaskManagerComponent* comp = GetTaskOwnerComponent()) {
        return comp->RemoveChildren(Children);
    }
    return false;
}
