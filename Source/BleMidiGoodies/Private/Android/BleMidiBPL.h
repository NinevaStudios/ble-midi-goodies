// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiBPL.generated.h"

class UBleMidiManager;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPermissionGrantResultDelegate, TArray<FString>&, Permissions, TArray<bool>, Granted);

UCLASS()
class UBleMidiBPL : public UBlueprintFunctionLibrary
{
GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static UBleMidiManager* CreateMidiManager();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static void RequestBluetoothPermissions();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static void RequestPermissions(const TArray<FString>& Permissions);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi")
	static void OpenApplicationSettings();

	static void ExecutePermissionResultDelegate(TArray<FString>& Permissions, TArray<bool> Granted);
private:
	static const ANSICHAR* UtilsClassName;
		
	static FOnPermissionGrantResultDelegate OnPermissionGrantResultDelegate;
};
