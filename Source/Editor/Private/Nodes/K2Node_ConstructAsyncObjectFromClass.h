// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "EdGraphSchema_K2.h"
#include "K2Node.h"
#include "K2Node_AddDelegate.h"
#include "K2Node_CreateDelegate.h"
#include "K2Node_Self.h"
#include "K2Node_CustomEvent.h"
#include "K2Node_TemporaryVariable.h"
#include "K2Node_ConstructAsyncObjectFromClass.generated.h"

class FBlueprintActionDatabaseRegistrar;
class UEdGraph;

UCLASS(abstract)
class AIEXTENSIONEDITOR_API UK2Node_ConstructAsyncObjectFromClass : public UK2Node
{
	GENERATED_UCLASS_BODY()

	//~ Begin UEdGraphNode Interface.
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	virtual FText GetTooltipText() const override;
	virtual bool HasExternalDependencies(TArray<class UStruct*>* OptionalOutput) const override;
	virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin);
	virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;
	//~ End UEdGraphNode Interface.

	//~ Begin UK2Node Interface
	virtual bool IsNodeSafeToIgnore() const override { return true; }
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual void GetNodeAttributes( TArray<TKeyValuePair<FString, FString>>& OutNodeAttributes ) const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	//~ End UK2Node Interface

	/** Create new pins to show properties on archetype */
	void CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins = nullptr);

	/** See if this is a spawn variable pin, or a 'default' pin */
	virtual bool IsSpawnVarPin(UEdGraphPin* Pin);

	/** Get the then output pin */
	UEdGraphPin* GetThenPin() const;
	/** Get the blueprint input pin */	
	UEdGraphPin* GetClassPin(const TArray<UEdGraphPin*>* InPinsToSearch=NULL) const;
	/** Get the world context input pin, can return NULL */
	UEdGraphPin* GetWorldContextPin(bool bChecked = true) const;
	/** Get the result output pin */
	UEdGraphPin* GetResultPin() const;
	/** Get the result input pin */
	UEdGraphPin* GetOwnerPin() const;

	/** Get the class that we are going to spawn, if it's defined as default value */
	UClass* GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch=NULL) const;

	/** Returns if the node uses World Object Context input */
	virtual bool UseWorldContext() const;

	/** Returns if the node uses Owner input */
	virtual bool UseOwner() const { return true; }

protected:
	/** Gets the default node title when no class is selected */
	virtual FText GetBaseNodeTitle() const;
	/** Gets the node title when a class has been selected. */
	virtual FText GetNodeTitleFormat() const;
	/** Gets base class to use for the 'class' pin.  UObject by default. */
	virtual UClass* GetClassPinBaseClass() const;

	/**
	 * Takes the specified "MutatablePin" and sets its 'PinToolTip' field (according
	 * to the specified description)
	 * 
	 * @param   MutatablePin	The pin you want to set tool-tip text on
	 * @param   PinDescription	A string describing the pin's purpose
	 */
	void SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const;

	/** Refresh pins when class was changed */
	void OnClassPinChanged();

    struct AIEXTENSIONEDITOR_API FHelper
    {
        static FString WorldContextPinName;
        static FString ClassPinName;
        static FString OwnerPinName;

        struct FOutputPinAndLocalVariable
        {
            UEdGraphPin* OutputPin;
            UK2Node_TemporaryVariable* TempVar;

            FOutputPinAndLocalVariable(UEdGraphPin* Pin, UK2Node_TemporaryVariable* Var) : OutputPin(Pin), TempVar(Var) {}
        };

        static bool ValidDataPin(const UEdGraphPin* Pin, EEdGraphPinDirection Direction, const UEdGraphSchema_K2* Schema);
        static bool CreateDelegateForNewFunction(UEdGraphPin* DelegateInputPin, FName FunctionName, UK2Node* CurrentNode, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext);
        static bool CopyEventSignature(UK2Node_CustomEvent* CENode, UFunction* Function, const UEdGraphSchema_K2* Schema);
        static bool HandleDelegateImplementation(
            UMulticastDelegateProperty* CurrentProperty, const TArray<FHelper::FOutputPinAndLocalVariable>& VariableOutputs,
            UEdGraphPin* ProxyObjectPin, UEdGraphPin*& InOutLastThenPin,
            UK2Node* CurrentNode, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext);
        static bool HandleDelegateBindImplementation(
            UMulticastDelegateProperty* CurrentProperty,
            UEdGraphPin* ProxyObjectPin, UEdGraphPin*& InOutLastThenPin,
            UK2Node* CurrentNode, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext);
    };

	/** Tooltip text for this node. */
	FText NodeTooltip;

private:
	/** Constructing FText strings can be costly, so we cache the node's title */
	FNodeTextCache CachedNodeTitle;
};
