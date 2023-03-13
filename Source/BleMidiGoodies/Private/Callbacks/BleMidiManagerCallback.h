// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiManager.h"

#include "BleMidiManagerCallback.generated.h"

UCLASS()
class UBleMidiManagerCallback : public UObject
{
	GENERATED_BODY()
public:

	void BindOnInputDeviceDelegate(const FOnDeviceInputDelegate& Delegate);
	void BindOnOutputDeviceDelegate(const FOnDeviceOutputDelegate& Delegate);
	void BindOnScanStatusChangedDelegate(const FOnMidiScanStatusChangedDelegate& Delegate);

	void ExecuteOnInputDevice(UBleMidiInputDevice* InputDevice);
	void ExecuteOnOutputDevice(UBleMidiOutputDevice* OutputDevice);
	void ExecuteOnScanStatusChanged(bool Status);

private:	
	FOnDeviceInputDelegate OnDeviceInputDelegate;
	FOnDeviceOutputDelegate OnDeviceOutputDelegate;
	FOnMidiScanStatusChangedDelegate OnMidiScanStatusChangedDelegate;
};
