#include "BleMidiManagerCallback.h"

UBleMidiManagerCallback::UBleMidiManagerCallback()
{
	if (StaticClass()->GetDefaultObject() != this)
	{
		AddToRoot();
	}
}

void UBleMidiManagerCallback::BindOnInputDeviceDelegate(FOnDeviceInputDelegate& Delegate)
{
	OnDeviceInputDelegate = Delegate;
}

void UBleMidiManagerCallback::BindOnOutputDeviceDelegate(FOnDeviceOutputDelegate& Delegate)
{
	OnDeviceOutputDelegate = Delegate;
}

void UBleMidiManagerCallback::BindOnScanStatusChangedDelegate(FOnMidiScanStatusChangedDelegate& Delegate)
{
	OnMidiScanStatusChangedDelegate = Delegate;
}

void UBleMidiManagerCallback::ExecuteOnInputDevice(BleMidiInputDevice* InputDevice)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnDeviceInputDelegate.ExecuteIfBound(InputDevice);
		this->RemoveFromRoot();
	});
}

void UBleMidiManagerCallback::ExecuteOnOutputDevice(BleMidiOutputDevice* OutputDevice)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnDeviceOutputDelegate.ExecuteIfBound(OutputDevice);
		this->RemoveFromRoot();
	});
}

void UBleMidiManagerCallback::ExecuteOnScanStatusChanged(bool Status)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnMidiScanStatusChangedDelegate.ExecuteIfBound(Status);
		this->RemoveFromRoot();
	});
}


