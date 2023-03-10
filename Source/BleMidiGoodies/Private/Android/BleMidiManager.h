// Copyright (c) 2023 Nineva Studios

#pragma once
#include "BleMidiInputDevice.h"
#include "BleMidiOutputDevice.h"
#include "BleMidiManager.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDeviceInputDelegate, UBleMidiInputDevice*, Device);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDeviceOutputDelegate, UBleMidiOutputDevice*, Device);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMidiScanStatusChangedDelegate, bool, Status);

UCLASS()
class UBleMidiManager : public UObject
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	bool Initialize(FOnMidiScanStatusChangedDelegate& OnMidiScanStatusChangedDelegate,
			  FOnDeviceInputDelegate& OnDeviceInputDelegate,
			  FOnDeviceOutputDelegate& OnDeviceOutputDelegate);
	
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	bool IsBleSupported();
	
	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	bool IsBleEnabled();

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	void SetBluetoothState(bool IsEnabled);

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	void SetRequestPairing(bool NeedPairing);

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	void StartScan(int TimeoutInMilliSeconds);

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	void StopScan();

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	void DisconnectInputDevice(UBleMidiInputDevice* MidiInputDevice);

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	void DisconnectOutputDevice(UBleMidiOutputDevice* MidiOutputDevice);

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	TArray<UBleMidiInputDevice*> GetMidiInputDevices();

	UFUNCTION(BlueprintCallable, Category = "Firebase Goodies|Cloud Functions")
	TArray<UBleMidiOutputDevice*> GetMidiOutputDevices();

private:
#if PLATFORM_ANDROID
	jobject javaManager;
#endif

};
