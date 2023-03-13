// Copyright (c) 2023 Nineva Studios

#include "BleMidiBPL.h"
#include "BleMidiManager.h"

#if PLATFORM_ANDROID
#include "Android/Utils/BleMidiMethodCallUtils.h"
#endif

const ANSICHAR* UtilsClassName = "com/ninevastudios/blemidilib/Utils";

UBleMidiManager* UBleMidiBPL::CreateMidiManager()
{
	return NewObject<UBleMidiManager>();	
}

void UBleMidiBPL::RequestBluetoothPermissions()
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallStaticVoidMethod(UtilsClassName, "requestBluetoothPermissions",
		"(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UBleMidiBPL::RequestPermissions(const TArray<FString>& Permissions)
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallStaticVoidMethod(UtilsClassName, "requestPermissions",
		"(Landroid/app/Activity;[Ljava/lang/String;)V", FJavaWrapper::GameActivityThis,
		BleMidiMethodCallUtils::ConvertToJStringArray(Permissions));
#endif
}

void UBleMidiBPL::OpenApplicationSettings()
{
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallStaticVoidMethod(UtilsClassName, "openApplicationSettings",
		"(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}
