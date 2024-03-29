﻿// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiBPL.generated.h"

class UBleMidiManager;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPermissionGrantResultDelegate, const TArray<FString>&, Permissions, const TArray<bool>&, Granted);

UCLASS(BlueprintType)
class BLEMIDIGOODIES_API UBleMidiBPL : public UBlueprintFunctionLibrary
{
GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static UBleMidiManager* CreateMidiManager();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static void RequestBluetoothPermissions(const FOnPermissionGrantResultDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static void RequestPermissions(const TArray<FString>& Permissions, const FOnPermissionGrantResultDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static void OpenApplicationSettings();

	static void ExecutePermissionResultDelegate(const TArray<FString>& Permissions, const TArray<bool>& Granted);
private:
	static const ANSICHAR* UtilsClassName;
		
	static FOnPermissionGrantResultDelegate OnPermissionGrantResultDelegate;
};
