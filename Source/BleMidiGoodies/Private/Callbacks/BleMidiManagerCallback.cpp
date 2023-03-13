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

#if PLATFORM_ANDROID

JNI_METHOD void Java_com_ninevastudios_blemidilib_BleMidiManager_OnInputDeviceEvent(JNIEnv* env, jclass clazz, jlong objAddr, jobject device)
{
	
	UBleMidiManagerCallback* callback = reinterpret_cast<UBleMidiManagerCallback*>(objAddr);
	if (IsValid(callback))
	{
		UBleMidiInputDevice* InputDevice = NewObject<UBleMidiInputDevice>();
#if PLATFORM_ANDROID
		InputDevice->Init(device);
#endif
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteOnInputDevice(InputDevice);
		});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid OnInputDevice callback"));
	}
	

}

JNI_METHOD void Java_com_ninevastudios_blemidilib_BleMidiManager_OnOutputDeviceEvent(JNIEnv* env, jclass clazz, jlong objAddr, jobject device)
{
	
	UBleMidiManagerCallback* callback = reinterpret_cast<UBleMidiManagerCallback*>(objAddr);
	if (IsValid(callback))
	{
		UBleMidiOutputDevice* OutputDevice = NewObject<UBleMidiOutputDevice>();
#if PLATFORM_ANDROID
		OutputDevice->Init(device);
#endif
		AsyncTask(ENamedThreads::GameThread, [=]() {
			callback->ExecuteOnOutputDevice(OutputDevice);
		});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid OnOutputDevice callback"));
	}
	
}

JNI_METHOD void Java_com_ninevastudios_blemidilib_BleMidiManager_OnMidiScanStatusChanged(JNIEnv* env, jclass clazz, jlong objAddr, jboolean status)
{
	
	UBleMidiManagerCallback* callback = reinterpret_cast<UBleMidiManagerCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
		callback->ExecuteOnOutputDevice(status);
	});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid OnMidiScanStatusChanged callback"));
	}
}
#endif