// Copyright (c) 2023 Nineva Studios

#pragma once
#include "BleMidiInputDevice.h"
#include "BleMidiOutputDevice.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#endif

#include "BleMidiManager.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDeviceInputDelegate, UBleMidiInputDevice*, Device);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDeviceOutputDelegate, UBleMidiOutputDevice*, Device);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMidiScanStatusChangedDelegate, bool, Status);

class UBleMidiManagerCallback;

UCLASS(BlueprintType)
class BLEMIDIGOODIES_API UBleMidiManager : public UObject
{
	GENERATED_BODY()
public:

	~UBleMidiManager();
	
	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	bool Initialize(const FOnMidiScanStatusChangedDelegate& OnMidiScanStatusChangedDelegate,
		const FOnDeviceInputDelegate& OnDeviceInputDelegate,
		const FOnDeviceOutputDelegate& OnDeviceOutputDelegate);
	
	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	bool IsBleSupported();
	
	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	bool IsBleEnabled();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	void SetBluetoothState(bool IsEnabled);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	void SetRequestPairing(bool NeedPairing);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	void StartScan(int TimeoutInMilliSeconds);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	void StopScan();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	void DisconnectInputDevice(UBleMidiInputDevice* MidiInputDevice);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	void DisconnectOutputDevice(UBleMidiOutputDevice* MidiOutputDevice);

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	TArray<UBleMidiInputDevice*> GetMidiInputDevices();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Manager")
	TArray<UBleMidiOutputDevice*> GetMidiOutputDevices();

private:
#if PLATFORM_ANDROID
	jobject JavaManager;
#endif
	UBleMidiManagerCallback* NativeCallback;
};
