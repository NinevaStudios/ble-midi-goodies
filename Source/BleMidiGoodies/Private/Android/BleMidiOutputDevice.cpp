// Copyright (c) 2023 Nineva Studios

#include "BleMidiOutputDevice.h"

const ANSICHAR* BleMidiOutputDeviceClassName = "com/ninevastudios/blemidilib/OutputDevice";

UBleMidiOutputDevice::UBleMidiOutputDevice()
{
	
}

FString UBleMidiOutputDevice::GetName()
{
	FString Name;
#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	Name = BleMidiMethodCallUtils::CallStringMethod(BleMidiOutputDeviceClassName, "getName", "()Ljava/lang/String;");
#endif
	return Name;
}

FString UBleMidiOutputDevice::GetAddress()
{
	FString Address;
#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	Address = BleMidiMethodCallUtils::CallStringMethod(BleMidiOutputDeviceClassName, "getAddress", "()Ljava/lang/String;");
#endif
	return Address;
}

void UBleMidiOutputDevice::SendMessage(int Type, TArray<int> Data)
{
#if PLATFORM_ANDROID
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	// TODO: ConvertToJIntArray(Data) may need specifier * or &
	BleMidiMethodCallUtils::CallVoidMethod(BleMidiOutputDeviceClassName, "sendMessage", "(I[I)V", Type, BleMidiCallMethodUtils::ConvertToJIntArray(Data));
#endif
}

#if PLATFORM_ANDROID

UBleMidiOutputDevice::Init(jobject Object)
{
	OutputDevice = Object;
}

#endif
