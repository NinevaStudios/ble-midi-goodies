#include "BleMidiInputDeviceCallback.h"
#include "Async/Async.h"

void UBleMidiInputDeviceCallback::BindOnMessageReceivedDelegate(const FOnMessageReceivedDelegate& Delegate)
{
	OnMessageReceivedDelegate = Delegate;
}

void UBleMidiInputDeviceCallback::ExecuteOnMessageReceived(EMidiMessageType Type, const TArray<int>& Data)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnMessageReceivedDelegate.ExecuteIfBound(Type, Data);
	});
}


#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_blemidilib_InputDevice_OnMessageReceived(JNIEnv* env, jclass clazz, jlong objAddr, jint type, jintArray data)
{
	
	UBleMidiInputDeviceCallback* callback = reinterpret_cast<UBleMidiInputDeviceCallback*>(objAddr);
	if (IsValid(callback))
	{
		AsyncTask(ENamedThreads::GameThread, [=]() {
		callback->ExecuteOnMessageReceived((EMidiMessageType) type, BleMidiMethodCallUtils::ConvertToIntArray(data));
	});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid OnMessageReceived callback"));
	}
}
#endif