// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiBPL.generated.h"

class UBleMidiManager;

UCLASS()
class UBleMidiBPL : public UBlueprintFunctionLibrary
{
GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	static UBleMidiManager* CreateMidiManager();
	
};
