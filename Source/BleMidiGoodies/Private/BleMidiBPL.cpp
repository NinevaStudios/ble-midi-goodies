// Copyright (c) 2023 Nineva Studios

#include "BleMidiBPL.h"
#include "BleMidiManager.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/AndroidPlatform.h"
#include "Utils/BleMidiMethodCallUtils.h"
#endif

const ANSICHAR* UBleMidiBPL::UtilsClassName = "com/ninevastudios/blemidilib/Utils";
FOnPermissionGrantResultDelegate UBleMidiBPL::OnPermissionGrantResultDelegate;

UBleMidiManager* UBleMidiBPL::CreateMidiManager()
{
	return NewObject<UBleMidiManager>();	
}

void UBleMidiBPL::RequestBluetoothPermissions(const FOnPermissionGrantResultDelegate& Callback)
{
	OnPermissionGrantResultDelegate = Callback;
	
#if PLATFORM_ANDROID
	BleMidiMethodCallUtils::CallStaticVoidMethod(UtilsClassName, "requestBluetoothPermissions",
		"(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UBleMidiBPL::RequestPermissions(const TArray<FString>& Permissions, const FOnPermissionGrantResultDelegate& Callback)
{
	OnPermissionGrantResultDelegate = Callback;
	
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

void UBleMidiBPL::ExecutePermissionResultDelegate(const TArray<FString>& Permissions, const TArray<bool>& Granted)
{
	if (OnPermissionGrantResultDelegate.IsBound())
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
			OnPermissionGrantResultDelegate.ExecuteIfBound(Permissions, Granted);
		});
	}
}

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_blemidilib_Utils_OnPermissionGrantResult(JNIEnv* env, jclass clazz, jobjectArray permissions, jbooleanArray granted)
{
	UBleMidiBPL::ExecutePermissionResultDelegate(BleMidiMethodCallUtils::ConvertToStringArray(permissions),
		BleMidiMethodCallUtils::ConvertToBoolArray(granted));
}

#endif