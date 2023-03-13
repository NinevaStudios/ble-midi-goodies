// Copyright (c) 2023 Nineva Studios

#include "BleMidiInputDevice.h"
#include "Callbacks/BleMidiInputDeviceCallback.h"

#if PLATFORM_ANDROID
#include "Android/Utils/BleMidiMethodCallUtils.h"
#endif

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
	if (InputDevice != nullptr)	
		Name = BleMidiMethodCallUtils::CallStringMethod(InputDevice, "getName", "()Ljava/lang/String;");
#endif
	return Name;
}

FString UBleMidiInputDevice::GetAddress()
{
	FString Address;
#if PLATFORM_ANDROID
	if (InputDevice != nullptr)	
		Address = BleMidiMethodCallUtils::CallStringMethod(InputDevice, "getAddress", "()Ljava/lang/String;");
#endif
	return Address;
}

void UBleMidiInputDevice::BindOnMessageReceivedCallback(const FOnMessageReceivedDelegate& Delegate)
{
	NativeCallback = NewObject<UBleMidiInputDeviceCallback>();
	NativeCallback->BindOnMessageReceivedDelegate(Delegate);
	NativeCallback->AddToRoot();

#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallVoidMethod(InputDevice, "bindCallback", "(J)V", (jlong) NativeCallback);
#endif
}

#if PLATFORM_ANDROID

void UBleMidiInputDevice::Init(jobject Object)
{
	InputDevice = Object;
}

#endif
