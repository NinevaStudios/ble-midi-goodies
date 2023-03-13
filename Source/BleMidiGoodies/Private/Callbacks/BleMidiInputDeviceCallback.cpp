#include "BleMidiInputDeviceCallback.h"
#include "Async/Async.h"

void UBleMidiInputDeviceCallback::BindOnMessageReceivedDelegate(const FOnMessageReceivedDelegate& Delegate)
{
	OnMessageReceivedDelegate = Delegate;
}

void UBleMidiInputDeviceCallback::ExecuteOnMessageReceivedDelegate(EMidiMessageType Type, TArray<int> Data)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		OnMessageReceivedDelegate.ExecuteIfBound(Type, Data);
	});
}
