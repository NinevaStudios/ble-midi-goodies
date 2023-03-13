// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiInputDevice.h"

#include "BleMidiInputDeviceCallback.generated.h"

UCLASS()
class UBleMidiInputDeviceCallback : public UObject
{
	GENERATED_BODY()
public:
	
	void BindOnMessageReceivedDelegate(const FOnMessageReceivedDelegate& Delegate);

	void ExecuteOnMessageReceived(EMidiMessageType Type, const TArray<int>& Data);

private:
	FOnMessageReceivedDelegate OnMessageReceivedDelegate;
};
