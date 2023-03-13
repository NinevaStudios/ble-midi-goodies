// Copyright (c) 2023 Nineva Studios

#pragma once
#include "Callbacks/BleMidiInputDeviceCallback.h"

#include "BleMidiInputDevice.generated.h"




UCLASS()
class UBleMidiInputDevice : public UObject
{
	GENERATED_BODY()
public:
	~UBleMidiInputDevice();
	
	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Output Device")
	FString GetName();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Output Device")
	FString GetAddress();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Output Device")
	void BindOnMessageReceivedCallback(const FOnMessageReceivedDelegate& Delegate);

#if PLATFORM_ANDROID
	void Init(jobject Object);
#endif

private:
#if PLATFORM_ANDROID
	jobject InputDevice;
#endif

public:
#if PLATFORM_ANDROID
	FORCEINLINE jobject* GetInputDevice() const { return InputDevice; }
#endif

	UBleMidiInputDeviceCallback* NativeCallback;
};
