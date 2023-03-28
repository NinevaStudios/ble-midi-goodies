// Copyright (c) 2023 Nineva Studios

#include "BleMidiManager.h"

#include "Callbacks/BleMidiManagerCallback.h"

#if PLATFORM_ANDROID
#include "Android/Utils/BleMidiMethodCallUtils.h"
#endif

UBleMidiManager::~UBleMidiManager()
{
	if (NativeCallback)
	{
		NativeCallback->RemoveFromRoot();
	}
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(JavaManager);
	JavaManager = nullptr;
#endif
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
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	
	jclass ManagerClass = FAndroidApplication::FindJavaClass("com/ninevastudios/blemidilib/BleMidiManager");
	jmethodID Constructor = FJavaWrapper::FindMethod(Env, ManagerClass, "<init>", "()V", false);
	
	JavaManager = Env->NewGlobalRef(Env->NewObject(ManagerClass, Constructor));
	if(JavaManager != nullptr)
		bIsInitializationSuccessful = BleMidiMethodCallUtils::CallBoolMethod(JavaManager, "initialize",
		"(Landroid/app/Activity;J)Z", FJavaWrapper::GameActivityThis, (jlong) NativeCallback);
#endif
	return bIsInitializationSuccessful;
}

bool UBleMidiManager::IsBleSupported()
{
	bool bIsBleSupported = false;
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		bIsBleSupported = BleMidiMethodCallUtils::CallBoolMethod(JavaManager, "isBleSupported",
		"(Landroid/app/Activity;)Z", FJavaWrapper::GameActivityThis);
#endif
	return bIsBleSupported;
}

bool UBleMidiManager::IsBleEnabled()
{
	bool bIsBleEnabled = false;
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		bIsBleEnabled = BleMidiMethodCallUtils::CallBoolMethod(JavaManager, "isBluetoothEnabled", "()Z");
#endif
	return bIsBleEnabled;
}

void UBleMidiManager::SetBluetoothState(bool IsEnabled)
{
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		BleMidiMethodCallUtils::CallVoidMethod(JavaManager, "setBluetoothState", "(Z)V", IsEnabled);
#endif
}

void UBleMidiManager::SetRequestPairing(bool NeedPairing)
{
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		BleMidiMethodCallUtils::CallVoidMethod(JavaManager, "setRequestPairing", "(Z)V", NeedPairing);
#endif
}

void UBleMidiManager::StartScan(int TimeoutInMilliSeconds)
{
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		BleMidiMethodCallUtils::CallVoidMethod(JavaManager, "startScan", "(I)V", TimeoutInMilliSeconds);
#endif
}

void UBleMidiManager::StopScan()
{
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		BleMidiMethodCallUtils::CallVoidMethod(JavaManager, "stopScan", "()V");
#endif
}

void UBleMidiManager::DisconnectInputDevice(UBleMidiInputDevice* MidiInputDevice)
{
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		BleMidiMethodCallUtils::CallVoidMethod(JavaManager, "disconnectInputDevice", "(Lcom/ninevastudios/blemidilib/InputDevice;)V", MidiInputDevice->GetInputDevice());
#endif
}

void UBleMidiManager::DisconnectOutputDevice(UBleMidiOutputDevice* MidiOutputDevice)
{
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
		BleMidiMethodCallUtils::CallVoidMethod(JavaManager, "disconnectOutputDevice", "(Lcom/ninevastudios/blemidilib/OutputDevice;)V", MidiOutputDevice->GetOutputDevice());
#endif
}

TArray<UBleMidiInputDevice*> UBleMidiManager::GetMidiInputDevices()
{
	TArray<UBleMidiInputDevice*> InputDevices;
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
	{
		jobjectArray InputDevicesObjectArray = static_cast<jobjectArray>(BleMidiMethodCallUtils::CallObjectMethod(JavaManager, "getMidiInputDevices",
			"()[Lcom/ninevastudios/blemidilib/InputDevice;"));
		InputDevices = BleMidiMethodCallUtils::ConvertToInputArray(InputDevicesObjectArray);
	}
#endif
	return InputDevices;
}

TArray<UBleMidiOutputDevice*> UBleMidiManager::GetMidiOutputDevices()
{
	TArray<UBleMidiOutputDevice*> OutputDevices;
#if PLATFORM_ANDROID
	if(JavaManager != nullptr)
	{
		jobjectArray OutputDevicesObjectArray = static_cast<jobjectArray>(BleMidiMethodCallUtils::CallObjectMethod(JavaManager, "getMidiOutputDevices",
			"()[Lcom/ninevastudios/blemidilib/OutputDevice;"));
		OutputDevices = BleMidiMethodCallUtils::ConvertToOutputArray(OutputDevicesObjectArray);
	}
#endif
	return OutputDevices;
}
