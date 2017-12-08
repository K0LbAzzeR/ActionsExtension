// Copyright 2015-2017 Piperift. All Rights Reserved.
#pragma once

#include "UnrealEd.h"

#include "PropertyEditorModule.h"
#include "IAssetTools.h"
#include "UtilityTree/IUtilityTreeEditor.h"

#include "UtilityTree.h"
 
DECLARE_LOG_CATEGORY_EXTERN(LogUtilityEd, All, All)
 
class FUtilityTreeEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // Get Quest Extension Editor module instance
    FORCEINLINE static FUtilityTreeEditorModule& GetInstance() {
        return FModuleManager::LoadModuleChecked<FUtilityTreeEditorModule>("UtilityTreeEditor");
    }

private:

    void RegisterPropertyTypeCustomizations();
    void PrepareAutoGeneratedDefaultEvents();
    void RegisterComponentVisualizer(FName ComponentClassName, TSharedPtr<FComponentVisualizer> Visualizer);

    /**
    * Registers a custom struct
    *
    * @param StructName                The name of the struct to register for property customization
    * @param StructLayoutDelegate    The delegate to call to get the custom detail layout instance
    */
    void RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate);

    template<class T>
    void RegisterCustomPinFactory();

    //Simplify Registering generated default events
#define RegisterDefaultEvent(Class, FuncName) \
    (FKismetEditorUtilities::RegisterAutoGeneratedDefaultEvent(this, Class::StaticClass(), GET_FUNCTION_NAME_CHECKED(Class, FuncName)))

public:

    /** Creates a new quest group editor. */
    TSharedRef<IUtilityTreeEditor> CreateUtilityTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UUtilityTree* UtilityTree);
};