// Copyright (c) 2023 Nineva Studios

#pragma once
#include "Android/BleMidiManager.h"

#include "BleMidiManagerCallback.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDeviceInputDelegate, UBleMidiInputDevice*, Device);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDeviceOutputDelegate, UBleMidiOutputDevice*, Device);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMidiScanStatusChangedDelegate, bool, Status);

class UBleMidiInputDevice;
class UBleMidiOutputDevice;

UCLASS()
class UBleMidiManagerCallback : public UObject
{
public:

	void BindOnInputDeviceDelegate(const FOnDeviceInputDelegate& Delegate);
	void BindOnOutputDeviceDelegate(const FOnDeviceOutputDelegate& Delegate);
	void BindOnScanStatusChangedDelegate(const FOnMidiScanStatusChangedDelegate& Delegate);

	void ExecuteOnInputDevice(UBleMidiInputDevice* InputDevice);
	void ExecuteOnOutputDevice(UBleMidiOutputDevice* OutputDevice);
	void ExecuteOnScanStatusChanged(bool Status);

private:
	UPROPERTY()
	FOnDeviceInputDelegate OnDeviceInputDelegate;
	UPROPERTY()
	FOnDeviceOutputDelegate OnDeviceOutputDelegate;
	UPROPERTY()
	FOnMidiScanStatusChangedDelegate OnMidiScanStatusChangedDelegate;
};
