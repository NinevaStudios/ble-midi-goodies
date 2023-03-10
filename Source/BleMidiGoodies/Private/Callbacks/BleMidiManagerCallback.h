// Copyright (c) 2023 Nineva Studios

#pragma once
#include "Android/BleMidiManager.h"

#include "BleMidiManagerCallback.generated.h"


UCLASS()
class UBleMidiManagerCallback : public UObject
{
public:

	UBleMidiManagerCallback();
	void BindOnInputDeviceDelegate(FOnDeviceInputDelegate& Delegate);
	void BindOnOutputDeviceDelegate(FOnDeviceOutputDelegate& Delegate);
	void BindOnScanStatusChangedDelegate(FOnMidiScanStatusChangedDelegate& Delegate);

	void ExecuteOnInputDevice(BleMidiInputDevice* InputDevice);
	void ExecuteOnOutputDevice(BleMidiOutputDevice* OutputDevice);
	void ExecuteOnScanStatusChanged(bool Status);

private:
	UPROPERTY()
	FOnDeviceInputDelegate OnDeviceInputDelegate;
	UPROPERTY()
	FOnDeviceOutputDelegate OnDeviceOutputDelegate;
	UPROPERTY()
	FOnMidiScanStatusChangedDelegate OnMidiScanStatusChangedDelegate;
};
