// Copyright (c) 2023 Nineva Studios

#include "BleMidiInputDevice.h"
#include "Callbacks/BleMidiInputDeviceCallback.h"

#if PLATFORM_ANDROID
#include "Android/Utils/BleMidiMethodCallUtils.h"
#endif

const ANSICHAR* BleMidiInputDeviceClassName = "com/ninevastudios/blemidilib/InputDevice";

UBleMidiInputDevice::~UBleMidiInputDevice()
{
	if (NativeCallback)
	{
		NativeCallback->RemoveFromRoot();
	}
}

FString UBleMidiInputDevice::GetName()
{
	FString Name;
#if PLATFORM_ANDROID
	Name = BleMidiMethodCallUtils::CallStringMethod(BleMidiInputDeviceClassName, "getName", "()Ljava/lang/String;");
#endif
	return Name;
}

FString UBleMidiInputDevice::GetAddress()
{
	FString Address;
#if PLATFORM_ANDROID
	Address = BleMidiMethodCallUtils::CallStringMethod(BleMidiInputDeviceClassName, "getAddress", "()Ljava/lang/String;");
#endif
	return Address;
}

void UBleMidiInputDevice::BindOnMessageReceivedCallback(const FOnMessageReceivedDelegate& Delegate)
{
	NativeCallback = NewObject<UBleMidiInputDeviceCallback>();
	NativeCallback->BindOnMessageReceivedDelegate(Delegate);
	NativeCallback->AddToRoot();

#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiInputDeviceClassName, "bindCallback", "(J)V", (jlong) NativeCallback);
#endif
}

#if PLATFORM_ANDROID

UBleMidiInputDevice::Init(jobject Object)
{
	InputDevice = Object;
}

#endif
