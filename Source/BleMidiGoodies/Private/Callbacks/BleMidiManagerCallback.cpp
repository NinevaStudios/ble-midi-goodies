#include "BleMidiManagerCallback.h"
#include "Async/Async.h"

void UBleMidiManagerCallback::BindOnInputDeviceDelegate(const FOnDeviceInputDelegate& Delegate)
{
	OnDeviceInputDelegate = Delegate;
}

void UBleMidiManagerCallback::BindOnOutputDeviceDelegate(const FOnDeviceOutputDelegate& Delegate)
{
	OnDeviceOutputDelegate = Delegate;
}

void UBleMidiManagerCallback::BindOnScanStatusChangedDelegate(const FOnMidiScanStatusChangedDelegate& Delegate)
{
	OnMidiScanStatusChangedDelegate = Delegate;
}

void UBleMidiManagerCallback::ExecuteOnInputDevice(UBleMidiInputDevice* InputDevice)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnDeviceInputDelegate.ExecuteIfBound(InputDevice);
	});
}

void UBleMidiManagerCallback::ExecuteOnOutputDevice(UBleMidiOutputDevice* OutputDevice)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnDeviceOutputDelegate.ExecuteIfBound(OutputDevice);
	});
}

void UBleMidiManagerCallback::ExecuteOnScanStatusChanged(bool Status)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnMidiScanStatusChangedDelegate.ExecuteIfBound(Status);
	});
}


