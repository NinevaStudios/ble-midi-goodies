// Copyright (c) 2023 Nineva Studios

#include "BleMidiManager.h"

#include "Callbacks/BleMidiManagerCallback.h"

#if PLATFORM_ANDROID
#include "Android/Utils/BleMidiMethodCallUtils.h"
#endif

const ANSICHAR* BleMidiManagerClassName = "com/ninevastudios/blemidilib/BleMidiManager";

UBleMidiManager::~UBleMidiManager()
{
	if (NativeCallback)
	{
		NativeCallback->RemoveFromRoot();
	}
}

bool UBleMidiManager::Initialize(const FOnMidiScanStatusChangedDelegate& OnMidiScanStatusChangedDelegate,
	const FOnDeviceInputDelegate& OnDeviceInputDelegate, const FOnDeviceOutputDelegate& OnDeviceOutputDelegate)
{
	NativeCallback = NewObject<UBleMidiManagerCallback>();
	NativeCallback->BindOnInputDeviceDelegate(OnDeviceInputDelegate);
	NativeCallback->BindOnOutputDeviceDelegate(OnDeviceOutputDelegate);
	NativeCallback->BindOnScanStatusChangedDelegate(OnMidiScanStatusChangedDelegate);
	NativeCallback->AddToRoot();

	bool bIsInitializationSuccessful = false;
#if PLATFORM_ANDROID
	bIsInitializationSuccessful = BleMidiMethodCallUtils::CallBoolMethod(BleMidiManagerClassName, "initialize",
		"(JLandroid/app/Activity;)Z", (jlong) NativeCallback, FJavaWrapper::GameActivityThis);
#endif
	return bIsInitializationSuccessful;
}

bool UBleMidiManager::IsBleSupported()
{
	bool bIsBleSupported = false;
#if PLATFORM_ANDROID
	bIsBleSupported = BleMidiMethodCallUtils::CallBoolMethod(BleMidiManagerClassName, "isBleSupported",
		"(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif
	return bIsBleSupported;
}

bool UBleMidiManager::IsBleEnabled()
{
	bool bIsBleEnabled = false;
#if PLATFORM_ANDROID
	bIsBleEnabled = BleMidiMethodCallUtils::CallBoolMethod(BleMidiManagerClassName, "isBluetoothEnabled", "()Z");
#endif
	return bIsBleEnabled;
}

void UBleMidiManager::SetBluetoothState(bool IsEnabled)
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiManagerClassName, "setBluetoothState", "(Z)V", IsEnabled);
#endif
}

void UBleMidiManager::SetRequestPairing(bool NeedPairing)
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiManagerClassName, "setRequestPairing", "(Z)V", NeedPairing);
#endif
}

void UBleMidiManager::StartScan(int TimeoutInMilliSeconds)
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiManagerClassName, "startScan", "(I)V", TimeoutInMilliSeconds);
#endif
}

void UBleMidiManager::StopScan()
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiManagerClassName, "stopScan", "()V");
#endif
}

void UBleMidiManager::DisconnectInputDevice(UBleMidiInputDevice* MidiInputDevice)
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiManagerClassName, "disconnectInputDevice", "(Lcom/ninevastudios/blemidilib/InputDevice;)V", MidiInputDevice->GetInputDevice());
#endif
}

void UBleMidiManager::DisconnectOutputDevice(UBleMidiOutputDevice* MidiOutputDevice)
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiManagerClassName, "disconnectOutputDevice", "(Lcom/ninevastudios/blemidilib/OutputDevice;)V", MidiOutputDevice->GetOutputDevice());
#endif
}

TArray<UBleMidiInputDevice*> UBleMidiManager::GetMidiInputDevices()
{
	TArray<UBleMidiInputDevice*> InputDevices;
#if PLATFORM_ANDROID
	jobjectArray InputDevicesObjectArray = BleMidiMethodCallUtils::CallObjectMethod(BleMidiManagerClassName, "getMidiInputDevices", "()[Lcom/ninevastudios/blemidilib/InputDevice;");
	InputDevices = BleMidiMethodCallUtils::ConvertToInputArray(InputDevicesObjectArray);
#endif
	return InputDevices;
}

TArray<UBleMidiOutputDevice*> UBleMidiManager::GetMidiOutputDevices()
{
	TArray<UBleMidiOutputDevice*> OutputDevices;
#if PLATFORM_ANDROID
	jobjectArray OutputDevicesObjectArray = BleMidiMethodCallUtils::CallObjectMethod(BleMidiManagerClassName, "getMidiOutputDevices", "()[Lcom/ninevastudios/blemidilib/OutputDevice;");
	OutputDevices = BleMidiMethodCallUtils::ConvertToInputArray(OutputDevicesObjectArray);
#endif
	return OutputDevices;
}
