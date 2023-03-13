// Copyright (c) 2023 Nineva Studios

#include "BleMidiOutputDevice.h"

#if PLATFORM_ANDROID
#include "Android/Utils/BleMidiMethodCallUtils.h"
#endif

FString UBleMidiOutputDevice::GetName()
{
	FString Name;
#if PLATFORM_ANDROID
	if(OutputDevice != nullptr)
		Name = BleMidiMethodCallUtils::CallStringMethod(OutputDevice, "getName", "()Ljava/lang/String;");
#endif
	return Name;
}

FString UBleMidiOutputDevice::GetAddress()
{
	FString Address;
#if PLATFORM_ANDROID
	if(OutputDevice != nullptr)
		Address = BleMidiMethodCallUtils::CallStringMethod(OutputDevice, "getAddress", "()Ljava/lang/String;");
#endif
	return Address;
}

void UBleMidiOutputDevice::SendMessage(int Type, TArray<int> Data)
{
#if PLATFORM_ANDROID
	// TODO: ConvertToJIntArray(Data) may need specifier * or &
	if(OutputDevice != nullptr)
		BleMidiMethodCallUtils::CallVoidMethod(OutputDevice, "sendMessage", "(I[I)V", Type, BleMidiMethodCallUtils::ConvertToJIntArray(Data));
#endif
}

#if PLATFORM_ANDROID

void UBleMidiOutputDevice::Init(jobject Object)
{
	OutputDevice = Object;
}

#endif
